@echo off
REM Script de inicio para Windows

echo.
echo ============================================
echo   Compilador PHP - IDE Web
echo ============================================
echo.

REM Verificar Docker
where docker >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: Docker no esta instalado
    echo Por favor instala Docker Desktop desde https://www.docker.com/
    pause
    exit /b 1
)

where docker-compose >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: Docker Compose no esta instalado
    pause
    exit /b 1
)

echo Docker detectado correctamente
echo.

REM Construir y levantar servicios
echo Construyendo y levantando servicios...
echo.
docker-compose up --build -d

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ============================================
    echo   Servicios iniciados exitosamente!
    echo ============================================
    echo.
    echo Acceso a la aplicacion:
    echo   - Frontend IDE:  http://localhost:3000
    echo   - Backend API:   http://localhost:3001
    echo   - Health Check:  http://localhost:3001/api/compiler/health
    echo.
    echo Para ver logs en tiempo real:
    echo   docker-compose logs -f
    echo.
    echo Para detener los servicios:
    echo   docker-compose down
    echo.
    echo Presiona Ctrl+C para salir de este script
    echo Los servicios seguiran corriendo en segundo plano
    echo.
    pause
) else (
    echo.
    echo Error al iniciar los servicios
    echo Revisa los logs con: docker-compose logs
    pause
    exit /b 1
)
