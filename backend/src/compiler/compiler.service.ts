import { Injectable } from '@nestjs/common';
import { exec } from 'child_process';
import { promisify } from 'util';
import * as fs from 'fs/promises';
import * as path from 'path';
import { CompilerGateway } from './compiler.gateway';

const execAsync = promisify(exec);

export interface CompilationResult {
  success: boolean;
  output: string;
  errors: string;
  symbolTable: string;
  executionStack: string[];
  generatedCode?: string;
}

@Injectable()
export class CompilerService {
  private readonly compilerPath = '/compiler';
  private readonly tempDir = '/tmp/php-compiler';
  private gateway: CompilerGateway | null = null;

  constructor() {
    this.initTempDir();
  }

  setGateway(gateway: CompilerGateway) {
    this.gateway = gateway;
  }

  private async initTempDir() {
    try {
      await fs.mkdir(this.tempDir, { recursive: true });
    } catch (error) {
      console.error('Error creando directorio temporal:', error);
    }
  }

  async compile(phpCode: string, inputs: string[] = []): Promise<CompilationResult> {
    const timestamp = Date.now();
    const inputFile = path.join(this.tempDir, `input_${timestamp}.php`);
    const outputFile = path.join(this.tempDir, `output_${timestamp}.txt`);
    const inputDataFile = path.join(this.tempDir, `inputdata_${timestamp}.txt`);

    try {
      // Log to terminal
      if (this.gateway) {
        this.gateway.sendCompilationLog('Starting compilation...');
      }

      // Write PHP code to temporary file
      await fs.writeFile(inputFile, phpCode);

      if (this.gateway) {
        this.gateway.sendCompilationLog(`Created temporary file: ${inputFile}`);
      }

      // Write user inputs to file if provided
      if (inputs.length > 0) {
        await fs.writeFile(inputDataFile, inputs.join('\n'));
        if (this.gateway) {
          this.gateway.sendCompilationLog(`Added ${inputs.length} input values`);
        }
      }

      // Execute compiler
      const compilerExecutable = path.join(this.compilerPath, 'phpcompiler');
      const inputRedirect = inputs.length > 0 ? ` < ${inputDataFile}` : '';
      const command = `${compilerExecutable} ${inputFile}${inputRedirect} > ${outputFile} 2>&1`;

      if (this.gateway) {
        this.gateway.sendCompilationLog(`Executing: ${command}`);
      }

      let stdout = '';
      let stderr = '';
      let execSuccess = true;

      try {
        const result = await execAsync(command, {
          cwd: this.compilerPath,
          timeout: 30000, // 30 seconds timeout
        });
        stdout = result.stdout;
        stderr = result.stderr;

        if (this.gateway) {
          this.gateway.sendCompilationLog('Compilation process completed');
        }
      } catch (execError: any) {
        execSuccess = false;
        stderr = execError.stderr || '';
        stdout = execError.stdout || '';

        if (this.gateway) {
          this.gateway.sendCompilationLog(`Error during execution: ${execError.message}`);
          if (stderr) {
            this.gateway.sendCompilationLog(`STDERR: ${stderr}`);
          }
          if (stdout) {
            this.gateway.sendCompilationLog(`STDOUT: ${stdout}`);
          }
        }
      }

      // Leer output del compilador
      let output = '';
      try {
        output = await fs.readFile(outputFile, 'utf-8');
        if (this.gateway && output) {
          this.gateway.sendCompilationLog(`Read output file (${output.length} bytes)`);
        }
      } catch (readError: any) {
        output = stdout;
        if (this.gateway) {
          this.gateway.sendCompilationLog(`Could not read output file: ${readError.message}`);
          if (stdout) {
            this.gateway.sendCompilationLog(`Using stdout instead (${stdout.length} bytes)`);
          }
        }
      }

      // Parsear output para extraer tabla de símbolos y pila
      const symbolTable = this.extractSymbolTable(output);
      const executionStack = this.extractExecutionStack(output);

      // Leer código C generado si existe
      let generatedCode = '';
      try {
        const cCodePath = path.join(this.compilerPath, 'output.c');
        generatedCode = await fs.readFile(cCodePath, 'utf-8');
      } catch {
        // No hay código generado
      }

      // Extraer errores del output
      const errorMessages = this.extractErrors(output);
      const hasErrors = stderr.length > 0 || errorMessages.length > 0 || output.includes('ERROR');

      // Clean up temporary files
      await this.cleanup(inputFile, outputFile, inputDataFile);

      return {
        success: !hasErrors,
        output: output,
        errors: errorMessages.length > 0 ? errorMessages : stderr,
        symbolTable: symbolTable,
        executionStack: executionStack,
        generatedCode: generatedCode,
      };
    } catch (error) {
      console.error('Compilation error:', error);

      // Clean up temporary files on error
      await this.cleanup(inputFile, outputFile, inputDataFile);

      return {
        success: false,
        output: '',
        errors: `Internal compiler error: ${error.message}`,
        symbolTable: '',
        executionStack: [],
      };
    }
  }

