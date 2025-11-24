# 🚀 Compilador PHP - Programación Estructurada

Compilador completo para PHP con programación estructurada, implementado con **Lex/Yacc** (C), backend en **NestJS**, frontend en **Next.js**, completamente dockerizado y desplegable en Render.

---

## 📋 Características

### ✅ Tipos de Datos
- **Enteros (int)**: Números enteros
- **Cadenas (string)**: Texto entre comillas
- **Booleanos (bool)**: true/false

### ✅ Operaciones Aritméticas
- Suma (+), Resta (-), Multiplicación (*), División (/)
- Incremento (++), Decremento (--)
- Asignación compuesta (+=, -=, *=, /=)

### ✅ Operadores de Comparación y Lógicos
- Comparación: ==, !=, <, >, <=, >=
- Lógicos: && (AND), || (OR), ! (NOT)

### ✅ Bloques de Decisión
- if, if-else, condiciones anidadas

### ✅ Bloques de Repetición
- while, for, do-while
- break, continue

### ✅ Características Avanzadas
- **AST (Abstract Syntax Tree)**: Ejecución en dos fases (parse → execute)
- **Tabla de símbolos**: Variables con tipos, valores y ámbitos
- **Pila de ejecución**: Visualización de operaciones en tiempo real con niveles de anidamiento
- **Terminal interactiva**: Acceso a bash del contenedor con autenticación
- **Detección inteligente de saltos de línea**: Distingue entre echo de valores y saltos de línea
- **Mensajes de error detallados**: Con número de línea
- **Concatenación de strings**: Con operador `.`
- **Escape sequences**: \n, \t, \r, \\, \"
- **Diseño responsive**: Optimizado para desktop y móviles

---

## 🏗️ Arquitectura

```
┌─────────────────────────────────────────┐
│         Usuario (Navegador)             │
│      http://localhost:3002              │
└─────────────────┬───────────────────────┘
                  │
        ┌─────────▼──────────┐
        │  Frontend (Next.js) │
        │  - Monaco Editor    │
        │  - Socket.io Client │
        └─────────┬───────────┘
                  │ HTTP/WebSocket
        ┌─────────▼───────────┐
        │  Backend (NestJS)   │
        │  - REST API         │
        │  - Socket.io Server │
        └─────────┬───────────┘
                  │ exec()
        ┌─────────▼───────────┐
        │  Compiler (C)       │
        │  - Bison (php.y)    │
        │  - Flex (php.l)     │
        │  - AST Interpreter  │
        │  - Symbol Table     │
        └─────────────────────┘
```

### Estructura del Proyecto

```
php-compiler/
├── compiler/           # Compilador Lex/Yacc
│   ├── php.l          # Analizador léxico (Flex)
│   ├── php.y          # Analizador sintáctico (Bison)
│   ├── tabsim.h/c     # Tabla de símbolos + AST
│   ├── Makefile
│   └── ejemplos/      # Archivos de ejemplo PHP
├── backend/           # Backend NestJS
│   └── src/
│       ├── compiler/  # Servicio de compilación
│       └── websocket/ # Comunicación en tiempo real
├── frontend/          # Frontend Next.js
│   └── src/
│       ├── app/       # Páginas
│       ├── components/# Componentes React
│       └── services/  # Cliente API
├── docker/            # Dockerfiles
│   ├── Dockerfile.compiler
│   ├── Dockerfile.backend
│   ├── Dockerfile.frontend
│   └── Dockerfile.deploy  # Para Render
└── docker-compose.yml
```

---

## 🚀 Instalación y Uso

### Prerequisitos
- Docker y Docker Compose
- Git

### Opción 1: Docker (Recomendado)

```bash
# 1. Clonar o navegar al directorio
cd php-compiler

# 2. Construir y levantar servicios
docker-compose up --build

# 3. Acceder a la aplicación
# Frontend: http://localhost:3002
# Backend:  http://localhost:3001
```

### Opción 2: Manual

#### Compilador
```bash
cd compiler
make clean && make

# Ejecutar con archivo de ejemplo
./phpcompiler ejemplos/ejemplo1_variables.php
```

