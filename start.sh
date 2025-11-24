#!/bin/bash

# Script de inicio para el compilador PHP

echo "🚀 Iniciando Compilador PHP - IDE Web"
echo "======================================"
echo ""

# Verificar Docker
if ! command -v docker &> /dev/null; then
    echo "❌ Error: Docker no está instalado"
    echo "Por favor instala Docker desde https://www.docker.com/"
    exit 1
fi

if ! command -v docker-compose &> /dev/null; then
    echo "❌ Error: Docker Compose no está instalado"
    echo "Por favor instala Docker Compose"
    exit 1
fi

echo "✅ Docker detectado"
echo ""

# Construir y levantar servicios
echo "📦 Construyendo y levantando servicios..."
docker-compose up --build -d

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Servicios iniciados exitosamente!"
    echo ""
    echo "🌐 Acceso a la aplicación:"
    echo "   - Frontend (IDE): http://localhost:3000"
    echo "   - Backend API:    http://localhost:3001"
    echo "   - Health Check:   http://localhost:3001/api/compiler/health"
    echo ""
    echo "📊 Para ver logs en tiempo real:"
    echo "   docker-compose logs -f"
    echo ""
    echo "🛑 Para detener los servicios:"
    echo "   docker-compose down"
    echo ""
else
    echo "❌ Error al iniciar los servicios"
    echo "Revisa los logs con: docker-compose logs"
    exit 1
fi
