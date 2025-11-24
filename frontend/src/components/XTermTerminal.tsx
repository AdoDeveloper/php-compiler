'use client';

import { useEffect, useRef, useState } from 'react';
import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';
import { WebLinksAddon } from 'xterm-addon-web-links';
import { io, Socket } from 'socket.io-client';
import 'xterm/css/xterm.css';

export default function XTermTerminal() {
  const terminalRef = useRef<HTMLDivElement>(null);
  const xtermRef = useRef<Terminal | null>(null);
  const socketRef = useRef<Socket | null>(null);
  const fitAddonRef = useRef<FitAddon | null>(null);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    if (!terminalRef.current) return;

    // Initialize xterm.js
    const term = new Terminal({
      cursorBlink: true,
      fontSize: 13,
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
      rows: 20,
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

    // Connect to WebSocket - detectar ambiente igual que Terminal.tsx
    const socketUrl = typeof window !== 'undefined' && window.location.hostname !== 'localhost'
      ? window.location.origin  // Producción (Render): usar origin actual
      : (process.env.NEXT_PUBLIC_API_URL || 'http://localhost:3001');  // Desarrollo (Docker): backend en 3001

    const socket = io(socketUrl);
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
    // Fit on mount
    setTimeout(() => handleResize(), 100);

    return () => {
      window.removeEventListener('resize', handleResize);
      socket.disconnect();
      term.dispose();
    };
  }, []);

  return <div ref={terminalRef} className="h-full w-full p-2" />;
}
