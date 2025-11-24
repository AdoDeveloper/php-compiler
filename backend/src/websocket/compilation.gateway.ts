import {
  WebSocketGateway,
  WebSocketServer,
  SubscribeMessage,
  MessageBody,
  ConnectedSocket,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { CompilerService } from '../compiler/compiler.service';

@WebSocketGateway({
  cors: {
    origin: process.env.FRONTEND_URL || 'http://localhost:3000',
    credentials: true,
  },
})
export class CompilationGateway {
  @WebSocketServer()
  server: Server;

  constructor(private readonly compilerService: CompilerService) {}

  @SubscribeMessage('compile')
  async handleCompile(
    @MessageBody() data: { code: string },
    @ConnectedSocket() client: Socket,
  ) {
    try {
      // Enviar mensaje de inicio
      client.emit('compilation:start', {
        message: 'Iniciando compilación...',
        timestamp: new Date().toISOString(),
      });

      // Compilar el código
      const result = await this.compilerService.compile(data.code);

      // Enviar actualizaciones de la pila en tiempo real
      if (result.executionStack && result.executionStack.length > 0) {
        for (let i = 0; i < result.executionStack.length; i++) {
          client.emit('stack:update', {
            index: i,
            entry: result.executionStack[i],
            total: result.executionStack.length,
          });
          // Pequeña pausa para simular ejecución en tiempo real
          await new Promise((resolve) => setTimeout(resolve, 50));
        }
      }

      // Enviar resultado final
      client.emit('compilation:complete', result);

      return {
        status: 'success',
        message: 'Compilación completada',
      };
    } catch (error) {
      client.emit('compilation:error', {
        message: error.message,
        timestamp: new Date().toISOString(),
      });

      return {
        status: 'error',
        message: error.message,
      };
    }
  }

  @SubscribeMessage('getInfo')
  async handleGetInfo(@ConnectedSocket() client: Socket) {
    const info = await this.compilerService.getCompilerInfo();
    client.emit('compiler:info', info);
    return info;
  }

  afterInit() {
    console.log('✅ WebSocket Gateway inicializado');
  }

  handleConnection(client: Socket) {
    console.log(`🔌 Cliente conectado: ${client.id}`);
  }

  handleDisconnect(client: Socket) {
    console.log(`🔌 Cliente desconectado: ${client.id}`);
  }
}
