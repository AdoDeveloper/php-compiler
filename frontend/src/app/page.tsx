'use client';

import { useState, useEffect } from 'react';
import CodeEditor from '../components/CodeEditor';
import ExecutionStack from '../components/ExecutionStack';
import SymbolTable from '../components/SymbolTable';
import OutputPanel from '../components/OutputPanel';
import CompilationDetails from '../components/CompilationDetails';
import Terminal from '../components/Terminal';
import { compilerService } from '../services/compilerService';
import { VscPlay, VscClearAll, VscCode, VscCopy, VscCheck, VscChevronDown } from 'react-icons/vsc';
import { FiClock, FiZap, FiGlobe, FiBook } from 'react-icons/fi';
import { useLanguage } from '../contexts/LanguageContext';

const defaultCode = `<?php
// Calculator Example
$a = 10;
$b = 5;
$sum = $a + $b;
$diff = $a - $b;
$mult = $a * $b;
$div = $a / $b;

echo $sum;
echo $diff;
echo $mult;
echo $div;
?>`;

export default function Home() {
  const { language, setLanguage, t } = useLanguage();
  const [code, setCode] = useState(defaultCode);
  const [output, setOutput] = useState('');
  const [fullOutput, setFullOutput] = useState('');
  const [errors, setErrors] = useState('');
  const [warnings, setWarnings] = useState('');
  const [symbolTable, setSymbolTable] = useState('');
  const [executionStack, setExecutionStack] = useState<string[]>([]);
  const [executionTime, setExecutionTime] = useState<number>(0);
  const [isCompiling, setIsCompiling] = useState(false);
  const [activeTab, setActiveTab] = useState<'stack' | 'symbols' | 'details'>('stack');
  const [showExamples, setShowExamples] = useState(false);
  const [copied, setCopied] = useState(false);

  useEffect(() => {
    compilerService.connect();

    compilerService.onCompilationStart((data) => {
      setIsCompiling(true);
      setOutput('Compiling...');
      setErrors('');
      setWarnings('');
      setExecutionStack([]);
      setExecutionTime(0);
    });

    compilerService.onStackUpdate((data) => {
      setExecutionStack((prev) => [...prev, data.entry]);
    });

    compilerService.onCompilationComplete((result) => {
      setIsCompiling(false);
      setOutput(result.output);
      setErrors(result.errors);
      setSymbolTable(result.symbolTable);
      if (result.executionStack) {
        setExecutionStack(result.executionStack);
      }
    });

    compilerService.onCompilationError((data) => {
      setIsCompiling(false);
      setErrors(data.message);
    });

    return () => {
      compilerService.disconnect();
    };
  }, []);

  // Keyboard shortcuts
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      // Ctrl+Enter to compile
      if (e.ctrlKey && e.key === 'Enter') {
        e.preventDefault();
        handleCompile();
      }
      // Ctrl+K to clear
      if (e.ctrlKey && e.key === 'k') {
        e.preventDefault();
        handleClear();
      }
      // Escape to close examples
      if (e.key === 'Escape' && showExamples) {
        setShowExamples(false);
      }
    };

    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, [code, showExamples]);

  // Click outside to close examples dropdown
  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      const target = e.target as HTMLElement;
      if (showExamples && !target.closest('.examples-dropdown')) {
        setShowExamples(false);
      }
    };

    document.addEventListener('click', handleClickOutside);
    return () => document.removeEventListener('click', handleClickOutside);
  }, [showExamples]);

  const handleCompile = async () => {
    const startTime = performance.now();
    setIsCompiling(true);
    setOutput('');
    setFullOutput('');
    setErrors('');
    setWarnings('');
    setSymbolTable('');
    setExecutionStack([]);
    setExecutionTime(0);

    try {
      const result = await compilerService.compile(code, []);

      const endTime = performance.now();
      const timeInMs = endTime - startTime;
      setExecutionTime(timeInMs);

      // Store full output for compilation details
      setFullOutput(result.output);

      // Extract ONLY program output (echo results)
      const outputLines = result.output.split('\n');
      const echoResults: string[] = [];
      let captureOutput = false;

      for (const line of outputLines) {
        // Start capturing after "=== EJECUTANDO PROGRAMA ==="
        if (line.includes('=== EJECUTANDO PROGRAMA ===') || line.includes('=== EXECUTING PROGRAM ===')) {
          captureOutput = true;
          continue;
        }

        // Stop capturing at the post-execution symbol table or any other section
        if (line.includes('=== TABLA DE SIMBOLOS (POST-EJECUCIÓN)') ||
            line.includes('=== SYMBOL TABLE (POST-EXECUTION)')) {
          captureOutput = false;
        }

        // If we're capturing, add lines (including empty ones to preserve formatting)
        if (captureOutput) {
          echoResults.push(line);
        }
      }

      // Build clean output with execution summary
      let cleanOutput = echoResults.join('\n').trim();

      // Add execution summary
      const hasErrors = result.errors && result.errors.length > 0 && !result.errors.includes('Sin errores');
      let summary = '\n\n────────────────────────────────\n';

      if (hasErrors) {
        summary += `❌ Compilation failed\n${result.errors}`;
      } else {
        summary += `✓ Compilation successful\n`;
        summary += `⏱ Execution time: ${timeInMs.toFixed(0)}ms`;
      }

      cleanOutput = cleanOutput + summary;
      setOutput(cleanOutput || 'No output');

      setErrors(hasErrors ? result.errors : '');
      setSymbolTable(result.symbolTable || '');
      setExecutionStack(result.executionStack || []);

    } catch (error: any) {
      const endTime = performance.now();
      setExecutionTime(endTime - startTime);
      setErrors('Connection error: ' + (error.message || 'Could not connect to backend'));
      setOutput('Error: Backend not responding. Please verify the service is running.');
    } finally {
      setIsCompiling(false);
    }
  };

  const handleClear = () => {
    setCode('<?php\n\n?>');
    setOutput('');
    setFullOutput('');
    setErrors('');
    setWarnings('');
    setSymbolTable('');
    setExecutionStack([]);
    setExecutionTime(0);
  };

  const toggleLanguage = () => {
    setLanguage(language === 'en' ? 'es' : 'en');
  };

  const handleCopyOutput = () => {
    navigator.clipboard.writeText(output);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  const exampleCodes = {
    complete: `<?php\n// Complete Example - Structured Programming\n// Variables: string, int, bool\n$name = "Student";\n$score = 85;\n$passed = true;\n\n// String concatenation\necho "Name: " . $name;\necho "\\n";\n\n// Arithmetic operations\n$bonus = 10;\n$total = $score + $bonus;\necho "Score: ";\necho $score;\necho "\\n";\necho "Total with bonus: ";\necho $total;\necho "\\n";\n\n// Decision block (if-else)\nif ($total >= 90) {\n  echo "Grade: A";\n} else {\n  if ($total >= 70) {\n    echo "Grade: B";\n  } else {\n    echo "Grade: C";\n  }\n}\necho "\\n";\n\n// Repetition block (for)\necho "Countdown: ";\nfor ($i = 5; $i > 0; $i--) {\n  echo $i;\n  echo " ";\n}\necho "\\n";\n\n// Boolean variable usage\nif ($passed) {\n  echo "Status: PASSED";\n} else {\n  echo "Status: FAILED";\n}\n?>`,
    variables: `<?php\n// Variables: string, int, bool\n$name = "PHP Compiler";\n$year = 2025;\n$active = true;\n\necho "Name: ";\necho $name;\necho "\\n";\necho "Year: ";\necho $year;\necho "\\n";\necho "Active: ";\nif ($active) {\n  echo "Yes";\n} else {\n  echo "No";\n}\n?>`,
    arithmetic: `<?php\n// Arithmetic Operations\n$a = 20;\n$b = 8;\n\necho "a = ";\necho $a;\necho "\\n";\necho "b = ";\necho $b;\necho "\\n";\n\necho "Sum: ";\necho $a + $b;\necho "\\n";\necho "Difference: ";\necho $a - $b;\necho "\\n";\necho "Product: ";\necho $a * $b;\necho "\\n";\necho "Division: ";\necho $a / $b;\n?>`,
    decision: `<?php\n// Decision Blocks (if-else)\n$temperature = 25;\n\necho "Temperature: ";\necho $temperature;\necho "C\\n";\n\nif ($temperature > 30) {\n  echo "Hot";\n} else {\n  if ($temperature > 20) {\n    echo "Warm";\n  } else {\n    if ($temperature > 10) {\n      echo "Cool";\n    } else {\n      echo "Cold";\n    }\n  }\n}\n?>`,
    forLoop: `<?php\n// For Loop - Repetition\necho "Numbers 0-9: ";\nfor ($i = 0; $i < 10; $i++) {\n  echo $i;\n  echo " ";\n}\necho "\\n";\n\necho "Even numbers: ";\nfor ($j = 0; $j <= 10; $j = $j + 2) {\n  echo $j;\n  echo " ";\n}\n?>`,
    whileLoop: `<?php\n// While Loop - Repetition\n$counter = 1;\n\necho "While loop: ";\nwhile ($counter <= 5) {\n  echo $counter;\n  echo " ";\n  $counter++;\n}\necho "\\n";\n\n$num = 10;\necho "Countdown: ";\nwhile ($num > 0) {\n  echo $num;\n  echo " ";\n  $num--;\n}\n?>`,
    doWhile: `<?php\n// Do-While Loop - Repetition\n$x = 1;\n\necho "Do-While loop:\\n";\ndo {\n  echo "Iteration ";\n  echo $x;\n  echo "\\n";\n  $x++;\n} while ($x <= 5);\n?>`,
  };

  const loadExample = (example: keyof typeof exampleCodes) => {
    setCode(exampleCodes[example]);
    setShowExamples(false);
  };

  return (
    <main className="min-h-screen bg-black text-white">
      {/* Header */}
      <header className="border-b border-gray-800 bg-black/50 backdrop-blur-xl sticky top-0 z-50">
        <div className="max-w-[1400px] mx-auto px-4 sm:px-6 py-3 sm:py-4">
          <div className="flex items-center justify-between gap-2">
            <div className="flex items-center gap-2 sm:gap-3 min-w-0">
              <div className="w-7 h-7 sm:w-8 sm:h-8 bg-white rounded-md flex items-center justify-center flex-shrink-0">
                <VscCode className="text-black text-base sm:text-lg" />
              </div>
              <div className="min-w-0">
                <h1 className="text-base sm:text-xl font-semibold tracking-tight truncate">{t.header.title}</h1>
                <p className="text-[10px] sm:text-xs text-gray-500 hidden sm:block">{t.header.subtitle}</p>
              </div>
            </div>

            <div className="flex items-center gap-2 sm:gap-3 flex-shrink-0">
              <button
                onClick={toggleLanguage}
                className="flex items-center gap-1.5 sm:gap-2 text-[10px] sm:text-xs text-gray-400 hover:text-white border border-gray-800 hover:border-gray-700 px-2 sm:px-3 py-1 sm:py-1.5 rounded-full transition-all"
              >
                <FiGlobe className="text-sm sm:text-base" />
                <span>{language === 'en' ? 'ES' : 'EN'}</span>
              </button>
              <div className="hidden sm:flex items-center gap-2 text-xs text-gray-500 bg-gray-900 px-3 py-1.5 rounded-full">
                <FiZap className="text-green-500" />
                <span>{t.header.ready}</span>
              </div>
            </div>
          </div>
        </div>
      </header>

      <div className="max-w-[1400px] mx-auto px-4 sm:px-6 py-4 sm:py-8">
        {/* Action Bar */}
        <div className="flex flex-col sm:flex-row items-stretch sm:items-center justify-between gap-3 sm:gap-0 mb-4 sm:mb-6">
          <div className="flex flex-wrap items-center gap-2">
            <button
              onClick={handleCompile}
              disabled={isCompiling}
              className={`flex items-center gap-2 px-3 sm:px-4 py-2 rounded-lg text-xs sm:text-sm font-medium transition-all whitespace-nowrap ${
                isCompiling
                  ? 'bg-gray-800 text-gray-500 cursor-not-allowed'
                  : 'bg-white text-black hover:bg-gray-100'
              }`}
              title="Run (Ctrl+Enter)"
            >
              <VscPlay className="text-sm sm:text-base" />
              <span>{isCompiling ? t.buttons.compiling : t.buttons.run}</span>
            </button>
            <button
              onClick={handleClear}
              className="flex items-center gap-2 px-3 sm:px-4 py-2 border border-gray-800 text-gray-400 hover:text-white hover:border-gray-700 rounded-lg text-xs sm:text-sm font-medium transition-all whitespace-nowrap"
              title="Clear (Ctrl+K)"
            >
              <VscClearAll className="text-sm sm:text-base" />
              <span>{t.buttons.clear}</span>
            </button>
            <div className="relative examples-dropdown">
              <button
                onClick={() => setShowExamples(!showExamples)}
                className="flex items-center gap-2 px-3 sm:px-4 py-2 border border-gray-800 text-gray-400 hover:text-white hover:border-gray-700 rounded-lg text-xs sm:text-sm font-medium transition-all whitespace-nowrap"
              >
                <FiBook className="text-sm sm:text-base" />
                <span>{t.buttons.examples}</span>
                <VscChevronDown className={`transition-transform text-xs ${showExamples ? 'rotate-180' : ''}`} />
              </button>
              {showExamples && (
                <div className="absolute top-full mt-2 left-0 bg-gray-900 border border-gray-800 rounded-lg shadow-xl z-50 min-w-[220px] animate-fadeIn">
                  <button
                    onClick={() => loadExample('complete')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors first:rounded-t-lg font-semibold"
                  >
                    ✓ Complete Example
                  </button>
                  <div className="border-t border-gray-700 my-1"></div>
                  <button
                    onClick={() => loadExample('variables')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors"
                  >
                    Variables (3 types)
                  </button>
                  <button
                    onClick={() => loadExample('arithmetic')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors"
                  >
                    Arithmetic Operations
                  </button>
                  <button
                    onClick={() => loadExample('decision')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors"
                  >
                    Decision Blocks (if-else)
                  </button>
                  <button
                    onClick={() => loadExample('forLoop')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors"
                  >
                    For Loop
                  </button>
                  <button
                    onClick={() => loadExample('whileLoop')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors"
                  >
                    While Loop
                  </button>
                  <button
                    onClick={() => loadExample('doWhile')}
                    className="w-full text-left px-4 py-2 text-sm text-gray-300 hover:bg-gray-800 hover:text-white transition-colors last:rounded-b-lg"
                  >
                    Do-While Loop
                  </button>
                </div>
              )}
            </div>
          </div>

          {executionTime > 0 && (
            <div className="flex items-center gap-2 text-sm text-gray-500 animate-fadeIn">
              <FiClock />
              <span>{executionTime.toFixed(0)}ms</span>
            </div>
          )}
        </div>

        {/* Main Grid - Editor and Output on Top */}
        <div className="grid grid-cols-1 lg:grid-cols-2 gap-6 mb-6">
          {/* Left - Code Editor */}
          <div className="border border-gray-800 rounded-xl overflow-hidden bg-gray-950">
            <div className="border-b border-gray-800 px-4 py-3 bg-black/50">
              <h2 className="text-sm font-medium text-gray-400">{t.labels.editor}</h2>
            </div>
            <div className="p-0">
              <CodeEditor code={code} onChange={setCode} />
            </div>
          </div>

          {/* Right - Output */}
          <div className="border border-gray-800 rounded-xl overflow-hidden bg-gray-950">
            <div className="border-b border-gray-800 px-4 py-3 bg-black/50 flex items-center justify-between">
              <h2 className="text-sm font-medium text-gray-400">{t.labels.output}</h2>
              {output && output.trim().length > 0 && (
                <button
                  onClick={handleCopyOutput}
                  className="flex items-center gap-2 px-3 py-1.5 text-xs text-gray-400 hover:text-white border border-gray-800 hover:border-gray-700 rounded-lg transition-all"
                  title="Copy output"
                >
                  {copied ? (
                    <>
                      <VscCheck className="text-green-500" />
                      <span>Copied!</span>
                    </>
                  ) : (
                    <>
                      <VscCopy />
                      <span>Copy</span>
                    </>
                  )}
                </button>
              )}
            </div>
            <div className="p-4 h-[600px] overflow-auto font-mono text-sm">
              <OutputPanel output={output} errors={errors} warnings={warnings} />
            </div>
          </div>
        </div>

        {/* Bottom - Analysis Tabs */}
        <div className="border border-gray-800 rounded-xl overflow-hidden bg-gray-950">
          <div className="border-b border-gray-800 flex bg-black/50">
            <button
              onClick={() => setActiveTab('stack')}
              className={`flex-1 px-3 sm:px-4 py-2 sm:py-3 text-xs sm:text-sm font-medium transition-all whitespace-nowrap ${
                activeTab === 'stack'
                  ? 'text-white border-b-2 border-white'
                  : 'text-gray-500 hover:text-gray-300'
              }`}
            >
              <span className="hidden sm:inline">{t.labels.executionStack}</span>
              <span className="sm:hidden">Stack</span>
              {executionStack.length > 0 && (
                <span className="ml-1 sm:ml-2 text-[10px] sm:text-xs bg-gray-800 px-1.5 sm:px-2 py-0.5 rounded-full">
                  {executionStack.length}
                </span>
              )}
            </button>
            <button
              onClick={() => setActiveTab('symbols')}
              className={`flex-1 px-3 sm:px-4 py-2 sm:py-3 text-xs sm:text-sm font-medium transition-all whitespace-nowrap ${
                activeTab === 'symbols'
                  ? 'text-white border-b-2 border-white'
                  : 'text-gray-500 hover:text-gray-300'
              }`}
            >
              <span className="hidden sm:inline">{t.labels.symbolTable}</span>
              <span className="sm:hidden">Symbols</span>
            </button>
            <button
              onClick={() => setActiveTab('details')}
              className={`flex-1 px-3 sm:px-4 py-2 sm:py-3 text-xs sm:text-sm font-medium transition-all whitespace-nowrap ${
                activeTab === 'details'
                  ? 'text-white border-b-2 border-white'
                  : 'text-gray-500 hover:text-gray-300'
              }`}
            >
              <span className="hidden sm:inline">{t.labels.compilationDetails}</span>
              <span className="sm:hidden">Details</span>
            </button>
          </div>

          <div className="p-3 sm:p-4 min-h-[250px] sm:min-h-[300px] max-h-[350px] sm:max-h-[400px] overflow-auto">
            {activeTab === 'stack' ? (
              <ExecutionStack stack={executionStack} />
            ) : activeTab === 'symbols' ? (
              <SymbolTable table={symbolTable} />
            ) : (
              <CompilationDetails fullOutput={fullOutput} />
            )}
          </div>
        </div>
      </div>

      {/* Footer */}
      <footer className="border-t border-gray-800 mt-12 py-8">
        <div className="max-w-[1400px] mx-auto px-6 text-center text-xs text-gray-600">
          <p>{t.footer}</p>
        </div>
      </footer>

      {/* Terminal (Logs + Interactive) */}
      <Terminal />

      <style jsx>{`
        @keyframes fadeIn {
          from {
            opacity: 0;
            transform: translateY(-4px);
          }
          to {
            opacity: 1;
            transform: translateY(0);
          }
        }

        .animate-fadeIn {
          animation: fadeIn 0.3s ease-out;
        }
      `}</style>
    </main>
  );
}
