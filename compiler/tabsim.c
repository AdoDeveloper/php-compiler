#include "tabsim.h"

// Variables globales
simbolo *tabla = NULL;
int level = 0;
RegistroPila stack[MAX_STACK];
int stack_top = 0;
int error_count = 0;

// Crear tabla de símbolos vacía
simbolo* crear() {
    return NULL;
}

// Insertar símbolo en la tabla
void insertar(simbolo **tabla, simbolo *s) {
    s->sig = *tabla;
    s->scope = level;
    *tabla = s;

    // Registrar en la pila de ejecución
    char detalles[512];
    snprintf(detalles, sizeof(detalles),
             "Variable '%s' tipo %s, scope %d",
             s->nombre, tipo_a_string(s->tipo), s->scope);
    push_stack("DECLARACION", s->linea, detalles);
}

// Buscar símbolo en cualquier ámbito
simbolo* buscar(simbolo *tabla, char nombre[]) {
    simbolo *actual = tabla;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

// Buscar símbolo solo en el bloque actual
simbolo* buscarEnBloque(simbolo *tabla, char nombre[], int scope) {
    simbolo *actual = tabla;
    while (actual != NULL && actual->scope >= scope) {
        if (strcmp(actual->nombre, nombre) == 0 && actual->scope == scope) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

// Imprimir tabla de símbolos
void imprimir(simbolo *tabla) {
    printf("\n=== TABLA DE SIMBOLOS ===\n");
    printf("%-15s %-10s %-10s %-15s %-6s\n",
           "Nombre", "Tipo", "Valor", "Inicializado", "Scope");
    printf("---------------------------------------------------------------\n");

    simbolo *actual = tabla;
    while (actual != NULL) {
        printf("%-15s %-10s ", actual->nombre, tipo_a_string(actual->tipo));

        // Imprimir valor según tipo
        if (actual->inicializado) {
            switch (actual->tipo) {
                case TYPE_INT:
                    printf("%-10d", actual->valor.valor_int);
                    break;
                case TYPE_STRING:
                    printf("%-10s", actual->valor.valor_str);
                    break;
                case TYPE_BOOL:
                    printf("%-10s", actual->valor.valor_bool ? "true" : "false");
                    break;
                default:
                    printf("%-10s", "N/A");
            }
        } else {
            printf("%-10s", "N/A");
        }

        printf("%-15s %-6d\n",
               actual->inicializado ? "Si" : "No",
               actual->scope);

        actual = actual->sig;
    }
    printf("=========================\n\n");
}

// Entrar a un nuevo bloque
void entrarBloque() {
    level++;
    char detalles[512];
    snprintf(detalles, sizeof(detalles), "Nivel de anidamiento: %d", level);
    push_stack("ENTRAR_BLOQUE", 0, detalles);
}

// Salir de un bloque
void salirBloque() {
    char detalles[512];
    snprintf(detalles, sizeof(detalles), "Saliendo del nivel: %d", level);
    push_stack("SALIR_BLOQUE", 0, detalles);
    level--;
}

// Eliminar símbolos del bloque actual
void eliminarBloque(simbolo **tabla) {
    simbolo *actual = *tabla;
    simbolo *anterior = NULL;

    while (actual != NULL && actual->scope > level) {
        simbolo *temp = actual;
        actual = actual->sig;
        free(temp);
    }

    *tabla = actual;
}

// Agregar operación a la pila de ejecución
void push_stack(const char *operacion, int linea, const char *detalles) {
    if (stack_top < MAX_STACK) {
        strncpy(stack[stack_top].operacion, operacion, sizeof(stack[stack_top].operacion) - 1);
        stack[stack_top].linea = linea;
        strncpy(stack[stack_top].detalles, detalles, sizeof(stack[stack_top].detalles) - 1);
        stack_top++;
    }
}

// Quitar operación de la pila
void pop_stack() {
    if (stack_top > 0) {
        stack_top--;
    }
}

// Imprimir pila de ejecución
void print_stack() {
    printf("\n=== PILA DE EJECUCION ===\n");
    if (stack_top == 0) {
        printf("(vacía)\n");
    } else {
        for (int i = stack_top - 1; i >= 0; i--) {
            if (stack[i].linea > 0) {
                printf("[%d] %s (línea %d): %s\n",
                       i + 1, stack[i].operacion, stack[i].linea, stack[i].detalles);
            } else {
                printf("[%d] %s: %s\n",
                       i + 1, stack[i].operacion, stack[i].detalles);
            }
        }
    }
    printf("=========================\n\n");
}

// Limpiar pila
void clear_stack() {
    stack_top = 0;
}

// Convertir tipo a string
const char* tipo_a_string(TipoDato tipo) {
    switch (tipo) {
        case TYPE_INT: return "int";
        case TYPE_STRING: return "string";
        case TYPE_BOOL: return "bool";
        case TYPE_UNDEFINED: return "indefinido";
        default: return "desconocido";
    }
}

// Registrar error
void registrar_error(const char *mensaje, int linea) {
    error_count++;
    fprintf(stderr, "ERROR en línea %d: %s\n", linea, mensaje);
}

// Imprimir resumen de errores
void imprimir_errores() {
    if (error_count > 0) {
        fprintf(stderr, "\nTotal de errores: %d\n", error_count);
    } else {
        printf("\nCompilación exitosa. Sin errores.\n");
    }
}

// ============================================================================
// IMPLEMENTACIÓN DEL ABSTRACT SYNTAX TREE (AST)
// ============================================================================

// Función auxiliar para crear nodo base
static NodoAST* crear_nodo_base(TipoNodoAST tipo, int linea) {
    NodoAST *nodo = (NodoAST*)malloc(sizeof(NodoAST));
    if (!nodo) {
        fprintf(stderr, "Error: No se pudo asignar memoria para nodo AST\n");
        exit(1);
    }
    memset(nodo, 0, sizeof(NodoAST));
    nodo->tipo = tipo;
    nodo->linea = linea;
    return nodo;
}

// Crear nodo literal
NodoAST* crear_nodo_literal(TipoDato tipo, ValorDato valor, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_LITERAL, linea);
    nodo->datos.literal.tipo_dato = tipo;
    nodo->datos.literal.valor = valor;
    return nodo;
}

// Crear nodo variable
NodoAST* crear_nodo_variable(const char *nombre, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_VARIABLE, linea);
    strncpy(nodo->datos.variable.nombre, nombre, sizeof(nodo->datos.variable.nombre) - 1);
    return nodo;
}

// Crear nodo binario
NodoAST* crear_nodo_binario(TipoOperador op, NodoAST *izq, NodoAST *der, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_BINARIO, linea);
    nodo->datos.binario.op = op;
    nodo->datos.binario.izq = izq;
    nodo->datos.binario.der = der;
    return nodo;
}

