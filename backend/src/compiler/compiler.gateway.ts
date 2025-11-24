import {
  WebSocketGateway,
  WebSocketServer,
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { CompilerService } from './compiler.service';

@WebSocketGateway({
  cors: {
    origin: ['http://localhost:3000', 'http://localhost:3002'],
    credentials: true,
  },
})
export class CompilerGateway implements OnGatewayConnection, OnGatewayDisconnect, OnGatewayInit {
  @WebSocketServer()
  server: Server;

  constructor(private compilerService: CompilerService) {}

  afterInit() {
    console.log('WebSocket Gateway initialized');
    // Register this gateway with the compiler service
    this.compilerService.setGateway(this);
  }

  handleConnection(client: Socket) {
    console.log(`Client connected: ${client.id}`);
    this.sendTerminalOutput('system', `✓ Client ${client.id} connected to terminal`);
  }

  handleDisconnect(client: Socket) {
    console.log(`Client disconnected: ${client.id}`);
    this.sendTerminalOutput('system', `✗ Client ${client.id} disconnected from terminal`);
  }

  sendTerminalOutput(type: 'stdout' | 'stderr' | 'system', data: string) {
    this.server.emit('terminal:output', { type, data });
  }

  sendCompilationLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.server.emit('terminal:output', {
      type: 'compilation',
      data: `${message}`,
    });
  }
}
