#ifndef TABSIM_H
#define TABSIM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STACK 1000

// Tipos de datos soportados
typedef enum {
    TYPE_UNDEFINED = 0,
    TYPE_INT,
    TYPE_STRING,
    TYPE_BOOL
} TipoDato;

// Unión para almacenar valores de diferentes tipos
typedef union {
    int valor_int;
    char valor_str[256];
    int valor_bool;  // 0 = false, 1 = true
} ValorDato;

// Estructura para símbolos en la tabla
typedef struct _simbolo {
    struct _simbolo *sig;
    char nombre[64];
    TipoDato tipo;
    ValorDato valor;
    int scope;       // Nivel de anidamiento
    int inicializado; // 0 = no inicializado, 1 = inicializado
    int linea;       // Línea de declaración
} simbolo;

// Estructura para la pila de ejecución
typedef struct {
    char operacion[256];
    int linea;
    char detalles[512];
} RegistroPila;

// Variables globales
extern simbolo *tabla;
extern int level;
extern RegistroPila stack[MAX_STACK];
extern int stack_top;
extern int error_count;

// Funciones de la tabla de símbolos
simbolo* crear();
void insertar(simbolo **tabla, simbolo *s);
simbolo* buscar(simbolo *tabla, char nombre[]);
simbolo* buscarEnBloque(simbolo *tabla, char nombre[], int scope);
void imprimir(simbolo *tabla);
void entrarBloque();
void salirBloque();
void eliminarBloque(simbolo **tabla);

// Funciones para la pila de ejecución
void push_stack(const char *operacion, int linea, const char *detalles);
void pop_stack();
void print_stack();
void clear_stack();

// Funciones de utilidad
const char* tipo_a_string(TipoDato tipo);
void registrar_error(const char *mensaje, int linea);
void imprimir_errores();

// ============================================================================
// ABSTRACT SYNTAX TREE (AST) - Para ejecución de ciclos y control de flujo
// ============================================================================

// Tipos de nodos del AST
typedef enum {
    AST_PROGRAMA,
    AST_SENTENCIAS,
    AST_ASIGNACION,
    AST_ECHO,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_FOR,
    AST_DO_WHILE,
    AST_BREAK,
    AST_CONTINUE,
    AST_EXPRESION,
    AST_BINARIO,      // Operaciones binarias (+, -, *, /, <, >, ==, etc.)
    AST_UNARIO,       // Operaciones unarias (-, !)
    AST_VARIABLE,
    AST_LITERAL,      // Números, strings, bool
    AST_INCREMENTO,   // ++
    AST_DECREMENTO    // --
} TipoNodoAST;

// Tipos de operadores
typedef enum {
    OP_SUMA, OP_RESTA, OP_MULT, OP_DIV,
    OP_LT, OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE,
    OP_AND, OP_OR, OP_NOT,
    OP_CONCAT,
    OP_UMINUS
} TipoOperador;

// Estructura del nodo AST
typedef struct _nodo_ast {
    TipoNodoAST tipo;
    int linea;

    union {
        // Para literales
        struct {
            TipoDato tipo_dato;
            ValorDato valor;
        } literal;

        // Para variables
        struct {
            char nombre[64];
        } variable;

        // Para operaciones binarias
        struct {
            TipoOperador op;
            struct _nodo_ast *izq;
            struct _nodo_ast *der;
        } binario;

        // Para operaciones unarias
        struct {
            TipoOperador op;
            struct _nodo_ast *operando;
        } unario;

        // Para asignaciones
        struct {
            char nombre_var[64];
            struct _nodo_ast *expresion;
        } asignacion;

        // Para echo
        struct {
            struct _nodo_ast *expresion;
        } echo;

        // Para if
        struct {
            struct _nodo_ast *condicion;
            struct _nodo_ast *bloque_then;
            struct _nodo_ast *bloque_else;  // NULL si no hay else
        } stmt_if;

        // Para while
        struct {
            struct _nodo_ast *condicion;
            struct _nodo_ast *bloque;
        } stmt_while;

        // Para for
        struct {
            struct _nodo_ast *init;       // Inicialización
            struct _nodo_ast *condicion;  // Condición
            struct _nodo_ast *incremento; // Incremento
            struct _nodo_ast *bloque;     // Cuerpo
        } stmt_for;

        // Para do-while
        struct {
            struct _nodo_ast *bloque;
            struct _nodo_ast *condicion;
        } stmt_do_while;

        // Para lista de sentencias
        struct {
            struct _nodo_ast **sentencias;
            int num_sentencias;
            int capacidad;
        } sentencias;

        // Para incremento/decremento
        struct {
            char nombre_var[64];
        } inc_dec;
    } datos;

} NodoAST;

// Funciones para crear nodos del AST
NodoAST* crear_nodo_literal(TipoDato tipo, ValorDato valor, int linea);
NodoAST* crear_nodo_variable(const char *nombre, int linea);
NodoAST* crear_nodo_binario(TipoOperador op, NodoAST *izq, NodoAST *der, int linea);
NodoAST* crear_nodo_unario(TipoOperador op, NodoAST *operando, int linea);
NodoAST* crear_nodo_asignacion(const char *nombre_var, NodoAST *expresion, int linea);
NodoAST* crear_nodo_echo(NodoAST *expresion, int linea);
NodoAST* crear_nodo_if(NodoAST *condicion, NodoAST *bloque_then, NodoAST *bloque_else, int linea);
NodoAST* crear_nodo_while(NodoAST *condicion, NodoAST *bloque, int linea);
NodoAST* crear_nodo_for(NodoAST *init, NodoAST *condicion, NodoAST *incremento, NodoAST *bloque, int linea);
NodoAST* crear_nodo_do_while(NodoAST *bloque, NodoAST *condicion, int linea);
NodoAST* crear_nodo_sentencias(int linea);
NodoAST* crear_nodo_break(int linea);
NodoAST* crear_nodo_continue(int linea);
NodoAST* crear_nodo_incremento(const char *nombre_var, int linea);
NodoAST* crear_nodo_decremento(const char *nombre_var, int linea);

void agregar_sentencia(NodoAST *nodo_sentencias, NodoAST *sentencia);
void liberar_ast(NodoAST *nodo);

// Estructura para resultado de evaluación
typedef struct {
    TipoDato tipo;
    ValorDato valor;
} ResultadoEval;

// Funciones para ejecutar el AST
ResultadoEval evaluar_expresion(NodoAST *nodo, simbolo **tabla);
void ejecutar_sentencia(NodoAST *nodo, simbolo **tabla, int *break_flag, int *continue_flag);
void ejecutar_programa(NodoAST *raiz, simbolo **tabla);

#endif
