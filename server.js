const http = require('http');
const httpProxy = require('http-proxy');
const { spawn } = require('child_process');

const PORT = process.env.PORT || 10000;
const BACKEND_PORT = 3001;
const FRONTEND_PORT = 3000;

console.log('=========================================');
console.log('🚀 Starting Unified PHP Compiler Server');
console.log('=========================================');
console.log(`📦 Main server will listen on port ${PORT}`);

// Crear proxy
const proxy = httpProxy.createProxyServer({});

// Manejar errores del proxy globalmente para evitar crashes
proxy.on('error', (err, req, res) => {
  console.error('Global proxy error:', err.message);
  if (res && !res.headersSent) {
    res.writeHead(502, { 'Content-Type': 'text/plain' });
    res.end('Bad Gateway');
  }
});

// Iniciar backend en localhost solo (no en 0.0.0.0 para evitar que Render lo detecte)
console.log(`🔧 Starting backend on port ${BACKEND_PORT}...`);
const backend = spawn('node', ['dist/main.js'], {
  cwd: '/app/backend',
  env: { ...process.env, PORT: BACKEND_PORT, HOST: '127.0.0.1', NODE_ENV: 'production' },
  stdio: 'inherit'
});

// Variable para rastrear si estamos apagando intencionalmente
let isShuttingDown = false;

// Manejar crash del backend
backend.on('exit', (code, signal) => {
  if (isShuttingDown) {
    console.log(`Backend process exited during shutdown (code: ${code}, signal: ${signal})`);
    return;
  }

  // Solo considerar como crash si el código no es 0 y no es SIGTERM/SIGINT
  if (code !== 0 && code !== null && signal !== 'SIGTERM' && signal !== 'SIGINT') {
    console.error(`❌ Backend process crashed with code ${code} and signal ${signal}`);
    process.exit(1);
  } else {
    console.log(`Backend process exited gracefully (code: ${code}, signal: ${signal})`);
  }
});

// Iniciar frontend en localhost solo (no en 0.0.0.0 para evitar que Render lo detecte)
console.log(`🔧 Starting frontend on port ${FRONTEND_PORT}...`);
const frontend = spawn('npx', ['next', 'start', '-H', '127.0.0.1', '-p', FRONTEND_PORT], {
  cwd: '/app/frontend',
  env: { ...process.env, PORT: FRONTEND_PORT, NODE_ENV: 'production' },
  stdio: 'inherit'
});

// Manejar crash del frontend
frontend.on('exit', (code, signal) => {
  if (isShuttingDown) {
    console.log(`Frontend process exited during shutdown (code: ${code}, signal: ${signal})`);
    return;
  }

  // Solo considerar como crash si el código no es 0 y no es SIGTERM/SIGINT
  if (code !== 0 && code !== null && signal !== 'SIGTERM' && signal !== 'SIGINT') {
    console.error(`❌ Frontend process crashed with code ${code} and signal ${signal}`);
    process.exit(1);
  } else {
    console.log(`Frontend process exited gracefully (code: ${code}, signal: ${signal})`);
  }
});

// Función para verificar si un servicio está listo
function checkService(port, path = '/') {
  return new Promise((resolve) => {
    http.get(`http://localhost:${port}${path}`, (res) => {
      resolve(res.statusCode >= 200 && res.statusCode < 500);
    }).on('error', () => {
      resolve(false);
    });
  });
}

// Estado de los servicios
let servicesReady = false;
let backendReady = false;
let frontendReady = false;

