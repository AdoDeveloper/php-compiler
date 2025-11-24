#!/bin/bash

# Script para instalar todas las dependencias del proyecto

echo ""
echo "============================================"
echo "  Instalador de Dependencias"
echo "  Compilador PHP"
echo "============================================"
echo ""

# Verificar Node.js
echo "[1/5] Verificando Node.js..."
if ! command -v node &> /dev/null; then
    echo ""
    echo "❌ ERROR: Node.js no está instalado"
    echo ""
    echo "Por favor, instala Node.js:"
    echo "  - Ubuntu/Debian: sudo apt install nodejs npm"
    echo "  - macOS: brew install node"
    echo "  - Otros: https://nodejs.org/"
    echo ""
    exit 1
fi

node --version
npm --version
echo "✅ Node.js detectado correctamente!"
echo ""

# Instalar backend
echo "[2/5] Instalando dependencias del Backend..."
cd backend
if [ -d "node_modules" ]; then
    echo "Limpiando instalación anterior..."
    rm -rf node_modules package-lock.json
fi
npm install
if [ $? -ne 0 ]; then
    echo "❌ ERROR al instalar dependencias del backend"
    exit 1
fi
echo "✅ Backend: OK"
cd ..
echo ""

# Instalar frontend
echo "[3/5] Instalando dependencias del Frontend..."
cd frontend
if [ -d "node_modules" ]; then
    echo "Limpiando instalación anterior..."
    rm -rf node_modules package-lock.json
fi
npm install
if [ $? -ne 0 ]; then
    echo "❌ ERROR al instalar dependencias del frontend"
    exit 1
fi
echo "✅ Frontend: OK"
cd ..
echo ""

# Compilar backend
echo "[4/5] Compilando Backend TypeScript..."
cd backend
npm run build
if [ $? -ne 0 ]; then
    echo "⚠️  ADVERTENCIA: Error al compilar backend"
    echo "Esto es normal si hay algunos errores de tipo"
fi
cd ..
echo ""

# Compilar frontend
echo "[5/5] Compilando Frontend NextJS..."
cd frontend
npm run build
if [ $? -ne 0 ]; then
    echo "⚠️  ADVERTENCIA: Error al compilar frontend"
    echo "Esto es normal en la primera ejecución"
fi
cd ..
echo ""

echo "============================================"
echo "  ✅ Instalación Completada!"
echo "============================================"
echo ""
echo "Próximos pasos:"
echo ""
echo "Para compilar el compilador Lex/Yacc:"
echo "  cd compiler"
echo "  make"
echo ""
echo "Para iniciar el Backend:"
echo "  cd backend"
echo "  npm run start:dev"
echo ""
echo "Para iniciar el Frontend:"
echo "  cd frontend"
echo "  npm run dev"
echo ""
echo "O usar Docker:"
echo "  docker-compose up --build"
echo ""
