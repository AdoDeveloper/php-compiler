%{
#include "tabsim.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char *s);
int yylex(void);
extern int yylineno;
extern simbolo *tabla;
extern FILE *yyin;

// Raíz del AST
NodoAST *raiz_ast = NULL;

// Macros para manejo de errores con contexto
#define YYERROR_VERBOSE 1
#define YYDEBUG 1

%}

%union {
    int int_val;
    char *string_val;
    int bool_val;
    simbolo *ptr_simbolo;
    TipoDato tipo;
    NodoAST *nodo;
}

%token PHP_OPEN PHP_CLOSE
%token TOK_ECHO IF ELSE ELSEIF WHILE FOR DO BREAK CONTINUE FUNCTION RETURN
%token <int_val> NUMERO
%token <string_val> STRING ID
%token <bool_val> TRUE FALSE
%token <ptr_simbolo> VARIABLE
%token EQ NE LE GE LT GT
%token AND OR NOT
%token INC DEC PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN
%token CONCAT

%type <nodo> programa sentencias sentencia
%type <nodo> asignacion declaracion expresion expresion_aritmetica
%type <nodo> expresion_logica expresion_relacional
%type <nodo> echo_stmt if_stmt while_stmt for_stmt do_while_stmt bloque

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left '+' '-'
%left CONCAT
%left '*' '/'
%right NOT
%right UMINUS

%start programa

%%

programa:
    PHP_OPEN sentencias PHP_CLOSE   {
                                        $$ = $2;
                                        raiz_ast = $$;
                                        printf("\n=== COMPILACIÓN COMPLETADA ===\n");
                                    }
    | PHP_OPEN sentencias            {
                                        $$ = $2;
                                        raiz_ast = $$;
                                        printf("\n=== COMPILACIÓN COMPLETADA (sin cierre) ===\n");
                                    }
    | sentencias                     {
                                        $$ = $1;
                                        raiz_ast = $$;
                                        printf("\n=== COMPILACIÓN COMPLETADA (sin etiquetas PHP) ===\n");
                                    }
    | error                          {
                                        yyerrok;
                                        printf("\n=== ERROR EN PROGRAMA ===\n");
                                        raiz_ast = NULL;
                                    }
    ;

sentencias:
    /* vacío */                     { $$ = crear_nodo_sentencias(yylineno); }
    | sentencias sentencia          {
                                        if ($2) {
                                            agregar_sentencia($1, $2);
                                        }
                                        $$ = $1;
                                    }
    ;

sentencia:
    asignacion ';'                  { $$ = $1; }
    | declaracion ';'                { $$ = NULL; /* Las declaraciones se manejan en asignación */ }
    | expresion ';'                 { $$ = NULL; /* Expresiones sueltas se ignoran */ }
    | echo_stmt ';'                 { $$ = $1; }
    | if_stmt                       { $$ = $1; }
    | while_stmt                    { $$ = $1; }
    | for_stmt                      { $$ = $1; }
    | do_while_stmt ';'             { $$ = $1; }
    | bloque                        { $$ = $1; }
    | BREAK ';'                     {
                                        $$ = crear_nodo_break(yylineno);
                                        push_stack("BREAK", yylineno, "Salir del ciclo");
                                    }
    | CONTINUE ';'                  {
                                        $$ = crear_nodo_continue(yylineno);
                                        push_stack("CONTINUE", yylineno, "Continuar ciclo");
                                    }
    | error ';'                     { yyerrok; $$ = NULL; }
    ;

bloque:
    '{' sentencias '}'              {
                                        $$ = $2;
                                    }
    ;

declaracion:
    VARIABLE                        {
                                        simbolo *existe = buscar(tabla, $1->nombre);
                                        if (existe == NULL) {
                                            $1->tipo = TYPE_UNDEFINED;
                                            $1->inicializado = 0;
                                            insertar(&tabla, $1);

                                            char detalles[512];
                                            snprintf(detalles, sizeof(detalles),
                                                    "Variable '%s' declarada sin tipo explícito",
                                                    $1->nombre);
                                            push_stack("DECLARACION", yylineno, detalles);
                                        }
                                        $$ = NULL;
                                    }
    ;

