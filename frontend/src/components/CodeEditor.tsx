'use client';

import { Editor } from '@monaco-editor/react';
import { useEffect, useState } from 'react';

interface CodeEditorProps {
  code: string;
  onChange: (value: string) => void;
}

export default function CodeEditor({ code, onChange }: CodeEditorProps) {
  const [isMobile, setIsMobile] = useState(false);

  useEffect(() => {
    const checkMobile = () => {
      setIsMobile(window.innerWidth < 768);
    };

    checkMobile();
    window.addEventListener('resize', checkMobile);

    return () => window.removeEventListener('resize', checkMobile);
  }, []);

  return (
    <div className="h-[600px] rounded-lg overflow-hidden">
      <Editor
        height="100%"
        defaultLanguage="php"
        value={code}
        onChange={(value) => onChange(value || '')}
        theme="vs-dark"
        options={{
          minimap: { enabled: !isMobile },
          fontSize: isMobile ? 12 : 14,
          lineNumbers: 'on',
          roundedSelection: false,
          scrollBeyondLastLine: false,
          automaticLayout: true,
          tabSize: 2,
          wordWrap: 'on',
          cursorBlinking: 'smooth',
          cursorSmoothCaretAnimation: 'on',
          smoothScrolling: true,
          formatOnPaste: true,
          formatOnType: true,
          readOnly: false,
          domReadOnly: false,
          quickSuggestions: !isMobile,
          suggestOnTriggerCharacters: !isMobile,
          acceptSuggestionOnEnter: isMobile ? 'off' : 'on',
          tabCompletion: isMobile ? 'off' : 'on',
        }}
      />
    </div>
  );
}
