'use client';

import { createContext, useContext, useState, useEffect, ReactNode } from 'react';

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
    examples: string;
    login: string;
    logout: string;
    copy: string;
    copied: string;
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
    logs: string;
    interactive: string;
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
  terminal: {
    accessTitle: string;
    accessSubtitle: string;
    passwordLabel: string;
    passwordPlaceholder: string;
    accessButton: string;
    authenticating: string;
    authRequired: string;
    loadingTerminal: string;
    incorrectPassword: string;
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
      examples: 'Examples',
      login: 'Login',
      logout: 'Logout',
      copy: 'Copy',
      copied: 'Copied!',
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
      logs: 'Logs',
      interactive: 'Terminal',
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
    terminal: {
      accessTitle: 'Terminal Access',
      accessSubtitle: 'Authentication required',
      passwordLabel: 'Password',
      passwordPlaceholder: 'Enter password',
      accessButton: 'Access Terminal',
      authenticating: 'Authenticating...',
      authRequired: 'Authentication required to access interactive terminal',
      loadingTerminal: 'Loading interactive terminal...',
      incorrectPassword: 'Incorrect password. Please try again.',
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
      examples: 'Ejemplos',
      login: 'Iniciar Sesión',
      logout: 'Cerrar Sesión',
      copy: 'Copiar',
      copied: '¡Copiado!',
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
      logs: 'Registros',
      interactive: 'Terminal',
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
    terminal: {
      accessTitle: 'Acceso a Terminal',
      accessSubtitle: 'Autenticación requerida',
      passwordLabel: 'Contraseña',
      passwordPlaceholder: 'Ingrese contraseña',
      accessButton: 'Acceder a Terminal',
      authenticating: 'Autenticando...',
      authRequired: 'Se requiere autenticación para acceder a la terminal interactiva',
      loadingTerminal: 'Cargando terminal interactiva...',
      incorrectPassword: 'Contraseña incorrecta. Por favor intente de nuevo.',
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

  // Cargar idioma guardado al iniciar
  useEffect(() => {
    const savedLanguage = localStorage.getItem('app_language');
    if (savedLanguage === 'en' || savedLanguage === 'es') {
      setLanguage(savedLanguage);
    }
  }, []);

  // Función personalizada para cambiar idioma y guardarlo
  const changeLanguage = (lang: Language) => {
    setLanguage(lang);
    localStorage.setItem('app_language', lang);
  };

  return (
    <LanguageContext.Provider
      value={{
        language,
        setLanguage: changeLanguage,
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
