'use client';

import { createContext, useContext, useState, ReactNode } from 'react';

type Language = 'en' | 'es';

interface Translations {
  header: {
    title: string;
    subtitle: string;
    ready: string;
  };
  buttons: {
    run: string;
    clear: string;
    compiling: string;
    addInput: string;
    submit: string;
    cancel: string;
  };
  labels: {
    editor: string;
    output: string;
    executionStack: string;
    symbolTable: string;
    compilationDetails: string;
    inputs: string;
    terminal: string;
    terminalConnected: string;
    terminalDisconnected: string;
    terminalLines: string;
    terminalMinimize: string;
    terminalExpand: string;
    terminalClear: string;
    terminalWaiting: string;
  };
  messages: {
    noOutput: string;
    noErrors: string;
    noWarnings: string;
    errors: string;
    warnings: string;
    executionStackEmpty: string;
    symbolTableEmpty: string;
    compilationDetailsEmpty: string;
  };
  footer: string;
}

const translations: Record<Language, Translations> = {
  en: {
    header: {
      title: 'PHP Compiler',
      subtitle: 'Powered by Lex/Yacc',
      ready: 'Ready',
    },
    buttons: {
      run: 'Run',
      clear: 'Clear',
      compiling: 'Compiling...',
      addInput: 'Add Input',
      submit: 'Submit',
      cancel: 'Cancel',
    },
    labels: {
      editor: 'Editor',
      output: 'Output',
      executionStack: 'Execution Stack',
      symbolTable: 'Symbol Table',
      compilationDetails: 'Compilation Details',
      inputs: 'Program Inputs',
      terminal: 'Backend Terminal',
      terminalConnected: 'Connected',
      terminalDisconnected: 'Disconnected',
      terminalLines: 'lines',
      terminalMinimize: 'Minimize',
      terminalExpand: 'Expand',
      terminalClear: 'Clear',
      terminalWaiting: 'Waiting for terminal output...',
    },
    messages: {
      noOutput: 'Output will appear here after compilation',
      noErrors: 'No errors',
      noWarnings: 'No warnings',
      errors: 'Errors',
      warnings: 'Warnings',
      executionStackEmpty: 'Execution stack will appear here during compilation',
      symbolTableEmpty: 'Symbol table will appear here after compilation',
      compilationDetailsEmpty: 'Compilation details will appear here',
    },
    footer: 'Built with Lex/Yacc, NestJS, Next.js and Docker',
  },
  es: {
    header: {
      title: 'Compilador PHP',
      subtitle: 'Desarrollado con Lex/Yacc',
      ready: 'Listo',
    },
    buttons: {
      run: 'Ejecutar',
      clear: 'Limpiar',
      compiling: 'Compilando...',
      addInput: 'Agregar Entrada',
      submit: 'Enviar',
      cancel: 'Cancelar',
    },
    labels: {
      editor: 'Editor',
      output: 'Salida',
      executionStack: 'Pila de Ejecución',
      symbolTable: 'Tabla de Símbolos',
      compilationDetails: 'Detalles de Compilación',
      inputs: 'Entradas del Programa',
      terminal: 'Terminal del Backend',
      terminalConnected: 'Conectado',
      terminalDisconnected: 'Desconectado',
      terminalLines: 'líneas',
      terminalMinimize: 'Minimizar',
      terminalExpand: 'Expandir',
      terminalClear: 'Limpiar',
      terminalWaiting: 'Esperando salida de la terminal...',
    },
    messages: {
      noOutput: 'La salida aparecerá aquí después de la compilación',
      noErrors: 'Sin errores',
      noWarnings: 'Sin advertencias',
      errors: 'Errores',
      warnings: 'Advertencias',
      executionStackEmpty: 'La pila de ejecución aparecerá aquí durante la compilación',
      symbolTableEmpty: 'La tabla de símbolos aparecerá aquí después de la compilación',
      compilationDetailsEmpty: 'Los detalles de compilación aparecerán aquí',
    },
    footer: 'Construido con Lex/Yacc, NestJS, Next.js y Docker',
  },
};

interface LanguageContextType {
  language: Language;
  setLanguage: (lang: Language) => void;
  t: Translations;
}

const LanguageContext = createContext<LanguageContextType | undefined>(undefined);

export function LanguageProvider({ children }: { children: ReactNode }) {
  const [language, setLanguage] = useState<Language>('en');

  return (
    <LanguageContext.Provider
      value={{
        language,
        setLanguage,
        t: translations[language],
      }}
    >
      {children}
    </LanguageContext.Provider>
  );
}

export function useLanguage() {
  const context = useContext(LanguageContext);
  if (!context) {
    throw new Error('useLanguage must be used within a LanguageProvider');
  }
  return context;
}