// Crear servidor HTTP inmediatamente
const server = http.createServer((req, res) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);

  // Health check siempre responde 200 directamente (no hacer proxy)
  if (req.url === '/api/health' || req.url.startsWith('/api/health?') || req.url === '/api/compiler/health') {
    console.log('Health check request received');
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({
      status: 'ok',
      servicesReady,
      backendReady,
      frontendReady,
      timestamp: new Date().toISOString()
    }));
    return;
  }

  // Si los servicios no están listos, devolver 503 para otras rutas
  if (!servicesReady) {
    res.writeHead(503, { 'Content-Type': 'text/plain' });
    res.end('Service Unavailable - Services are starting up...');
    return;
  }

  // Si la request es para /api o /socket.io, proxy al backend
  if (req.url.startsWith('/api') || req.url.startsWith('/socket.io')) {
    proxy.web(req, res, { target: `http://localhost:${BACKEND_PORT}` }, (err) => {
      if (err) {
        console.error('Proxy error:', err);
        if (!res.headersSent) {
          res.writeHead(502);
          res.end('Bad Gateway');
        }
      }
    });
  } else {
    // Todo lo demás va al frontend Next.js
    proxy.web(req, res, { target: `http://localhost:${FRONTEND_PORT}` }, (err) => {
      if (err) {
        console.error('Proxy error:', err);
        if (!res.headersSent) {
          res.writeHead(502);
          res.end('Bad Gateway');
        }
      }
    });
  }
});

// Manejar WebSocket upgrades
server.on('upgrade', (req, socket, head) => {
  if (!servicesReady) {
    socket.destroy();
    return;
  }

  if (req.url.startsWith('/socket.io')) {
    proxy.ws(req, socket, head, { target: `http://localhost:${BACKEND_PORT}` });
  } else {
    proxy.ws(req, socket, head, { target: `http://localhost:${FRONTEND_PORT}` });
  }
});

// Iniciar el servidor inmediatamente
server.listen(PORT, '0.0.0.0', () => {
  console.log('=========================================');
  console.log(`✅ Server listening on http://0.0.0.0:${PORT}`);
  console.log('⏳ Waiting for backend and frontend to be ready...');
  console.log('=========================================');
});

// Esperar a que los servicios estén listos en segundo plano
async function waitForServices() {
  const maxRetries = 30;
  const retryInterval = 2000;

  for (let i = 0; i < maxRetries; i++) {
    if (!backendReady) {
      backendReady = await checkService(BACKEND_PORT, '/api/health');
      if (backendReady) {
        console.log(`✅ Backend is ready on port ${BACKEND_PORT}`);
      }
    }

    if (!frontendReady) {
      frontendReady = await checkService(FRONTEND_PORT, '/');
      if (frontendReady) {
        console.log(`✅ Frontend is ready on port ${FRONTEND_PORT}`);
      }
    }

    if (backendReady && frontendReady) {
      servicesReady = true;
      console.log('=========================================');
      console.log('✅ All services ready - Proxy is now active');
      console.log(`✅ Backend proxied from port ${BACKEND_PORT}`);
      console.log(`✅ Frontend proxied from port ${FRONTEND_PORT}`);
      console.log('=========================================');
      break;
    }

    if (i < maxRetries - 1) {
      await new Promise(resolve => setTimeout(resolve, retryInterval));
    }
  }

  if (!servicesReady) {
    console.warn('⚠️  Services not fully ready after timeout');
    console.warn(`   Backend ready: ${backendReady}, Frontend ready: ${frontendReady}`);
  }
}

// Iniciar el proceso de espera en segundo plano
waitForServices();

// Cleanup en exit
function shutdown() {
  if (isShuttingDown) {
    return; // Ya estamos apagando, no hacer nada
  }

  isShuttingDown = true;
  console.log('Shutting down gracefully...');

  try {
    backend.kill('SIGTERM');
    frontend.kill('SIGTERM');
  } catch (err) {
    console.error('Error killing processes:', err);
  }

  setTimeout(() => {
    console.log('Force killing processes...');
    try {
      backend.kill('SIGKILL');
      frontend.kill('SIGKILL');
    } catch (err) {
      // Ignore errors
    }
    process.exit(0);
  }, 5000);
}

process.on('SIGTERM', () => {
  console.log('⚠️  Received SIGTERM signal');
  console.log('Stack trace:', new Error().stack);
  shutdown();
});
process.on('SIGINT', () => {
  console.log('⚠️  Received SIGINT signal');
  shutdown();
});
