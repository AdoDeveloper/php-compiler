#!/bin/sh

echo "========================================="
echo "🚀 Starting PHP Compiler Application"
echo "========================================="

# Configurar variables de entorno basadas en PORT de Render
export PORT=${PORT:-10000}
export NODE_ENV=production

echo "📦 PORT: $PORT"

# Verificar que el compilador esté disponible
if [ -f /compiler/phpcompiler ]; then
    echo "✅ PHP Compiler found at /compiler/phpcompiler"
else
    echo "❌ ERROR: PHP Compiler not found!"
    exit 1
fi

# Iniciar servidor de integración que maneja todo
cd /app
exec node server.js
