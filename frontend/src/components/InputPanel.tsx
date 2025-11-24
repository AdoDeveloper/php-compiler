'use client';

import { useState } from 'react';
import { VscClose, VscAdd, VscTrash } from 'react-icons/vsc';
import { useLanguage } from '../contexts/LanguageContext';

interface InputPanelProps {
  onSubmit: (inputs: string[]) => void;
  onClose: () => void;
}

export default function InputPanel({ onSubmit, onClose }: InputPanelProps) {
  const { t } = useLanguage();
  const [inputs, setInputs] = useState<string[]>(['']);

  const handleAddInput = () => {
    setInputs([...inputs, '']);
  };

  const handleRemoveInput = (index: number) => {
    const newInputs = inputs.filter((_, i) => i !== index);
    setInputs(newInputs.length > 0 ? newInputs : ['']);
  };

  const handleInputChange = (index: number, value: string) => {
    const newInputs = [...inputs];
    newInputs[index] = value;
    setInputs(newInputs);
  };

  const handleSubmit = () => {
    onSubmit(inputs.filter(input => input.trim().length > 0));
  };

  return (
    <div className="fixed inset-0 bg-black/60 backdrop-blur-sm flex items-center justify-center z-50">
      <div className="bg-gray-900 rounded-xl p-6 w-full max-w-md shadow-2xl border border-gray-800">
        <div className="flex items-center justify-between mb-4">
          <h3 className="text-xl font-semibold text-white">{t.labels.inputs}</h3>
          <button
            onClick={onClose}
            className="text-gray-400 hover:text-white transition-colors"
          >
            <VscClose className="text-2xl" />
          </button>
        </div>

        <div className="space-y-2 mb-4 max-h-60 overflow-auto custom-scrollbar">
          {inputs.map((input, index) => (
            <div key={index} className="flex gap-2">
              <input
                type="text"
                value={input}
                onChange={(e) => handleInputChange(index, e.target.value)}
                placeholder={`Input ${index + 1}`}
                className="flex-1 bg-black border border-gray-800 rounded-lg px-3 py-2 text-white focus:outline-none focus:border-gray-700"
              />
              {inputs.length > 1 && (
                <button
                  onClick={() => handleRemoveInput(index)}
                  className="border border-gray-800 hover:border-red-500 text-gray-400 hover:text-red-400 p-2 rounded-lg transition-all"
                >
                  <VscTrash />
                </button>
              )}
            </div>
          ))}
        </div>

        <div className="flex gap-2">
          <button
            onClick={handleAddInput}
            className="flex items-center gap-2 px-4 py-2 border border-gray-800 text-gray-400 hover:text-white hover:border-gray-700 rounded-lg font-medium transition-all"
          >
            <VscAdd />
            {t.buttons.addInput}
          </button>
          <button
            onClick={handleSubmit}
            className="flex-1 px-4 py-2 bg-white text-black hover:bg-gray-100 rounded-lg font-medium transition-all"
          >
            {t.buttons.submit}
          </button>
        </div>
      </div>

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
