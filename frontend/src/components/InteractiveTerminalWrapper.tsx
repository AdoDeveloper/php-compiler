'use client';

import dynamic from 'next/dynamic';

// Import InteractiveTerminal only on client-side to avoid SSR issues with xterm.js
const InteractiveTerminal = dynamic(
  () => import('./InteractiveTerminal'),
  {
    ssr: false,
    loading: () => null,
  }
);

export default InteractiveTerminal;