// Crear nodo unario
NodoAST* crear_nodo_unario(TipoOperador op, NodoAST *operando, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_UNARIO, linea);
    nodo->datos.unario.op = op;
    nodo->datos.unario.operando = operando;
    return nodo;
}

// Crear nodo asignacion
NodoAST* crear_nodo_asignacion(const char *nombre_var, NodoAST *expresion, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_ASIGNACION, linea);
    strncpy(nodo->datos.asignacion.nombre_var, nombre_var, sizeof(nodo->datos.asignacion.nombre_var) - 1);
    nodo->datos.asignacion.expresion = expresion;
    return nodo;
}

// Crear nodo echo
NodoAST* crear_nodo_echo(NodoAST *expresion, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_ECHO, linea);
    nodo->datos.echo.expresion = expresion;
    return nodo;
}

// Crear nodo if
NodoAST* crear_nodo_if(NodoAST *condicion, NodoAST *bloque_then, NodoAST *bloque_else, int linea) {
    NodoAST *nodo = crear_nodo_base(bloque_else ? AST_IF_ELSE : AST_IF, linea);
    nodo->datos.stmt_if.condicion = condicion;
    nodo->datos.stmt_if.bloque_then = bloque_then;
    nodo->datos.stmt_if.bloque_else = bloque_else;
    return nodo;
}

// Crear nodo while
NodoAST* crear_nodo_while(NodoAST *condicion, NodoAST *bloque, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_WHILE, linea);
    nodo->datos.stmt_while.condicion = condicion;
    nodo->datos.stmt_while.bloque = bloque;
    return nodo;
}

