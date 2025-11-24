'use client';

import { useEffect, useRef, useState } from 'react';
import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';
import { WebLinksAddon } from 'xterm-addon-web-links';
import { io, Socket } from 'socket.io-client';
import { VscTerminal, VscClose, VscChevronDown, VscChevronUp } from 'react-icons/vsc';
import { useLanguage } from '../contexts/LanguageContext';
import 'xterm/css/xterm.css';

const API_URL = process.env.NEXT_PUBLIC_API_URL || 'http://localhost:3001';

export default function InteractiveTerminal() {
  const { t } = useLanguage();
  const terminalRef = useRef<HTMLDivElement>(null);
  const xtermRef = useRef<Terminal | null>(null);
  const socketRef = useRef<Socket | null>(null);
  const fitAddonRef = useRef<FitAddon | null>(null);
  const [isOpen, setIsOpen] = useState(false);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    if (!isOpen || !terminalRef.current) return;

    // Initialize xterm.js
    const term = new Terminal({
      cursorBlink: true,
      fontSize: 14,
      fontFamily: '"Cascadia Code", "Fira Code", "Courier New", monospace',
      theme: {
        background: '#000000',
        foreground: '#ffffff',
        cursor: '#ffffff',
        black: '#000000',
        red: '#f87171',
        green: '#4ade80',
        yellow: '#facc15',
        blue: '#60a5fa',
        magenta: '#c084fc',
        cyan: '#22d3ee',
        white: '#f3f4f6',
        brightBlack: '#6b7280',
        brightRed: '#fca5a5',
        brightGreen: '#86efac',
        brightYellow: '#fde047',
        brightBlue: '#93c5fd',
        brightMagenta: '#d8b4fe',
        brightCyan: '#67e8f9',
        brightWhite: '#ffffff',
      },
      scrollback: 1000,
      rows: 24,
      cols: 80,
    });

    const fitAddon = new FitAddon();
    const webLinksAddon = new WebLinksAddon();

    term.loadAddon(fitAddon);
    term.loadAddon(webLinksAddon);

    term.open(terminalRef.current);
    fitAddon.fit();

    xtermRef.current = term;
    fitAddonRef.current = fitAddon;

    // Connect to WebSocket
    const socket = io(API_URL);
    socketRef.current = socket;

    socket.on('connect', () => {
      setIsConnected(true);
      term.writeln('\r\n\x1b[1;32m✓ Connected to backend container\x1b[0m');
      term.writeln('\x1b[1;33m💡 Interactive terminal ready!\x1b[0m');
      term.writeln('\x1b[90m═══════════════════════════════════════════════\x1b[0m\r\n');
    });

    socket.on('disconnect', () => {
      setIsConnected(false);
      term.writeln('\r\n\x1b[1;31m✗ Disconnected from backend\x1b[0m\r\n');
    });

    socket.on('terminal:data', (data: string) => {
      term.write(data);
    });

    socket.on('terminal:exit', (data: { code: number }) => {
      term.writeln(`\r\n\x1b[1;31mProcess exited with code ${data.code}\x1b[0m\r\n`);
    });

    // Handle user input
    term.onData((data) => {
      socket.emit('terminal:input', data);
    });

    // Handle window resize
    const handleResize = () => {
      if (fitAddonRef.current && terminalRef.current) {
        fitAddonRef.current.fit();
        const { cols, rows } = term;
        socket.emit('terminal:resize', { cols, rows });
      }
    };

    window.addEventListener('resize', handleResize);

    return () => {
      window.removeEventListener('resize', handleResize);
      socket.disconnect();
      term.dispose();
    };
  }, [isOpen]);

  const toggleTerminal = () => {
    setIsOpen(!isOpen);
  };

  const closeTerminal = () => {
    setIsOpen(false);
  };

  if (!isOpen) {
    return (
      <button
        onClick={toggleTerminal}
        className="fixed bottom-4 right-4 z-50 flex items-center gap-2 px-4 py-3 bg-white text-black hover:bg-gray-100 rounded-lg shadow-2xl font-medium transition-all border-2 border-gray-800"
      >
        <VscTerminal className="text-lg" />
        <span>{t.labels.terminal || 'Interactive Terminal'}</span>
      </button>
    );
  }

  return (
    <div className="fixed inset-x-0 bottom-0 z-50 bg-black border-t-2 border-gray-800 shadow-2xl">
      {/* Terminal Header */}
      <div className="flex items-center justify-between px-4 py-2 bg-gray-900/90 backdrop-blur-sm border-b border-gray-800">
        <div className="flex items-center gap-3">
          <VscTerminal className="text-green-400 text-lg" />
          <span className="text-sm font-semibold text-white">
            {t.labels.terminal || 'Interactive Terminal'}
          </span>
          <div className={`w-2 h-2 rounded-full ${isConnected ? 'bg-green-500' : 'bg-red-500'}`} />
          <span className="text-xs text-gray-500">
            {isConnected ? (t.labels.terminalConnected || 'Connected') : (t.labels.terminalDisconnected || 'Disconnected')}
          </span>
        </div>

        <div className="flex items-center gap-2">
          <button
            onClick={toggleTerminal}
            className="p-1.5 hover:bg-gray-800 rounded transition-colors"
          >
            <VscChevronDown className="text-gray-400 hover:text-white" />
          </button>
          <button
            onClick={closeTerminal}
            className="p-1.5 hover:bg-gray-800 rounded transition-colors"
          >
            <VscClose className="text-gray-400 hover:text-white" />
          </button>
        </div>
      </div>

      {/* Terminal Content */}
      <div className="h-[500px] p-2">
        <div ref={terminalRef} className="h-full" />
      </div>

      {/* Helper Text */}
      <div className="px-4 py-2 bg-gray-900/50 border-t border-gray-800">
        <p className="text-xs text-gray-500">
          <span className="text-yellow-400">💡 Tip:</span> Try commands like{' '}
          <code className="px-1 py-0.5 bg-gray-800 rounded text-green-400">ls</code>,{' '}
          <code className="px-1 py-0.5 bg-gray-800 rounded text-green-400">cat php.l</code>,{' '}
          <code className="px-1 py-0.5 bg-gray-800 rounded text-green-400">./phpcompiler test.php</code>
        </p>
      </div>
    </div>
  );
}