#### Backend
```bash
cd backend
npm install
npm run build
npm run start:prod
```

#### Frontend
```bash
cd frontend
npm install
npm run build
npm start
```

---

## 📝 Ejemplos de Código

### Ejemplo Completo - Programación Estructurada

```php
<?php
// Variables: string, int, bool
$name = "Student";
$score = 85;
$passed = true;

// Concatenación de strings
echo "Name: " . $name;
echo "\n";

// Operaciones aritméticas
$bonus = 10;
$total = $score + $bonus;
echo "Score: ";
echo $score;
echo "\n";
echo "Total with bonus: ";
echo $total;
echo "\n";

// Bloque de decisión (if-else)
if ($total >= 90) {
  echo "Grade: A";
} else {
  if ($total >= 70) {
    echo "Grade: B";
  } else {
    echo "Grade: C";
  }
}
echo "\n";

// Bloque de repetición (for)
echo "Countdown: ";
for ($i = 5; $i > 0; $i--) {
  echo $i;
  echo " ";
}
echo "\n";

// Uso de variable booleana
if ($passed) {
  echo "Status: PASSED";
} else {
  echo "Status: FAILED";
}
?>
```

### Ejemplo - Bucles

```php
<?php
// While
$counter = 1;
echo "While loop: ";
while ($counter <= 5) {
  echo $counter;
  echo " ";
  $counter++;
}
echo "\n";

// For
echo "Numbers 0-9: ";
for ($i = 0; $i < 10; $i++) {
  echo $i;
  echo " ";
}
echo "\n";

// Do-While
$x = 1;
echo "Do-While loop:\n";
do {
  echo "Iteration ";
  echo $x;
  echo "\n";
  $x++;
} while ($x <= 5);
?>
```

---

## 🔧 API del Backend

### POST /api/compiler/compile
Compila código PHP y retorna resultados.

**Request:**
```json
{
  "code": "<?php $x = 10; echo $x; ?>"
}
```

**Response:**
```json
{
  "success": true,
  "output": "10",
  "errors": "",
  "symbolTable": "=== TABLA DE SIMBOLOS ===\n$x | int | 10 | Si | 0",
  "executionStack": [
    "[3] ECHO (línea 1): 10",
    "[2] ASIGNACION (línea 1): $x = 10",
    "[1] DECLARACION (línea 1): Variable $x"
  ]
}
```

### GET /api/compiler/health
Verifica estado del servicio.

---

## 🌐 WebSocket Events

- `compile`: Enviar código para compilar
- `compilation:start`: Notificación de inicio
- `stack:update`: Actualización de pila en tiempo real
- `compilation:complete`: Compilación completada
- `compilation:error`: Error durante compilación

---

## 🐛 Manejo de Errores

### Errores Sintácticos

El parser Bison detecta errores cuando encuentra tokens inesperados:

```php
<?php
echo $x
// Error: syntax error en línea 2, token '}'
// Causa: falta ';' al final de la línea 1
?>
```

**Por qué el error apunta a la línea siguiente:**
Los parsers shift-reduce (como Bison) no detectan el error hasta que encuentran un token que no encaja. En este caso, el `}` no es válido después de una sentencia `echo` incompleta.

### Errores de Variables

```php
<?php
echo $noDeclarada;  // Error: Variable no declarada
?>
```

### Errores Semánticos

```php
<?php
$x = 10;
$y = "texto";
$z = $x + $y;  // Error: tipos incompatibles en suma
?>
```

---

## 📊 Tabla de Símbolos

Rastrea información de cada variable:

```
=== TABLA DE SIMBOLOS (POST-EJECUCIÓN) ===
Nombre    Tipo     Valor    Inicializado    Scope
----------------------------------------------------
$total    int      95       Si              0
$bonus    int      10       Si              0
$score    int      85       Si              0
$name     string   Student  Si              0
```

---

## 🔄 Pila de Ejecución

Muestra operaciones en tiempo real:

```
=== PILA DE EJECUCION ===
[5] ECHO (línea 10): 95
[4] SUMA (línea 9): 85 + 10
[3] ASIGNACION (línea 9): $total = 95
[2] ASIGNACION (línea 8): $bonus = 10
[1] ASIGNACION (línea 7): $score = 85
```

---

## 🚢 Deployment en Render

### Despliegue Completo (Frontend + Backend + Compiler)

El proyecto incluye configuración para desplegar todo el stack en un solo servicio gratuito de Render.

#### Pasos:

1. **Subir a GitHub:**
```bash
git add .
git commit -m "Ready for deployment"
git push origin main
```

2. **En Render.com:**
   - New → Web Service
   - Connect GitHub repository
   - Render detectará `render.yaml` automáticamente
   - Click "Create Web Service"

3. **Esperar 5-10 minutos** mientras construye

4. **Acceder** a tu app en la URL que Render te proporcione (ej: `https://tu-app.onrender.com`)

#### Archivos de configuración:

- `render.yaml` - Configuración de Render
- `docker/Dockerfile.deploy` - Dockerfile multi-stage optimizado
- `docker/nginx.conf` - Reverse proxy
- `docker/supervisord.conf` - Gestor de procesos

#### Limitaciones del plan gratuito:

| Característica | Límite |
|---------------|--------|
| RAM | 512 MB |
| Horas activas | 750 horas/mes |
| Auto-sleep | Después de 15 min inactividad |
| Cold start | ~30 segundos |
| HTTPS | Incluido gratis |

---

## 🛠️ Comandos Útiles

### Docker

```bash
# Levantar servicios
docker-compose up

# Reconstruir
docker-compose up --build

# Ver logs
docker-compose logs -f

# Detener
docker-compose down

# Limpiar todo
docker-compose down -v
```

### Compilador

```bash
# Compilar
cd compiler && make

# Limpiar
make clean

# Ejecutar con archivo de ejemplo
./phpcompiler ejemplos/ejemplo1_variables.php

# O ejecutar código directamente (el compilador leerá desde stdin)
./phpcompiler
```

---

## 📚 Implementación Técnica

### Analizador Léxico (Flex - php.l)

Reconoce:
- Palabras reservadas: if, while, for, echo, etc.
- Variables: `$variable`
- Números: `[0-9]+`
- Strings: `"..."` o `'...'` con escape sequences
- Operadores: +, -, *, /, ==, !=, <, >, etc.
- Comentarios: `//` y `/* */`

### Analizador Sintáctico (Bison - php.y)

- Gramática LR(1) para PHP estructurado
- Construcción de AST (Abstract Syntax Tree)
- Ejecución en dos fases:
  1. **Parse**: Construye AST
  2. **Execute**: Interpreta AST

### Tabla de Símbolos (tabsim.c)

Estructura:
```c
typedef struct _simbolo {
    char nombre[64];
    TipoDato tipo;        // int, string, bool
    ValorDato valor;      // Unión de tipos
    int scope;            // Nivel de anidamiento
    int inicializado;
    int linea;
    struct _simbolo *sig;
} simbolo;
```

### AST Interpreter

15 tipos de nodos AST:
- Literales: número, string, bool, variable
- Operadores: binarios, unarios
- Sentencias: asignación, echo, if, while, for, do-while
- Expresiones: aritméticas, lógicas, comparación
- Concatenación de strings

---

## ⚡ Características Clave

### ✅ Ejecución Correcta de Bucles

```php
for ($i = 0; $i < 10; $i++) {
  echo $i;  // Output: 0123456789 ✓
}
```

### ✅ Echo sin Saltos de Línea Automáticos

```php
echo "Hello";  // Output: Hello (sin \n)
echo "World\n"; // Output: World con salto de línea
```

### ✅ Concatenación de Strings

```php
$name = "Juan";
echo "Hola " . $name;  // Output: Hola Juan
```

### ✅ Coerción de Tipos

```php
$x = 10;
echo "Valor: " . $x;  // Convierte int a string automáticamente
```

---

## 🎨 Interfaz de Usuario

### Características del Frontend:

- **Editor Monaco**: Syntax highlighting para PHP con detección automática de mobile
- **Diseño 100% Responsive**:
  - Optimizado para desktop, tablet y móviles
  - Editor adaptable (sin minimap en mobile)
  - Botones con texto visible en todos los tamaños
  - Sin scroll horizontal no deseado
- **Ejemplos integrados**: 7 ejemplos precargados con dropdown
- **Bilingüe**: Cambio instantáneo entre Inglés y Español
- **Keyboard shortcuts**:
  - `Ctrl+Enter`: Compilar
  - `Ctrl+K`: Limpiar
  - `Escape`: Cerrar menú de ejemplos
- **Copy to clipboard**: Copiar output con un click
- **3 pestañas de análisis**:
  - **Execution Stack**: Pila con niveles de anidamiento
  - **Symbol Table**: Tabla de símbolos post-ejecución
  - **Compilation Details**: Output completo del compilador

### 🖥️ Terminal Interactiva (Nueva!)

Terminal flotante con dos pestañas:

#### 1. **Logs** (Pestaña de monitoreo)
- Visualización en tiempo real de la compilación
- Timestamps automáticos
- Colores por tipo de mensaje:
  - 🟢 Verde: stdout
  - 🔴 Rojo: stderr/errores
  - 🔵 Azul: compilación
  - 🟡 Amarillo: sistema
- Botón Clear para limpiar logs
- Auto-scroll al final

#### 2. **Terminal** (Pestaña interactiva - Protegida)
- **Acceso bash completo** al contenedor del compilador
- **Autenticación con contraseña** (configurable vía variable de entorno)
- **XTerm.js** con colores y formato completo
- Comandos disponibles:
  ```bash
  ls                    # Listar archivos
  cat php.l             # Ver código fuente del lexer
  nano test.php         # Crear/editar archivos PHP
  ./phpcompiler file.php # Ejecutar compilador directamente
  ```
- **Características de seguridad**:
  - Requiere autenticación antes de acceder
  - Icono de candado 🔒 cuando no está autenticado
  - Modal de login elegante
  - Sesión persistente en localStorage
  - Botón de logout visible cuando está autenticado

### Configuración de Contraseña de Terminal

**Docker Desktop (desarrollo):**
```bash
# En archivo .env
NEXT_PUBLIC_TERMINAL_PASSWORD=tu_password_segura
```

**Render (producción):**
1. Dashboard de Render → Tu servicio → Environment
2. Agregar variable: `NEXT_PUBLIC_TERMINAL_PASSWORD = tu_password_segura`
3. Redeploy automático

**IMPORTANTE**: La variable `NEXT_PUBLIC_TERMINAL_PASSWORD` debe estar disponible **durante el build** de Next.js, no solo en runtime. El Dockerfile.deploy ya está configurado para recibirla como `ARG`.

---

## 🔍 Detalles Técnicos

### Macros de Yacc
- `YYERROR_VERBOSE`: Mensajes de error detallados
- `yyerrok`: Recuperación de errores
- `yylineno`: Rastreo de números de línea

### Tipos de Datos (C)
```c
typedef enum {
    TYPE_UNDEFINED,
    TYPE_INT,
    TYPE_STRING,
    TYPE_BOOL
} TipoDato;
```

### Conversiones de Tipo
- **Aritmética**: Solo int + int
- **Concatenación**: Convierte todo a string con `.`
- **Comparación**: Tipos compatibles

---

## 📦 Tecnologías Utilizadas

- **Lex (Flex)**: Análisis léxico
- **Yacc (Bison)**: Análisis sintáctico
- **C**: Implementación del compilador
- **NestJS**: Backend con TypeScript
- **Next.js**: Frontend con React
- **Monaco Editor**: Editor de código
- **Socket.io**: Comunicación en tiempo real
- **Docker**: Containerización
- **Nginx**: Reverse proxy (deployment)
- **Supervisord**: Gestor de procesos (deployment)

---

## 🤝 Contribuciones

Proyecto desarrollado como parte de un curso de compiladores.

## 📄 Licencia

Uso académico.

---

**¡Feliz compilación!** 🎉
