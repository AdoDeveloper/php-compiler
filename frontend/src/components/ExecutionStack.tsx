'use client';

import { useLanguage } from '../contexts/LanguageContext';

interface ExecutionStackProps {
  stack: string[];
}

export default function ExecutionStack({ stack }: ExecutionStackProps) {
  const { t } = useLanguage();

  return (
    <div className="space-y-2">
      {stack.length === 0 ? (
        <div className="flex flex-col items-center justify-center h-[400px] text-gray-600">
          <p className="text-sm">{t.messages.executionStackEmpty}</p>
        </div>
      ) : (
        <div className="space-y-2 max-h-[450px] overflow-y-auto custom-scrollbar">
          {stack.map((entry, index) => (
            <div
              key={index}
              className="group bg-gray-900/50 border border-gray-800 hover:border-gray-700 rounded-lg p-3 transition-all animate-slideIn"
              style={{
                animationDelay: `${index * 20}ms`,
              }}
            >
              <div className="flex items-start gap-3">
                <span className="text-gray-500 font-mono text-xs min-w-[32px] bg-gray-800 px-2 py-1 rounded">
                  {stack.length - index}
                </span>
                <span className="text-gray-300 font-mono text-xs flex-1 leading-relaxed">
                  {entry}
                </span>
              </div>
            </div>
          ))}
        </div>
      )}

      <style jsx>{`
        @keyframes slideIn {
          from {
            opacity: 0;
            transform: translateX(-8px);
          }
          to {
            opacity: 1;
            transform: translateX(0);
          }
        }

        .animate-slideIn {
          animation: slideIn 0.3s ease-out forwards;
        }

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
      `}</style>
    </div>
  );
}