// Crear nodo for
NodoAST* crear_nodo_for(NodoAST *init, NodoAST *condicion, NodoAST *incremento, NodoAST *bloque, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_FOR, linea);
    nodo->datos.stmt_for.init = init;
    nodo->datos.stmt_for.condicion = condicion;
    nodo->datos.stmt_for.incremento = incremento;
    nodo->datos.stmt_for.bloque = bloque;
    return nodo;
}

// Crear nodo do-while
NodoAST* crear_nodo_do_while(NodoAST *bloque, NodoAST *condicion, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_DO_WHILE, linea);
    nodo->datos.stmt_do_while.bloque = bloque;
    nodo->datos.stmt_do_while.condicion = condicion;
    return nodo;
}

// Crear nodo sentencias
NodoAST* crear_nodo_sentencias(int linea) {
    NodoAST *nodo = crear_nodo_base(AST_SENTENCIAS, linea);
    nodo->datos.sentencias.capacidad = 10;
    nodo->datos.sentencias.num_sentencias = 0;
    nodo->datos.sentencias.sentencias = (NodoAST**)malloc(sizeof(NodoAST*) * nodo->datos.sentencias.capacidad);
    return nodo;
}

// Crear nodo break
NodoAST* crear_nodo_break(int linea) {
    return crear_nodo_base(AST_BREAK, linea);
}

// Crear nodo continue
NodoAST* crear_nodo_continue(int linea) {
    return crear_nodo_base(AST_CONTINUE, linea);
}

// Crear nodo incremento
NodoAST* crear_nodo_incremento(const char *nombre_var, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_INCREMENTO, linea);
    strncpy(nodo->datos.inc_dec.nombre_var, nombre_var, sizeof(nodo->datos.inc_dec.nombre_var) - 1);
    return nodo;
}

// Crear nodo decremento
NodoAST* crear_nodo_decremento(const char *nombre_var, int linea) {
    NodoAST *nodo = crear_nodo_base(AST_DECREMENTO, linea);
    strncpy(nodo->datos.inc_dec.nombre_var, nombre_var, sizeof(nodo->datos.inc_dec.nombre_var) - 1);
    return nodo;
}

// Agregar sentencia a lista de sentencias
void agregar_sentencia(NodoAST *nodo_sentencias, NodoAST *sentencia) {
    if (!nodo_sentencias || nodo_sentencias->tipo != AST_SENTENCIAS || !sentencia) {
        return;
    }

    // Expandir array si es necesario
    if (nodo_sentencias->datos.sentencias.num_sentencias >= nodo_sentencias->datos.sentencias.capacidad) {
        nodo_sentencias->datos.sentencias.capacidad *= 2;
        nodo_sentencias->datos.sentencias.sentencias = (NodoAST**)realloc(
            nodo_sentencias->datos.sentencias.sentencias,
            sizeof(NodoAST*) * nodo_sentencias->datos.sentencias.capacidad
        );
    }

    nodo_sentencias->datos.sentencias.sentencias[nodo_sentencias->datos.sentencias.num_sentencias++] = sentencia;
}

// Liberar memoria del AST
void liberar_ast(NodoAST *nodo) {
    if (!nodo) return;

    switch (nodo->tipo) {
        case AST_BINARIO:
            liberar_ast(nodo->datos.binario.izq);
            liberar_ast(nodo->datos.binario.der);
            break;
        case AST_UNARIO:
            liberar_ast(nodo->datos.unario.operando);
            break;
        case AST_ASIGNACION:
            liberar_ast(nodo->datos.asignacion.expresion);
            break;
        case AST_ECHO:
            liberar_ast(nodo->datos.echo.expresion);
            break;
        case AST_IF:
        case AST_IF_ELSE:
            liberar_ast(nodo->datos.stmt_if.condicion);
            liberar_ast(nodo->datos.stmt_if.bloque_then);
            if (nodo->datos.stmt_if.bloque_else) {
                liberar_ast(nodo->datos.stmt_if.bloque_else);
            }
            break;
        case AST_WHILE:
            liberar_ast(nodo->datos.stmt_while.condicion);
            liberar_ast(nodo->datos.stmt_while.bloque);
            break;
        case AST_FOR:
            liberar_ast(nodo->datos.stmt_for.init);
            liberar_ast(nodo->datos.stmt_for.condicion);
            liberar_ast(nodo->datos.stmt_for.incremento);
            liberar_ast(nodo->datos.stmt_for.bloque);
            break;
        case AST_DO_WHILE:
            liberar_ast(nodo->datos.stmt_do_while.bloque);
            liberar_ast(nodo->datos.stmt_do_while.condicion);
            break;
        case AST_SENTENCIAS:
            for (int i = 0; i < nodo->datos.sentencias.num_sentencias; i++) {
                liberar_ast(nodo->datos.sentencias.sentencias[i]);
            }
            free(nodo->datos.sentencias.sentencias);
            break;
        default:
            break;
    }

    free(nodo);
}
// ============================================================================
// EVALUACIÓN Y EJECUCIÓN DEL AST
// ============================================================================

