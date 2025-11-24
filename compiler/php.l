%{
#include "tabsim.h"
#include "php.tab.h"
#include <string.h>

// Desactivar macro ECHO de Flex
#undef ECHO

void yyerror(char *);
extern simbolo *tabla;
extern int yylineno;
%}

%option yylineno
%option noyywrap

%%

"<?php"         { return PHP_OPEN; }
"?>"            { return PHP_CLOSE; }

    /* Palabras reservadas */
"echo"          { return TOK_ECHO; }
"if"            { return IF; }
"else"          { return ELSE; }
"elseif"        { return ELSEIF; }
"while"         { return WHILE; }
"for"           { return FOR; }
"do"            { return DO; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"function"      { return FUNCTION; }
"return"        { return RETURN; }
"true"          { yylval.bool_val = 1; return TRUE; }
"false"         { yylval.bool_val = 0; return FALSE; }

    /* Operadores de comparación */
"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

    /* Operadores lógicos */
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

    /* Operadores aritméticos */
"++"            { return INC; }
"--"            { return DEC; }
"+="            { return PLUS_ASSIGN; }
"-="            { return MINUS_ASSIGN; }
"*="            { return MULT_ASSIGN; }
"/="            { return DIV_ASSIGN; }

    /* Operador de concatenación */
"."             { return CONCAT; }

    /* Números enteros */
[0-9]+          {
                    yylval.int_val = atoi(yytext);
                    return NUMERO;
                }

    /* Strings entre comillas dobles */
\"([^\\\"]|\\.)*\"  {
                        yylval.string_val = (char *)malloc(strlen(yytext));
                        int j = 0;
                        for (int i = 1; i < strlen(yytext) - 1; i++) {
                            if (yytext[i] == '\\' && i + 1 < strlen(yytext) - 1) {
                                switch (yytext[i + 1]) {
                                    case 'n': yylval.string_val[j++] = '\n'; i++; break;
                                    case 't': yylval.string_val[j++] = '\t'; i++; break;
                                    case 'r': yylval.string_val[j++] = '\r'; i++; break;
                                    case '\\': yylval.string_val[j++] = '\\'; i++; break;
                                    case '"': yylval.string_val[j++] = '"'; i++; break;
                                    default: yylval.string_val[j++] = yytext[i];
                                }
                            } else {
                                yylval.string_val[j++] = yytext[i];
                            }
                        }
                        yylval.string_val[j] = '\0';
                        return STRING;
                    }

    /* Strings entre comillas simples */
'([^\\']|\\.)*'     {
                        yylval.string_val = (char *)malloc(strlen(yytext) - 1);
                        strncpy(yylval.string_val, yytext + 1, strlen(yytext) - 2);
                        yylval.string_val[strlen(yytext) - 2] = '\0';
                        return STRING;
                    }

    /* Variables (empiezan con $) */
\$[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.ptr_simbolo = (simbolo *)malloc(sizeof(simbolo));
                            strncpy(yylval.ptr_simbolo->nombre, yytext, sizeof(yylval.ptr_simbolo->nombre) - 1);
                            yylval.ptr_simbolo->scope = level;
                            yylval.ptr_simbolo->tipo = TYPE_UNDEFINED;
                            yylval.ptr_simbolo->inicializado = 0;
                            yylval.ptr_simbolo->linea = yylineno;
                            return VARIABLE;
                          }

    /* Identificadores de funciones */
[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.string_val = strdup(yytext);
                            return ID;
                        }

    /* Operadores y símbolos */
[-+*/()={};,]  { return *yytext; }

    /* Espacios y tabs */
[ \t]+          ;

    /* Nueva línea */
\n              { /* yylineno se incrementa automáticamente */ }

    /* Comentarios de una línea */
"//".*          ;

    /* Comentarios multilínea */
"/*"([^*]|\*+[^*/])*\*+"/" ;

    /* Caracteres no válidos */
.               {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "Carácter no válido: '%s'", yytext);
                    yyerror(msg);
                }

%%
