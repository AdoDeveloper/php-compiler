import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { NestExpressApplication } from '@nestjs/platform-express';
import { join } from 'path';
import { existsSync } from 'fs';

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);

  // Habilitar CORS
  app.enableCors({
    origin: true,
    credentials: true,
  });

  // Servir archivos estáticos de Next.js en producción
  const frontendStaticPath = join(__dirname, '../../frontend/.next/static');
  const frontendPublicPath = join(__dirname, '../../frontend/public');

  if (existsSync(frontendStaticPath)) {
    console.log('✅ Serving Next.js static files from:', frontendStaticPath);
    app.useStaticAssets(frontendStaticPath, { prefix: '/_next/static' });
  }

  if (existsSync(frontendPublicPath)) {
    console.log('✅ Serving public files from:', frontendPublicPath);
    app.useStaticAssets(frontendPublicPath, { prefix: '/' });
  }

  const port = process.env.PORT || 3001;
  const host = process.env.HOST || '0.0.0.0';
  await app.listen(port, host);

  console.log(`✅ PHP Compiler Backend running on http://${host}:${port}`);
  console.log(`✅ Frontend files will be served by Next.js on separate process`);
}

bootstrap();