// Evaluar expresión y retornar resultado
ResultadoEval evaluar_expresion(NodoAST *nodo, simbolo **tabla) {
    ResultadoEval resultado;
    resultado.tipo = TYPE_UNDEFINED;

    if (!nodo) {
        return resultado;
    }

    switch (nodo->tipo) {
        case AST_LITERAL:
            resultado.tipo = nodo->datos.literal.tipo_dato;
            resultado.valor = nodo->datos.literal.valor;
            break;

        case AST_VARIABLE: {
            simbolo *var = buscar(*tabla, nodo->datos.variable.nombre);
            if (var && var->inicializado) {
                resultado.tipo = var->tipo;
                resultado.valor = var->valor;
            } else {
                fprintf(stderr, "Error línea %d: Variable '%s' no inicializada\n",
                        nodo->linea, nodo->datos.variable.nombre);
            }
            break;
        }

        case AST_BINARIO: {
            ResultadoEval izq = evaluar_expresion(nodo->datos.binario.izq, tabla);
            ResultadoEval der = evaluar_expresion(nodo->datos.binario.der, tabla);

            switch (nodo->datos.binario.op) {
                case OP_SUMA:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_INT;
                        resultado.valor.valor_int = izq.valor.valor_int + der.valor.valor_int;
                    }
                    break;

                case OP_RESTA:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_INT;
                        resultado.valor.valor_int = izq.valor.valor_int - der.valor.valor_int;
                    }
                    break;

                case OP_MULT:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_INT;
                        resultado.valor.valor_int = izq.valor.valor_int * der.valor.valor_int;
                    }
                    break;

                case OP_DIV:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        if (der.valor.valor_int != 0) {
                            resultado.tipo = TYPE_INT;
                            resultado.valor.valor_int = izq.valor.valor_int / der.valor.valor_int;
                        } else {
                            fprintf(stderr, "Error línea %d: División por cero\n", nodo->linea);
                        }
                    }
                    break;

                case OP_LT:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_int < der.valor.valor_int;
                    }
                    break;

                case OP_GT:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_int > der.valor.valor_int;
                    }
                    break;

                case OP_LE:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_int <= der.valor.valor_int;
                    }
                    break;

                case OP_GE:
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_int >= der.valor.valor_int;
                    }
                    break;

                case OP_EQ:
                    resultado.tipo = TYPE_BOOL;
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.valor.valor_bool = izq.valor.valor_int == der.valor.valor_int;
                    } else if (izq.tipo == TYPE_STRING && der.tipo == TYPE_STRING) {
                        resultado.valor.valor_bool = strcmp(izq.valor.valor_str, der.valor.valor_str) == 0;
                    } else if (izq.tipo == TYPE_BOOL && der.tipo == TYPE_BOOL) {
                        resultado.valor.valor_bool = izq.valor.valor_bool == der.valor.valor_bool;
                    }
                    break;

                case OP_NE:
                    resultado.tipo = TYPE_BOOL;
                    if (izq.tipo == TYPE_INT && der.tipo == TYPE_INT) {
                        resultado.valor.valor_bool = izq.valor.valor_int != der.valor.valor_int;
                    } else if (izq.tipo == TYPE_STRING && der.tipo == TYPE_STRING) {
                        resultado.valor.valor_bool = strcmp(izq.valor.valor_str, der.valor.valor_str) != 0;
                    } else if (izq.tipo == TYPE_BOOL && der.tipo == TYPE_BOOL) {
                        resultado.valor.valor_bool = izq.valor.valor_bool != der.valor.valor_bool;
                    }
                    break;

                case OP_AND:
                    if (izq.tipo == TYPE_BOOL && der.tipo == TYPE_BOOL) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_bool && der.valor.valor_bool;
                    }
                    break;

                case OP_OR:
                    if (izq.tipo == TYPE_BOOL && der.tipo == TYPE_BOOL) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = izq.valor.valor_bool || der.valor.valor_bool;
                    }
                    break;

                case OP_CONCAT: {
                    resultado.tipo = TYPE_STRING;
                    char left_str[256] = "";
                    char right_str[256] = "";

                    // Convertir izquierda a string
                    if (izq.tipo == TYPE_STRING) {
                        strncpy(left_str, izq.valor.valor_str, sizeof(left_str) - 1);
                    } else if (izq.tipo == TYPE_INT) {
                        snprintf(left_str, sizeof(left_str), "%d", izq.valor.valor_int);
                    } else if (izq.tipo == TYPE_BOOL) {
                        strncpy(left_str, izq.valor.valor_bool ? "1" : "", sizeof(left_str) - 1);
                    }

                    // Convertir derecha a string
                    if (der.tipo == TYPE_STRING) {
                        strncpy(right_str, der.valor.valor_str, sizeof(right_str) - 1);
                    } else if (der.tipo == TYPE_INT) {
                        snprintf(right_str, sizeof(right_str), "%d", der.valor.valor_int);
                    } else if (der.tipo == TYPE_BOOL) {
                        strncpy(right_str, der.valor.valor_bool ? "1" : "", sizeof(right_str) - 1);
                    }

                    snprintf(resultado.valor.valor_str, sizeof(resultado.valor.valor_str),
                            "%s%s", left_str, right_str);
                    break;
                }

                default:
                    break;
            }
            break;
        }

        case AST_UNARIO: {
            ResultadoEval operando = evaluar_expresion(nodo->datos.unario.operando, tabla);

            switch (nodo->datos.unario.op) {
                case OP_UMINUS:
                    if (operando.tipo == TYPE_INT) {
                        resultado.tipo = TYPE_INT;
                        resultado.valor.valor_int = -operando.valor.valor_int;
                    }
                    break;

                case OP_NOT:
                    if (operando.tipo == TYPE_BOOL) {
                        resultado.tipo = TYPE_BOOL;
                        resultado.valor.valor_bool = !operando.valor.valor_bool;
                    }
                    break;

                default:
                    break;
            }
            break;
        }

        default:
            break;
    }

    return resultado;
}

