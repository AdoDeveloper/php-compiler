import axios from 'axios';
import { io, Socket } from 'socket.io-client';

// En producción (Render), usar rutas relativas (el proxy maneja el ruteo)
// En desarrollo (Docker Desktop), usar la URL del backend
const API_URL = typeof window !== 'undefined' && window.location.hostname !== 'localhost'
  ? window.location.origin  // Producción: usar la URL actual (proxy manejará /api)
  : (process.env.NEXT_PUBLIC_API_URL || 'http://localhost:3001');  // Desarrollo: backend en 3001

export interface CompilationResult {
  success: boolean;
  output: string;
  errors: string;
  symbolTable: string;
  executionStack: string[];
  generatedCode?: string;
}

class CompilerService {
  private socket: Socket | null = null;

  connect() {
    if (this.socket?.connected) return;

    this.socket = io(API_URL);

    this.socket.on('connect', () => {
      console.log('✅ Conectado al servidor WebSocket');
    });

    this.socket.on('disconnect', () => {
      console.log('❌ Desconectado del servidor WebSocket');
    });
  }

  disconnect() {
    if (this.socket) {
      this.socket.disconnect();
      this.socket = null;
    }
  }

  async compile(code: string, inputs?: string[]): Promise<CompilationResult> {
    try {
      const response = await axios.post(`${API_URL}/api/compiler/compile`, {
        code,
        inputs: inputs || [],
      });

      // Always return the response, even if success is false
      // because it contains compiler errors
      return response.data;
    } catch (error: any) {
      // Only throw error if there's a network or server problem
      // Not if the compiler returned syntax/semantic errors
      if (error.response?.data) {
        return error.response.data;
      }

      throw new Error(
        error.response?.data?.message || 'Backend connection error'
      );
    }
  }

  async getInfo(): Promise<any> {
    try {
      const response = await axios.get(`${API_URL}/api/compiler/info`);
      return response.data;
    } catch (error: any) {
      throw new Error('Error al obtener información del compilador');
    }
  }

  onCompilationStart(callback: (data: any) => void) {
    this.socket?.on('compilation:start', callback);
  }

  onStackUpdate(callback: (data: any) => void) {
    this.socket?.on('stack:update', callback);
  }

  onCompilationComplete(callback: (result: CompilationResult) => void) {
    this.socket?.on('compilation:complete', callback);
  }

  onCompilationError(callback: (data: any) => void) {
    this.socket?.on('compilation:error', callback);
  }

  emitCompile(code: string) {
    this.socket?.emit('compile', { code });
  }
}

export const compilerService = new CompilerService();
