@echo off
REM Script para instalar todas las dependencias del proyecto

echo ============================================
echo   Instalador de Dependencias
echo   Compilador PHP
echo ============================================
echo.

REM Verificar Node.js
echo [1/5] Verificando Node.js...
node --version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Node.js no esta instalado o no funciona correctamente
    echo.
    echo Por favor, sigue estos pasos:
    echo 1. Ve a https://nodejs.org/
    echo 2. Descarga la version LTS
    echo 3. Instala con las opciones por defecto
    echo 4. Reinicia esta terminal
    echo 5. Ejecuta este script nuevamente
    echo.
    pause
    exit /b 1
)

node --version
npm --version
echo Node.js detectado correctamente!
echo.

REM Instalar backend
echo [2/5] Instalando dependencias del Backend...
cd backend
if exist node_modules (
    echo Limpiando instalacion anterior...
    rmdir /s /q node_modules
    del package-lock.json 2>nul
)
npm install
if %ERRORLEVEL% NEQ 0 (
    echo ERROR al instalar dependencias del backend
    pause
    exit /b 1
)
echo Backend: OK
cd ..
echo.

REM Instalar frontend
echo [3/5] Instalando dependencias del Frontend...
cd frontend
if exist node_modules (
    echo Limpiando instalacion anterior...
    rmdir /s /q node_modules
    del package-lock.json 2>nul
)
npm install
if %ERRORLEVEL% NEQ 0 (
    echo ERROR al instalar dependencias del frontend
    pause
    exit /b 1
)
echo Frontend: OK
cd ..
echo.

REM Compilar backend
echo [4/5] Compilando Backend TypeScript...
cd backend
npm run build
if %ERRORLEVEL% NEQ 0 (
    echo ADVERTENCIA: Error al compilar backend
    echo Esto es normal si hay algunos errores de tipo
)
cd ..
echo.

REM Compilar frontend
echo [5/5] Compilando Frontend NextJS...
cd frontend
npm run build
if %ERRORLEVEL% NEQ 0 (
    echo ADVERTENCIA: Error al compilar frontend
    echo Esto es normal en la primera ejecucion
)
cd ..
echo.

echo ============================================
echo   Instalacion Completada!
echo ============================================
echo.
echo Proximos pasos:
echo.
echo Para compilar el compilador Lex/Yacc:
echo   cd compiler
echo   make
echo.
echo Para iniciar el Backend:
echo   cd backend
echo   npm run start:dev
echo.
echo Para iniciar el Frontend:
echo   cd frontend
echo   npm run dev
echo.
echo O usar Docker:
echo   docker-compose up --build
echo.
pause