// Ejecutar sentencia
void ejecutar_sentencia(NodoAST *nodo, simbolo **tabla, int *break_flag, int *continue_flag) {
    if (!nodo) return;

    // Verificar flags de control de flujo
    if (*break_flag || *continue_flag) {
        return;
    }

    switch (nodo->tipo) {
        case AST_SENTENCIAS:
            for (int i = 0; i < nodo->datos.sentencias.num_sentencias; i++) {
                ejecutar_sentencia(nodo->datos.sentencias.sentencias[i], tabla, break_flag, continue_flag);
                if (*break_flag || *continue_flag) {
                    break;
                }
            }
            break;

        case AST_ASIGNACION: {
            ResultadoEval valor = evaluar_expresion(nodo->datos.asignacion.expresion, tabla);
            simbolo *var = buscar(*tabla, nodo->datos.asignacion.nombre_var);

            if (!var) {
                // Crear variable nueva
                var = (simbolo*)malloc(sizeof(simbolo));
                memset(var, 0, sizeof(simbolo));
                strncpy(var->nombre, nodo->datos.asignacion.nombre_var, sizeof(var->nombre) - 1);
                var->tipo = valor.tipo;
                var->valor = valor.valor;
                var->inicializado = 1;
                var->scope = level;
                var->linea = nodo->linea;
                insertar(tabla, var);
            } else {
                // Actualizar variable existente
                var->tipo = valor.tipo;
                var->valor = valor.valor;
                var->inicializado = 1;
            }
            break;
        }

        case AST_ECHO: {
            ResultadoEval valor = evaluar_expresion(nodo->datos.echo.expresion, tabla);

            if (valor.tipo == TYPE_INT) {
                printf("%d", valor.valor.valor_int);
            } else if (valor.tipo == TYPE_STRING) {
                printf("%s", valor.valor.valor_str);
            } else if (valor.tipo == TYPE_BOOL) {
                printf("%s", valor.valor.valor_bool ? "1" : "");
            }
            break;
        }

        case AST_IF:
        case AST_IF_ELSE: {
            ResultadoEval condicion = evaluar_expresion(nodo->datos.stmt_if.condicion, tabla);

            if (condicion.tipo == TYPE_BOOL && condicion.valor.valor_bool) {
                entrarBloque();
                ejecutar_sentencia(nodo->datos.stmt_if.bloque_then, tabla, break_flag, continue_flag);
                salirBloque();
            } else if (nodo->datos.stmt_if.bloque_else) {
                entrarBloque();
                ejecutar_sentencia(nodo->datos.stmt_if.bloque_else, tabla, break_flag, continue_flag);
                salirBloque();
            }
            break;
        }

        case AST_WHILE: {
            while (1) {
                ResultadoEval condicion = evaluar_expresion(nodo->datos.stmt_while.condicion, tabla);

                if (condicion.tipo != TYPE_BOOL || !condicion.valor.valor_bool) {
                    break;
                }

                entrarBloque();
                ejecutar_sentencia(nodo->datos.stmt_while.bloque, tabla, break_flag, continue_flag);
                salirBloque();

                if (*break_flag) {
                    *break_flag = 0;  // Consumir el break
                    break;
                }

                if (*continue_flag) {
                    *continue_flag = 0;  // Consumir el continue y continuar el loop
                }
            }
            break;
        }

        case AST_FOR: {
            // Ejecutar inicialización
            if (nodo->datos.stmt_for.init) {
                ejecutar_sentencia(nodo->datos.stmt_for.init, tabla, break_flag, continue_flag);
            }

            // Loop
            while (1) {
                // Evaluar condición
                if (nodo->datos.stmt_for.condicion) {
                    ResultadoEval condicion = evaluar_expresion(nodo->datos.stmt_for.condicion, tabla);
                    if (condicion.tipo != TYPE_BOOL || !condicion.valor.valor_bool) {
                        break;
                    }
                }

                // Ejecutar cuerpo
                entrarBloque();
                ejecutar_sentencia(nodo->datos.stmt_for.bloque, tabla, break_flag, continue_flag);
                salirBloque();

                if (*break_flag) {
                    *break_flag = 0;
                    break;
                }

                if (*continue_flag) {
                    *continue_flag = 0;
                }

                // Ejecutar incremento
                if (nodo->datos.stmt_for.incremento) {
                    ejecutar_sentencia(nodo->datos.stmt_for.incremento, tabla, break_flag, continue_flag);
                }
            }
            break;
        }

        case AST_DO_WHILE: {
            do {
                entrarBloque();
                ejecutar_sentencia(nodo->datos.stmt_do_while.bloque, tabla, break_flag, continue_flag);
                salirBloque();

                if (*break_flag) {
                    *break_flag = 0;
                    break;
                }

                if (*continue_flag) {
                    *continue_flag = 0;
                }

                ResultadoEval condicion = evaluar_expresion(nodo->datos.stmt_do_while.condicion, tabla);
                if (condicion.tipo != TYPE_BOOL || !condicion.valor.valor_bool) {
                    break;
                }
            } while (1);
            break;
        }

        case AST_INCREMENTO: {
            simbolo *var = buscar(*tabla, nodo->datos.inc_dec.nombre_var);
            if (var && var->tipo == TYPE_INT) {
                var->valor.valor_int++;
            }
            break;
        }

        case AST_DECREMENTO: {
            simbolo *var = buscar(*tabla, nodo->datos.inc_dec.nombre_var);
            if (var && var->tipo == TYPE_INT) {
                var->valor.valor_int--;
            }
            break;
        }

        case AST_BREAK:
            *break_flag = 1;
            break;

        case AST_CONTINUE:
            *continue_flag = 1;
            break;

        default:
            break;
    }
}

// Ejecutar programa completo
void ejecutar_programa(NodoAST *raiz, simbolo **tabla) {
    if (!raiz) return;

    int break_flag = 0;
    int continue_flag = 0;

    ejecutar_sentencia(raiz, tabla, &break_flag, &continue_flag);
}
