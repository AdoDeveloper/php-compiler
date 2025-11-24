import { Module } from '@nestjs/common';
import { CompilationGateway } from './compilation.gateway';
import { CompilerModule } from '../compiler/compiler.module';

@Module({
  imports: [CompilerModule],
  providers: [CompilationGateway],
})
export class WebSocketModule {}
