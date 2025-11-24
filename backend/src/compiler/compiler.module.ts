import { Module } from '@nestjs/common';
import { CompilerController } from './compiler.controller';
import { CompilerService } from './compiler.service';
import { CompilerGateway } from './compiler.gateway';

@Module({
  controllers: [CompilerController],
  providers: [CompilerService, CompilerGateway],
  exports: [CompilerService],
})
export class CompilerModule {}
