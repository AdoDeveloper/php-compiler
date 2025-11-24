import {
  WebSocketGateway,
  WebSocketServer,
  SubscribeMessage,
  OnGatewayConnection,
  OnGatewayDisconnect,
  MessageBody,
  ConnectedSocket,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import * as pty from 'node-pty';

interface TerminalSession {
  process: pty.IPty;
  cwd: string;
}

@WebSocketGateway({
  cors: {
    origin: ['http://localhost:3000', 'http://localhost:3002'],
    credentials: true,
  },
})
export class TerminalGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer()
  server: Server;

  private sessions = new Map<string, TerminalSession>();

  handleConnection(client: Socket) {
    console.log(`Interactive terminal client connected: ${client.id}`);

    // Create a new PTY session for this client with bash
    const ptyProcess = pty.spawn('/bin/bash', [], {
      name: 'xterm-256color',
      cols: 80,
      rows: 24,
      cwd: '/compiler',
      env: {
        ...process.env,
        TERM: 'xterm-256color',
        COLORTERM: 'truecolor',
        PS1: '\\[\\033[1;32m\\]\\u@php-compiler\\[\\033[0m\\]:\\[\\033[1;34m\\]\\w\\[\\033[0m\\]$ ',
      },
    });

    const session: TerminalSession = {
      process: ptyProcess,
      cwd: '/compiler',
    };

    this.sessions.set(client.id, session);

    // Send all output to client
    ptyProcess.onData((data: string) => {
      client.emit('terminal:data', data);
    });

    // Handle process exit
    ptyProcess.onExit((exitInfo) => {
      client.emit('terminal:exit', { code: exitInfo.exitCode });
      this.sessions.delete(client.id);
    });

    // Send welcome message
    setTimeout(() => {
      ptyProcess.write('clear\r');
      setTimeout(() => {
        ptyProcess.write('echo "🚀 Interactive Terminal Ready - Type your commands below"\r');
        ptyProcess.write('echo "📁 Current directory: $(pwd)"\r');
        ptyProcess.write('echo "💡 Try: ls, cat php.l, nano test.php, ./phpcompiler file.php"\r');
        ptyProcess.write('echo ""\r');
      }, 100);
    }, 100);
  }

  handleDisconnect(client: Socket) {
    console.log(`Interactive terminal client disconnected: ${client.id}`);

    const session = this.sessions.get(client.id);
    if (session) {
      session.process.kill();
      this.sessions.delete(client.id);
    }
  }

  @SubscribeMessage('terminal:input')
  handleInput(
    @MessageBody() data: string,
    @ConnectedSocket() client: Socket,
  ) {
    const session = this.sessions.get(client.id);
    if (session && session.process) {
      session.process.write(data);
    }
  }

  @SubscribeMessage('terminal:resize')
  handleResize(
    @MessageBody() size: { cols: number; rows: number },
    @ConnectedSocket() client: Socket,
  ) {
    const session = this.sessions.get(client.id);
    if (session && session.process) {
      session.process.resize(size.cols, size.rows);
      console.log(`Terminal resized to: ${size.cols}x${size.rows}`);
    }
  }

}