  private extractSymbolTable(output: string): string {
    // Try to get the post-execution symbol table first
    const postExecMarker = '=== TABLA DE SIMBOLOS (POST-EJECUCIÓN) ===';
    let startIndex = output.indexOf(postExecMarker);

    // If not found, get the regular symbol table
    if (startIndex === -1) {
      const startMarker = '=== TABLA DE SIMBOLOS ===';
      startIndex = output.indexOf(startMarker);
      if (startIndex === -1) return '';
    }

    const endMarker = '=========================';
    const endIndex = output.indexOf(endMarker, startIndex + endMarker.length);
    if (endIndex === -1) return '';

    return output.substring(startIndex, endIndex + endMarker.length);
  }

  private extractExecutionStack(output: string): string[] {
    const stackMarker = '=== PILA DE EJECUCION ===';
    const endMarker = '=========================';

    const startIndex = output.indexOf(stackMarker);
    if (startIndex === -1) return [];

    const endIndex = output.indexOf(endMarker, startIndex + stackMarker.length);
    if (endIndex === -1) return [];

    const stackSection = output.substring(
      startIndex + stackMarker.length,
      endIndex
    );

    return stackSection
      .split('\n')
      .map((line) => line.trim())
      .filter((line) => line.length > 0 && line !== '(vacía)');
  }

  private extractErrors(output: string): string {
    // Buscar sección de errores sintácticos
    const errorStart = output.indexOf('*** ERROR SINTACTICO ***');
    if (errorStart === -1) {
      // Buscar errores semánticos
      if (output.includes('ERROR') || output.includes('error')) {
        const lines = output.split('\n');
        const errorLines = lines.filter(line =>
          line.includes('ERROR') ||
          line.includes('error') ||
          line.includes('Total de errores:')
        );
        return errorLines.join('\n');
      }
      return '';
    }

    const errorEnd = output.indexOf('Total de errores:', errorStart);
    if (errorEnd === -1) return '';

    // Encontrar el final de la línea de "Total de errores"
    const lineEnd = output.indexOf('\n', errorEnd);
    const errorSection = output.substring(errorStart, lineEnd > 0 ? lineEnd : output.length);

    return errorSection.trim();
  }

  private async cleanup(...files: string[]) {
    for (const file of files) {
      try {
        await fs.unlink(file);
      } catch {
        // Ignorar errores de limpieza
      }
    }
  }

  async getCompilerInfo(): Promise<{ version: string; features: string[] }> {
    return {
      version: '1.0.0',
      features: [
        'Variables (int, string, bool)',
        'Arithmetic operations (+, -, *, /)',
        'Logical operations (&&, ||, !)',
        'Comparison operators (==, !=, <, >, <=, >=)',
        'Decision blocks (if, else, elseif)',
        'Iteration blocks (while, for, do-while)',
        'Real-time execution stack',
        'Symbol table with types and scopes',
        'C code generation',
        'Detailed error reporting',
      ],
    };
  }
}
