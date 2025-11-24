'use client';

import { useLanguage } from '../contexts/LanguageContext';

interface SymbolTableProps {
  table: string;
}

export default function SymbolTable({ table }: SymbolTableProps) {
  const { t } = useLanguage();
  const hasTable = table && table.trim().length > 0;

  return (
    <div>
      {!hasTable ? (
        <div className="flex flex-col items-center justify-center h-[400px] text-gray-600">
          <p className="text-sm">{t.messages.symbolTableEmpty}</p>
        </div>
      ) : (
        <div className="max-h-[450px] overflow-auto custom-scrollbar">
          <pre className="text-gray-300 font-mono text-xs whitespace-pre leading-relaxed">
            {table}
          </pre>
        </div>
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
      `}</style>
    </div>
  );
}