asignacion:
    VARIABLE '=' expresion          {
                                        // Validación semántica
                                        simbolo *var = buscar(tabla, $1->nombre);
                                        if (var == NULL) {
                                            $1->tipo = TYPE_UNDEFINED;  // Se determinará en tiempo de ejecución
                                            $1->inicializado = 0;
                                            insertar(&tabla, $1);

                                            char detalles[512];
                                            snprintf(detalles, sizeof(detalles),
                                                    "Variable '%s' declarada implícitamente",
                                                    $1->nombre);
                                            push_stack("ASIGNACION", yylineno, detalles);
                                        }

                                        // Crear nodo AST
                                        $$ = crear_nodo_asignacion($1->nombre, $3, yylineno);
                                    }
    | VARIABLE PLUS_ASSIGN expresion    {
                                            simbolo *var = buscar(tabla, $1->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", $1->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("ASIGNACION_COMPUESTA", yylineno, "+=");

                                            // Crear AST: $var = $var + expr
                                            NodoAST *var_nodo = crear_nodo_variable($1->nombre, yylineno);
                                            NodoAST *suma = crear_nodo_binario(OP_SUMA, var_nodo, $3, yylineno);
                                            $$ = crear_nodo_asignacion($1->nombre, suma, yylineno);
                                        }
    | VARIABLE MINUS_ASSIGN expresion   {
                                            simbolo *var = buscar(tabla, $1->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", $1->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("ASIGNACION_COMPUESTA", yylineno, "-=");

                                            // Crear AST: $var = $var - expr
                                            NodoAST *var_nodo = crear_nodo_variable($1->nombre, yylineno);
                                            NodoAST *resta = crear_nodo_binario(OP_RESTA, var_nodo, $3, yylineno);
                                            $$ = crear_nodo_asignacion($1->nombre, resta, yylineno);
                                        }
    | VARIABLE INC                      {
                                            simbolo *var = buscar(tabla, $1->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", $1->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("INCREMENTO", yylineno, "++");

                                            $$ = crear_nodo_incremento($1->nombre, yylineno);
                                        }
    | VARIABLE DEC                      {
                                            simbolo *var = buscar(tabla, $1->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", $1->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("DECREMENTO", yylineno, "--");

                                            $$ = crear_nodo_decremento($1->nombre, yylineno);
                                        }
    ;

echo_stmt:
    TOK_ECHO expresion              {
                                        // Detectar si es un salto de línea
                                        char *descripcion = "Imprimir valor";
                                        if ($2->tipo == AST_LITERAL &&
                                            $2->datos.literal.tipo_dato == TYPE_STRING) {
                                            if (strcmp($2->datos.literal.valor.valor_str, "\\n") == 0 ||
                                                strcmp($2->datos.literal.valor.valor_str, "\n") == 0) {
                                                descripcion = "Salto de línea";
                                            } else if (strlen($2->datos.literal.valor.valor_str) == 0) {
                                                descripcion = "Línea vacía";
                                            }
                                        }
                                        push_stack("ECHO", yylineno, descripcion);
                                        $$ = crear_nodo_echo($2, yylineno);
                                    }
    ;

if_stmt:
    IF '(' expresion ')' bloque     {
                                        push_stack("IF", yylineno, "Bloque condicional");
                                        $$ = crear_nodo_if($3, $5, NULL, yylineno);
                                    }
    | IF '(' expresion ')' bloque ELSE bloque
                                    {
                                        push_stack("IF-ELSE", yylineno, "Bloque condicional con else");
                                        $$ = crear_nodo_if($3, $5, $7, yylineno);
                                    }
    ;

while_stmt:
    WHILE '(' expresion ')' bloque  {
                                        push_stack("WHILE", yylineno, "Ciclo while");
                                        $$ = crear_nodo_while($3, $5, yylineno);
                                    }
    ;

do_while_stmt:
    DO bloque WHILE '(' expresion ')'
                                    {
                                        push_stack("DO-WHILE", yylineno, "Ciclo do-while");
                                        $$ = crear_nodo_do_while($2, $5, yylineno);
                                    }
    ;

for_stmt:
    FOR '(' asignacion ';' expresion ';' asignacion ')' bloque
                                    {
                                        push_stack("FOR", yylineno, "Ciclo for");
                                        $$ = crear_nodo_for($3, $5, $7, $9, yylineno);
                                    }
    ;

expresion:
    expresion_aritmetica            { $$ = $1; }
    | expresion_logica              { $$ = $1; }
    | expresion_relacional          { $$ = $1; }
    | VARIABLE                      {
                                        simbolo *var = buscar(tabla, $1->nombre);
                                        if (var == NULL) {
                                            char msg[256];
                                            snprintf(msg, sizeof(msg),
                                                    "Variable '%s' no declarada", $1->nombre);
                                            yyerror(msg);
                                        }
                                        $$ = crear_nodo_variable($1->nombre, yylineno);
                                    }
    | NUMERO                        {
                                        ValorDato valor;
                                        valor.valor_int = $1;
                                        $$ = crear_nodo_literal(TYPE_INT, valor, yylineno);
                                    }
    | STRING                        {
                                        ValorDato valor;
                                        strncpy(valor.valor_str, $1, sizeof(valor.valor_str) - 1);
                                        $$ = crear_nodo_literal(TYPE_STRING, valor, yylineno);
                                    }
    | TRUE                          {
                                        ValorDato valor;
                                        valor.valor_bool = 1;
                                        $$ = crear_nodo_literal(TYPE_BOOL, valor, yylineno);
                                    }
    | FALSE                         {
                                        ValorDato valor;
                                        valor.valor_bool = 0;
                                        $$ = crear_nodo_literal(TYPE_BOOL, valor, yylineno);
                                    }
    | '(' expresion ')'             { $$ = $2; }
    ;

expresion_aritmetica:
    expresion '+' expresion         {
                                        push_stack("SUMA", yylineno, "+");
                                        $$ = crear_nodo_binario(OP_SUMA, $1, $3, yylineno);
                                    }
    | expresion '-' expresion       {
                                        push_stack("RESTA", yylineno, "-");
                                        $$ = crear_nodo_binario(OP_RESTA, $1, $3, yylineno);
                                    }
    | expresion '*' expresion       {
                                        push_stack("MULTIPLICACION", yylineno, "*");
                                        $$ = crear_nodo_binario(OP_MULT, $1, $3, yylineno);
                                    }
    | expresion '/' expresion       {
                                        push_stack("DIVISION", yylineno, "/");
                                        $$ = crear_nodo_binario(OP_DIV, $1, $3, yylineno);
                                    }
    | expresion CONCAT expresion    {
                                        push_stack("CONCATENACION", yylineno, ".");
                                        $$ = crear_nodo_binario(OP_CONCAT, $1, $3, yylineno);
                                    }
    | '-' expresion %prec UMINUS    {
                                        $$ = crear_nodo_unario(OP_UMINUS, $2, yylineno);
                                    }
    ;

expresion_relacional:
    expresion EQ expresion          {
                                        push_stack("COMPARACION", yylineno, "==");
                                        $$ = crear_nodo_binario(OP_EQ, $1, $3, yylineno);
                                    }
    | expresion NE expresion        {
                                        push_stack("COMPARACION", yylineno, "!=");
                                        $$ = crear_nodo_binario(OP_NE, $1, $3, yylineno);
                                    }
    | expresion LT expresion        {
                                        push_stack("COMPARACION", yylineno, "<");
                                        $$ = crear_nodo_binario(OP_LT, $1, $3, yylineno);
                                    }
    | expresion GT expresion        {
                                        push_stack("COMPARACION", yylineno, ">");
                                        $$ = crear_nodo_binario(OP_GT, $1, $3, yylineno);
                                    }
    | expresion LE expresion        {
                                        push_stack("COMPARACION", yylineno, "<=");
                                        $$ = crear_nodo_binario(OP_LE, $1, $3, yylineno);
                                    }
    | expresion GE expresion        {
                                        push_stack("COMPARACION", yylineno, ">=");
                                        $$ = crear_nodo_binario(OP_GE, $1, $3, yylineno);
                                    }
    ;

expresion_logica:
    expresion AND expresion         {
                                        push_stack("AND_LOGICO", yylineno, "&&");
                                        $$ = crear_nodo_binario(OP_AND, $1, $3, yylineno);
                                    }
    | expresion OR expresion        {
                                        push_stack("OR_LOGICO", yylineno, "||");
                                        $$ = crear_nodo_binario(OP_OR, $1, $3, yylineno);
                                    }
    | NOT expresion                 {
                                        push_stack("NOT_LOGICO", yylineno, "!");
                                        $$ = crear_nodo_unario(OP_NOT, $2, yylineno);
                                    }
    ;

%%

/* Macro personalizada para yyerror con detalles */
void yyerror(char *s) {
    extern char *yytext;
    fprintf(stderr, "\n*** ERROR SINTACTICO ***\n");
    fprintf(stderr, "Línea %d: %s\n", yylineno, s);
    fprintf(stderr, "Token problemático: '%s'\n", yytext);
    fprintf(stderr, "************************\n\n");

    char detalles[512];
    snprintf(detalles, sizeof(detalles), "%s (token: '%s')", s, yytext);
    push_stack("ERROR", yylineno, detalles);

    error_count++;
}

int main(int argc, char **argv) {

    // Inicializar tabla de símbolos
    tabla = crear();
    clear_stack();

    // Abrir archivo de entrada si se especifica
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: No se puede abrir el archivo '%s'\n", argv[1]);
            return 1;
        }
        printf("Compilando archivo: %s\n\n", argv[1]);
    } else {
        printf("Leyendo desde entrada estándar (Ctrl+D para terminar)...\n\n");
        yyin = stdin;
    }

    // Ejecutar parser - esto construye el AST
    int result = yyparse();

    // Imprimir información de compilación
    print_stack();
    imprimir(tabla);
    imprimir_errores();

    // Si la compilación fue exitosa y hay AST, ejecutarlo
    if (result == 0 && raiz_ast != NULL && error_count == 0) {
        printf("\n=== EJECUTANDO PROGRAMA ===\n");
        ejecutar_programa(raiz_ast, &tabla);
        printf("\n");

        // Imprimir tabla de símbolos actualizada con valores finales
        printf("\n=== TABLA DE SIMBOLOS (POST-EJECUCIÓN) ===\n");
        imprimir(tabla);

        // Liberar memoria del AST
        liberar_ast(raiz_ast);
    }

    // Cerrar archivo de entrada si no es stdin
    if (yyin != stdin) {
        fclose(yyin);
    }

    return result;
}
