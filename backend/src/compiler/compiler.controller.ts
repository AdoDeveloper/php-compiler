import { Controller, Post, Body, Get, HttpException, HttpStatus } from '@nestjs/common';
import { CompilerService } from './compiler.service';

@Controller('api/compiler')
export class CompilerController {
  constructor(private readonly compilerService: CompilerService) {}

  @Post('compile')
  async compile(@Body('code') code: string, @Body('inputs') inputs?: string[]) {
    if (!code || code.trim().length === 0) {
      throw new HttpException(
        'PHP code cannot be empty',
        HttpStatus.BAD_REQUEST
      );
    }

    try {
      const result = await this.compilerService.compile(code, inputs || []);
      return result;
    } catch (error) {
      throw new HttpException(
        `Compilation error: ${error.message}`,
        HttpStatus.INTERNAL_SERVER_ERROR
      );
    }
  }

  @Get('info')
  async getInfo() {
    return await this.compilerService.getCompilerInfo();
  }

  @Get('health')
  async healthCheck() {
    return {
      status: 'ok',
      timestamp: new Date().toISOString(),
      service: 'php-compiler-backend',
    };
  }
}
