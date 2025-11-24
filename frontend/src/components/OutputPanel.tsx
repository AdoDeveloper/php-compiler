'use client';

import { VscCheck, VscError, VscWarning } from 'react-icons/vsc';
import { useLanguage } from '../contexts/LanguageContext';

interface OutputPanelProps {
  output: string;
  errors: string;
  warnings?: string;
}

export default function OutputPanel({ output, errors, warnings }: OutputPanelProps) {
  const { t } = useLanguage();
  const hasErrors = errors && errors.trim().length > 0;
  const hasWarnings = warnings && warnings.trim().length > 0;
  const hasOutput = output && output.trim().length > 0;

  return (
    <div className="space-y-4">
      {/* Output Section */}
      <div className="min-h-[200px] max-h-[300px] overflow-auto">
        {!hasOutput ? (
          <div className="flex flex-col items-center justify-center h-[200px] text-gray-600">
            <p className="text-sm">{t.messages.noOutput}</p>
          </div>
        ) : (
          <pre className="text-green-400 font-mono text-sm whitespace-pre-wrap leading-relaxed">
            {output}
          </pre>
        )}
      </div>

      {/* Status Bar */}
      <div className="flex gap-2 pt-3 border-t border-gray-800">
        {/* Errors */}
        {hasErrors ? (
          <div className="flex-1 bg-red-500/10 border border-red-500/20 rounded-lg p-3">
            <div className="flex items-center gap-2 text-red-400 font-medium mb-2 text-xs">
              <VscError />
              <span>{t.messages.errors}</span>
            </div>
            <pre className="text-red-300 font-mono text-xs whitespace-pre-wrap max-h-20 overflow-auto">
              {errors}
            </pre>
          </div>
        ) : (
          <div className="flex-1 bg-green-500/5 border border-green-500/10 rounded-lg p-3">
            <div className="flex items-center gap-2 text-green-500 font-medium text-xs">
              <VscCheck />
              <span>{t.messages.noErrors}</span>
            </div>
          </div>
        )}

        {/* Warnings */}
        {hasWarnings ? (
          <div className="flex-1 bg-yellow-500/10 border border-yellow-500/20 rounded-lg p-3">
            <div className="flex items-center gap-2 text-yellow-400 font-medium mb-2 text-xs">
              <VscWarning />
              <span>{t.messages.warnings}</span>
            </div>
            <pre className="text-yellow-300 font-mono text-xs whitespace-pre-wrap max-h-20 overflow-auto">
              {warnings}
            </pre>
          </div>
        ) : (
          <div className="flex-1 bg-gray-900/50 border border-gray-800 rounded-lg p-3">
            <div className="flex items-center gap-2 text-gray-500 font-medium text-xs">
              <VscCheck />
              <span>{t.messages.noWarnings}</span>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}
