'use client';

import { useEffect, useRef, useState } from 'react';
import { VscTerminal, VscClearAll, VscChevronDown, VscChevronUp, VscDebugConsole, VscSignOut, VscLock } from 'react-icons/vsc';
import { useLanguage } from '../contexts/LanguageContext';
import { useAuth } from '../contexts/AuthContext';
import { io, Socket } from 'socket.io-client';
import dynamic from 'next/dynamic';

// Detectar ambiente: localhost usa puerto 3001, producción usa origin actual
const getApiUrl = () => {
  if (typeof window !== 'undefined') {
    return window.location.hostname === 'localhost'
      ? (process.env.NEXT_PUBLIC_API_URL || 'http://localhost:3001')
      : window.location.origin;
  }
  return 'http://localhost:3001';
};

// Import xterm components only on client-side
const XTermTerminal = dynamic(
  () => import('./XTermTerminal'),
  { ssr: false, loading: () => <div className="h-80 flex items-center justify-center text-gray-500">Loading interactive terminal...</div> }
);

const LoginModal = dynamic(
  () => import('./LoginModal'),
  { ssr: false }
);

export default function Terminal() {
  const { t, language } = useLanguage();
  const { isAuthenticated, logout } = useAuth();
  const [logs, setLogs] = useState<Array<{ type: string; data: string; timestamp: Date }>>([]);
  const [isExpanded, setIsExpanded] = useState(false);
  const [isConnected, setIsConnected] = useState(false);
  const [activeTab, setActiveTab] = useState<'logs' | 'interactive'>('logs');
  const [showLoginModal, setShowLoginModal] = useState(false);
  const terminalRef = useRef<HTMLDivElement>(null);
  const socketRef = useRef<Socket | null>(null);

  useEffect(() => {
    // Connect to WebSocket
    const API_URL = getApiUrl();
    const socket = io(API_URL);
    socketRef.current = socket;

    socket.on('connect', () => {
      setIsConnected(true);
      addLog('system', language === 'en'
        ? '✓ Connected to backend terminal'
        : '✓ Conectado a la terminal del backend');
    });

    socket.on('disconnect', () => {
      setIsConnected(false);
      addLog('system', language === 'en'
        ? '✗ Disconnected from backend terminal'
        : '✗ Desconectado de la terminal del backend');
    });

    socket.on('terminal:output', (data: { type: string; data: string }) => {
      addLog(data.type, data.data);
    });

    socket.on('compilation:start', () => {
      addLog('compilation', language === 'en'
        ? '▶ Compilation started'
        : '▶ Compilación iniciada');
    });

    socket.on('compilation:complete', () => {
      addLog('compilation', language === 'en'
        ? '✓ Compilation completed'
        : '✓ Compilación completada');
    });

    socket.on('compilation:error', (data: { message: string }) => {
      addLog('error', `✗ ${data.message}`);
    });

    return () => {
      socket.disconnect();
    };
  }, [language]);

  const addLog = (type: string, data: string) => {
    setLogs((prev) => [...prev, { type, data, timestamp: new Date() }]);
    // Auto-scroll to bottom
    setTimeout(() => {
      if (terminalRef.current) {
        terminalRef.current.scrollTop = terminalRef.current.scrollHeight;
      }
    }, 10);
  };

  const clearLogs = () => {
    setLogs([]);
  };

  const getLogColor = (type: string) => {
    switch (type) {
      case 'stdout':
        return 'text-green-400';
      case 'stderr':
      case 'error':
        return 'text-red-400';
      case 'compilation':
        return 'text-blue-400';
      case 'system':
        return 'text-yellow-400';
      default:
        return 'text-gray-300';
    }
  };

  const handleInteractiveClick = () => {
    if (isAuthenticated) {
      setActiveTab('interactive');
    } else {
      setShowLoginModal(true);
    }
  };

  return (
    <div className={`fixed bottom-4 right-4 left-4 sm:left-auto z-40 transition-all duration-300 ${
      isExpanded ? 'sm:w-[700px] w-full' : 'w-auto'
    }`}>
      {/* Terminal Tab (always visible) */}
      <div className="flex justify-end">
        <button
          onClick={() => setIsExpanded(!isExpanded)}
          className="flex items-center gap-2 px-4 py-2 bg-gray-900 border border-gray-800 rounded-t-lg hover:bg-gray-800 transition-all shadow-lg"
        >
          <VscTerminal className="text-green-400" />
          <span className="text-sm font-medium text-white">
            {t.labels.terminal}
          </span>
          <div className={`w-2 h-2 rounded-full ${isConnected ? 'bg-green-500' : 'bg-red-500'}`} />
          {logs.length > 0 && activeTab === 'logs' && (
            <span className="text-xs bg-green-600 text-white px-2 py-0.5 rounded-full">
              {logs.length}
            </span>
          )}
          {isExpanded ? (
            <VscChevronDown className="text-gray-400" />
          ) : (
            <VscChevronUp className="text-gray-400" />
          )}
        </button>
      </div>

      {/* Terminal Panel (expandable) */}
      {isExpanded && (
        <div className="border border-gray-800 rounded-lg rounded-tr-none bg-black shadow-2xl overflow-hidden animate-slideUp max-w-full">
          {/* Terminal Header with Tabs */}
          <div className="flex flex-col sm:flex-row items-stretch sm:items-center justify-between gap-2 px-3 sm:px-4 py-2 border-b border-gray-800 bg-gray-900/50">
            <div className="flex items-center gap-1 sm:gap-2 overflow-x-auto flex-nowrap">
              <button
                onClick={() => setActiveTab('logs')}
                className={`flex items-center gap-1 sm:gap-2 px-2 sm:px-3 py-1.5 text-[10px] sm:text-xs rounded-md transition-all whitespace-nowrap ${
                  activeTab === 'logs'
                    ? 'bg-gray-800 text-white border border-gray-700'
                    : 'text-gray-400 hover:text-white hover:bg-gray-800/50'
                }`}
              >
                <VscTerminal className="text-xs sm:text-sm flex-shrink-0" />
                <span>Logs</span>
                {logs.length > 0 && (
                  <span className="text-[9px] sm:text-xs bg-gray-700 px-1 sm:px-1.5 py-0.5 rounded-full">
                    {logs.length}
                  </span>
                )}
              </button>
              <button
                onClick={handleInteractiveClick}
                className={`flex items-center gap-1 sm:gap-2 px-2 sm:px-3 py-1.5 text-[10px] sm:text-xs rounded-md transition-all whitespace-nowrap ${
                  activeTab === 'interactive'
                    ? 'bg-gray-800 text-white border border-gray-700'
                    : 'text-gray-400 hover:text-white hover:bg-gray-800/50'
                }`}
              >
                <VscDebugConsole className="text-xs sm:text-sm flex-shrink-0" />
                <span>Terminal</span>
                {!isAuthenticated && (
                  <VscLock className="text-xs text-yellow-500 flex-shrink-0" />
                )}
              </button>
            </div>

            <div className="flex items-center gap-1 sm:gap-2">
              {activeTab === 'logs' && (
                <button
                  onClick={clearLogs}
                  className="flex items-center gap-1 sm:gap-2 px-2 sm:px-3 py-1 text-[10px] sm:text-xs border border-gray-800 text-gray-400 hover:text-white hover:border-gray-700 rounded-lg transition-all whitespace-nowrap"
                >
                  <VscClearAll className="flex-shrink-0" />
                  <span className="hidden xs:inline">{t.labels.terminalClear}</span>
                </button>
              )}

              {activeTab === 'interactive' && isAuthenticated && (
                <button
                  onClick={() => {
                    logout();
                    setActiveTab('logs');
                  }}
                  className="flex items-center gap-1 sm:gap-2 px-2 sm:px-3 py-1 text-[10px] sm:text-xs border border-gray-800 text-gray-400 hover:text-red-400 hover:border-red-700 rounded-lg transition-all whitespace-nowrap"
                  title="Logout"
                >
                  <VscSignOut className="flex-shrink-0" />
                  <span className="hidden xs:inline">Logout</span>
                </button>
              )}
            </div>
          </div>

          {/* Terminal Content */}
          {activeTab === 'logs' ? (
            <div
              ref={terminalRef}
              className="h-80 overflow-y-auto custom-scrollbar bg-black px-4 py-2"
            >
              {logs.length === 0 ? (
                <div className="flex items-center justify-center h-full text-gray-600 text-sm">
                  {t.labels.terminalWaiting}
                </div>
              ) : (
                <div className="space-y-1">
                  {logs.map((log, index) => (
                    <div key={index} className="flex gap-2 font-mono text-xs">
                      <span className="text-gray-600 select-none">
                        {log.timestamp.toLocaleTimeString()}
                      </span>
                      <pre className={`flex-1 whitespace-pre-wrap ${getLogColor(log.type)}`}>
                        {log.data}
                      </pre>
                    </div>
                  ))}
                </div>
              )}
            </div>
          ) : (
            <div className="h-80 bg-black">
              {isAuthenticated ? (
                <XTermTerminal />
              ) : (
                <div className="h-full flex items-center justify-center text-gray-500">
                  <div className="text-center space-y-3">
                    <div className="text-4xl"><VscLock /></div>
                    <p className="text-sm">Authentication required to access interactive terminal</p>
                    <button
                      onClick={() => setShowLoginModal(true)}
                      className="px-4 py-2 bg-green-600 hover:bg-green-700 text-white text-sm rounded-lg transition-all"
                    >
                      Login
                    </button>
                  </div>
                </div>
              )}
            </div>
          )}
        </div>
      )}

      {/* Login Modal */}
      {showLoginModal && (
        <LoginModal
          isOpen={showLoginModal}
          onClose={() => {
            setShowLoginModal(false);
            if (isAuthenticated) {
              setActiveTab('interactive');
            }
          }}
        />
      )}

      <style jsx>{`
        .custom-scrollbar::-webkit-scrollbar {
          width: 6px;
        }

        .custom-scrollbar::-webkit-scrollbar-track {
          background: transparent;
        }

        .custom-scrollbar::-webkit-scrollbar-thumb {
          background: #374151;
          border-radius: 3px;
        }

        .custom-scrollbar::-webkit-scrollbar-thumb:hover {
          background: #4b5563;
        }

        @keyframes slideUp {
          from {
            opacity: 0;
            transform: translateY(10px);
          }
          to {
            opacity: 1;
            transform: translateY(0);
          }
        }

        .animate-slideUp {
          animation: slideUp 0.2s ease-out;
        }
      `}</style>
    </div>
  );
}
