import { Module } from '@nestjs/common';
import { CompilerModule } from './compiler/compiler.module';
import { WebSocketModule } from './websocket/websocket.module';
import { TerminalModule } from './terminal/terminal.module';

@Module({
  imports: [CompilerModule, WebSocketModule, TerminalModule],
})
export class AppModule {}
