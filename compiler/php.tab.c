/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "php.y"

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


#line 92 "php.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "php.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PHP_OPEN = 3,                   /* PHP_OPEN  */
  YYSYMBOL_PHP_CLOSE = 4,                  /* PHP_CLOSE  */
  YYSYMBOL_TOK_ECHO = 5,                   /* TOK_ECHO  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_ELSEIF = 8,                     /* ELSEIF  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_FUNCTION = 14,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_NUMERO = 16,                    /* NUMERO  */
  YYSYMBOL_STRING = 17,                    /* STRING  */
  YYSYMBOL_ID = 18,                        /* ID  */
  YYSYMBOL_TRUE = 19,                      /* TRUE  */
  YYSYMBOL_FALSE = 20,                     /* FALSE  */
  YYSYMBOL_VARIABLE = 21,                  /* VARIABLE  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_GT = 27,                        /* GT  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_INC = 31,                       /* INC  */
  YYSYMBOL_DEC = 32,                       /* DEC  */
  YYSYMBOL_PLUS_ASSIGN = 33,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 34,              /* MINUS_ASSIGN  */
  YYSYMBOL_MULT_ASSIGN = 35,               /* MULT_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 36,                /* DIV_ASSIGN  */
  YYSYMBOL_CONCAT = 37,                    /* CONCAT  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_UMINUS = 42,                    /* UMINUS  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* '{'  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_46_ = 46,                       /* '='  */
  YYSYMBOL_47_ = 47,                       /* '('  */
  YYSYMBOL_48_ = 48,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_programa = 50,                  /* programa  */
  YYSYMBOL_sentencias = 51,                /* sentencias  */
  YYSYMBOL_sentencia = 52,                 /* sentencia  */
  YYSYMBOL_bloque = 53,                    /* bloque  */
  YYSYMBOL_declaracion = 54,               /* declaracion  */
  YYSYMBOL_asignacion = 55,                /* asignacion  */
  YYSYMBOL_echo_stmt = 56,                 /* echo_stmt  */
  YYSYMBOL_if_stmt = 57,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 58,                /* while_stmt  */
  YYSYMBOL_do_while_stmt = 59,             /* do_while_stmt  */
  YYSYMBOL_for_stmt = 60,                  /* for_stmt  */
  YYSYMBOL_expresion = 61,                 /* expresion  */
  YYSYMBOL_expresion_aritmetica = 62,      /* expresion_aritmetica  */
  YYSYMBOL_expresion_relacional = 63,      /* expresion_relacional  */
  YYSYMBOL_expresion_logica = 64           /* expresion_logica  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   423

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    48,    40,    38,     2,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
       2,    46,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    67,    72,    77,    85,    86,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   108,   112,
     116,   122,   140,   158,   173,   188,   200,   215,   233,   237,
     245,   252,   260,   268,   269,   270,   271,   281,   286,   291,
     296,   301,   305,   309,   313,   317,   321,   325,   331,   335,
     339,   343,   347,   351,   358,   362,   366
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PHP_OPEN",
  "PHP_CLOSE", "TOK_ECHO", "IF", "ELSE", "ELSEIF", "WHILE", "FOR", "DO",
  "BREAK", "CONTINUE", "FUNCTION", "RETURN", "NUMERO", "STRING", "ID",
  "TRUE", "FALSE", "VARIABLE", "EQ", "NE", "LE", "GE", "LT", "GT", "AND",
  "OR", "NOT", "INC", "DEC", "PLUS_ASSIGN", "MINUS_ASSIGN", "MULT_ASSIGN",
  "DIV_ASSIGN", "CONCAT", "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'",
  "'{'", "'}'", "'='", "'('", "')'", "$accept", "programa", "sentencias",
  "sentencia", "bloque", "declaracion", "asignacion", "echo_stmt",
  "if_stmt", "while_stmt", "do_while_stmt", "for_stmt", "expresion",
  "expresion_aritmetica", "expresion_relacional", "expresion_logica", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-22)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      71,   -43,   -43,     4,   156,   116,   -43,   -42,    -9,   -41,
     -30,   -28,   -35,   -23,   -20,   -43,   -43,   -43,   -43,   107,
      -9,    -9,   -43,    -9,   -43,   -43,    10,    26,    27,   -43,
     -43,    30,   -43,   330,   -43,   -43,   -43,   -43,   -43,   -43,
     374,    -9,    -9,    33,    22,   -43,   -43,   -43,   -43,    -9,
      -9,    -9,   -43,   -43,   196,   222,   -43,   -43,   -43,   -43,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,   -43,   249,   276,     1,    46,    49,   374,
     374,   374,   -43,   -43,   228,   228,    11,    11,    11,    11,
       2,   382,   -27,    38,    38,   -43,   -43,   -35,   -35,    -9,
      -9,    90,   -43,   352,   303,   -35,    33,   -43,   -43,    51,
     -35,   -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     6,     0,     0,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,    36,
       0,     0,     6,     0,     7,    16,     0,     0,     0,    12,
      13,     0,    14,     0,    33,    35,    34,     2,    19,    36,
      27,     0,     0,     0,     0,    17,    18,    25,    26,     0,
       0,     0,    56,    47,     0,     0,     9,     8,    11,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10,     0,     0,     0,     0,     0,    23,
      24,    22,    20,    41,    48,    49,    52,    53,    50,    51,
      54,    55,    46,    42,    43,    44,    45,     0,     0,     0,
       0,    28,    30,     0,     0,     0,     0,    31,    29,     0,
       0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,     0,   -43,   -12,   -43,   -38,   -43,   -43,   -43,
     -43,   -43,    -5,   -43,   -43,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    38,     5,    40,     6,    77,    41,    15,    16,    22,
      17,    18,    39,    71,    72,    52,    53,    42,    55,    43,
      45,    20,    54,    46,    60,    61,    62,    63,    64,    65,
      21,    78,    47,    48,    49,    50,    74,    75,    23,    68,
      69,    70,    71,    72,    79,    80,    81,    51,    68,    69,
      70,    71,    72,    56,    76,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,   109,    57,
      58,    -6,     1,    59,     2,    68,    -6,    -6,    71,    72,
      -6,    -6,    -6,    -6,    -6,   101,   102,    -6,    -6,    99,
      -6,    -6,    -6,   108,   103,   104,   100,   105,   111,   110,
       0,    -6,     0,     0,     0,     0,     0,     0,     0,     0,
      -6,     0,     0,     0,     0,    -6,    -3,     7,    -6,     0,
      37,     8,     9,     0,     0,    10,    11,    12,    13,    14,
       0,     0,    15,    16,     0,    17,    18,    19,    47,    48,
      49,    50,     0,     0,     0,     0,    20,     0,     0,     0,
     -21,     0,     0,    51,     0,    21,    -4,     7,     0,     0,
      22,     8,     9,    23,     0,    10,    11,    12,    13,    14,
       0,     0,    15,    16,     0,    17,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     7,     0,     0,
      22,     8,     9,    23,     0,    10,    11,    12,    13,    14,
       0,     0,    15,    16,     0,    17,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,     0,     0,
      22,    82,     0,    23,    60,    61,    62,    63,    64,    65,
      66,    67,    62,    63,    64,    65,     0,     0,     0,    68,
      69,    70,    71,    72,     0,    68,    69,    70,    71,    72,
      83,    60,    61,    62,    63,    64,    65,    66,    67,     0,
       0,     0,     0,     0,     0,     0,    68,    69,    70,    71,
      72,     0,     0,     0,     0,     0,     0,    97,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,     0,     0,    68,    69,    70,    71,    72,     0,     0,
       0,     0,     0,     0,    98,    60,    61,    62,    63,    64,
      65,    66,    67,     0,     0,     0,     0,     0,     0,     0,
      68,    69,    70,    71,    72,     0,     0,     0,     0,     0,
       0,   107,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,     0,    73,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,    68,
      69,    70,    71,    72,     0,   106,    60,    61,    62,    63,
      64,    65,    66,    67,    60,    61,    62,    63,    64,    65,
      66,    68,    69,    70,    71,    72,     0,     0,     0,    68,
      69,    70,    71,    72
};

static const yytype_int8 yycheck[] =
{
      12,    43,     2,     8,     0,    43,    47,    16,    17,    44,
      19,    20,    21,    40,    41,    20,    21,    47,    23,    47,
      43,    30,    22,    43,    22,    23,    24,    25,    26,    27,
      39,     9,    31,    32,    33,    34,    41,    42,    47,    37,
      38,    39,    40,    41,    49,    50,    51,    46,    37,    38,
      39,    40,    41,    43,    21,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   106,    43,
      43,     0,     1,    43,     3,    37,     5,     6,    40,    41,
       9,    10,    11,    12,    13,    97,    98,    16,    17,    43,
      19,    20,    21,   105,    99,   100,    47,     7,   110,    48,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    44,     0,     1,    47,    -1,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    20,    21,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      43,    -1,    -1,    46,    -1,    39,     0,     1,    -1,    -1,
      44,     5,     6,    47,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,     1,    -1,    -1,
      44,     5,     6,    47,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      44,    45,    -1,    47,    22,    23,    24,    25,    26,    27,
      28,    29,    24,    25,    26,    27,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    -1,    37,    38,    39,    40,    41,
      48,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    -1,    43,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    -1,    43,    22,    23,    24,    25,
      26,    27,    28,    29,    22,    23,    24,    25,    26,    27,
      28,    37,    38,    39,    40,    41,    -1,    -1,    -1,    37,
      38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    50,    51,    51,     0,     1,     5,     6,
       9,    10,    11,    12,    13,    16,    17,    19,    20,    21,
      30,    39,    44,    47,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     4,    43,    21,
      61,    47,    47,    47,    53,    43,    43,    31,    32,    33,
      34,    46,    61,    61,    51,    61,    43,    43,    43,    43,
      22,    23,    24,    25,    26,    27,    28,    29,    37,    38,
      39,    40,    41,    43,    61,    61,    21,    55,     9,    61,
      61,    61,    45,    48,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    48,    48,    43,
      47,    53,    53,    61,    61,     7,    43,    48,    53,    55,
      48,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    54,    55,    55,    55,    55,    55,    56,    57,    57,
      58,    59,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    64,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     1,     0,     2,     2,     2,
       2,     2,     1,     1,     1,     2,     1,     2,     2,     2,
       3,     1,     3,     3,     3,     2,     2,     2,     5,     7,
       5,     6,     9,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: PHP_OPEN sentencias PHP_CLOSE  */
#line 62 "php.y"
                                    {
                                        (yyval.nodo) = (yyvsp[-1].nodo);
                                        raiz_ast = (yyval.nodo);
                                        printf("\n=== COMPILACIÓN COMPLETADA ===\n");
                                    }
#line 1279 "php.tab.c"
    break;

  case 3: /* programa: PHP_OPEN sentencias  */
#line 67 "php.y"
                                     {
                                        (yyval.nodo) = (yyvsp[0].nodo);
                                        raiz_ast = (yyval.nodo);
                                        printf("\n=== COMPILACIÓN COMPLETADA (sin cierre) ===\n");
                                    }
#line 1289 "php.tab.c"
    break;

  case 4: /* programa: sentencias  */
#line 72 "php.y"
                                     {
                                        (yyval.nodo) = (yyvsp[0].nodo);
                                        raiz_ast = (yyval.nodo);
                                        printf("\n=== COMPILACIÓN COMPLETADA (sin etiquetas PHP) ===\n");
                                    }
#line 1299 "php.tab.c"
    break;

  case 5: /* programa: error  */
#line 77 "php.y"
                                     {
                                        yyerrok;
                                        printf("\n=== ERROR EN PROGRAMA ===\n");
                                        raiz_ast = NULL;
                                    }
#line 1309 "php.tab.c"
    break;

  case 6: /* sentencias: %empty  */
#line 85 "php.y"
                                     { (yyval.nodo) = crear_nodo_sentencias(yylineno); }
#line 1315 "php.tab.c"
    break;

  case 7: /* sentencias: sentencias sentencia  */
#line 86 "php.y"
                                    {
                                        if ((yyvsp[0].nodo)) {
                                            agregar_sentencia((yyvsp[-1].nodo), (yyvsp[0].nodo));
                                        }
                                        (yyval.nodo) = (yyvsp[-1].nodo);
                                    }
#line 1326 "php.tab.c"
    break;

  case 8: /* sentencia: asignacion ';'  */
#line 95 "php.y"
                                    { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 1332 "php.tab.c"
    break;

  case 9: /* sentencia: declaracion ';'  */
#line 96 "php.y"
                                     { (yyval.nodo) = NULL; /* Las declaraciones se manejan en asignación */ }
#line 1338 "php.tab.c"
    break;

  case 10: /* sentencia: expresion ';'  */
#line 97 "php.y"
                                    { (yyval.nodo) = NULL; /* Expresiones sueltas se ignoran */ }
#line 1344 "php.tab.c"
    break;

  case 11: /* sentencia: echo_stmt ';'  */
#line 98 "php.y"
                                    { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 1350 "php.tab.c"
    break;

  case 12: /* sentencia: if_stmt  */
#line 99 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1356 "php.tab.c"
    break;

  case 13: /* sentencia: while_stmt  */
#line 100 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1362 "php.tab.c"
    break;

  case 14: /* sentencia: for_stmt  */
#line 101 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1368 "php.tab.c"
    break;

  case 15: /* sentencia: do_while_stmt ';'  */
#line 102 "php.y"
                                    { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 1374 "php.tab.c"
    break;

  case 16: /* sentencia: bloque  */
#line 103 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1380 "php.tab.c"
    break;

  case 17: /* sentencia: BREAK ';'  */
#line 104 "php.y"
                                    {
                                        (yyval.nodo) = crear_nodo_break(yylineno);
                                        push_stack("BREAK", yylineno, "Salir del ciclo");
                                    }
#line 1389 "php.tab.c"
    break;

  case 18: /* sentencia: CONTINUE ';'  */
#line 108 "php.y"
                                    {
                                        (yyval.nodo) = crear_nodo_continue(yylineno);
                                        push_stack("CONTINUE", yylineno, "Continuar ciclo");
                                    }
#line 1398 "php.tab.c"
    break;

  case 19: /* sentencia: error ';'  */
#line 112 "php.y"
                                    { yyerrok; (yyval.nodo) = NULL; }
#line 1404 "php.tab.c"
    break;

  case 20: /* bloque: '{' sentencias '}'  */
#line 116 "php.y"
                                    {
                                        (yyval.nodo) = (yyvsp[-1].nodo);
                                    }
#line 1412 "php.tab.c"
    break;

  case 21: /* declaracion: VARIABLE  */
#line 122 "php.y"
                                    {
                                        simbolo *existe = buscar(tabla, (yyvsp[0].ptr_simbolo)->nombre);
                                        if (existe == NULL) {
                                            (yyvsp[0].ptr_simbolo)->tipo = TYPE_UNDEFINED;
                                            (yyvsp[0].ptr_simbolo)->inicializado = 0;
                                            insertar(&tabla, (yyvsp[0].ptr_simbolo));

                                            char detalles[512];
                                            snprintf(detalles, sizeof(detalles),
                                                    "Variable '%s' declarada sin tipo explícito",
                                                    (yyvsp[0].ptr_simbolo)->nombre);
                                            push_stack("DECLARACION", yylineno, detalles);
                                        }
                                        (yyval.nodo) = NULL;
                                    }
#line 1432 "php.tab.c"
    break;

  case 22: /* asignacion: VARIABLE '=' expresion  */
#line 140 "php.y"
                                    {
                                        // Validación semántica
                                        simbolo *var = buscar(tabla, (yyvsp[-2].ptr_simbolo)->nombre);
                                        if (var == NULL) {
                                            (yyvsp[-2].ptr_simbolo)->tipo = TYPE_UNDEFINED;  // Se determinará en tiempo de ejecución
                                            (yyvsp[-2].ptr_simbolo)->inicializado = 0;
                                            insertar(&tabla, (yyvsp[-2].ptr_simbolo));

                                            char detalles[512];
                                            snprintf(detalles, sizeof(detalles),
                                                    "Variable '%s' declarada implícitamente",
                                                    (yyvsp[-2].ptr_simbolo)->nombre);
                                            push_stack("ASIGNACION", yylineno, detalles);
                                        }

                                        // Crear nodo AST
                                        (yyval.nodo) = crear_nodo_asignacion((yyvsp[-2].ptr_simbolo)->nombre, (yyvsp[0].nodo), yylineno);
                                    }
#line 1455 "php.tab.c"
    break;

  case 23: /* asignacion: VARIABLE PLUS_ASSIGN expresion  */
#line 158 "php.y"
                                        {
                                            simbolo *var = buscar(tabla, (yyvsp[-2].ptr_simbolo)->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", (yyvsp[-2].ptr_simbolo)->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("ASIGNACION_COMPUESTA", yylineno, "+=");

                                            // Crear AST: $var = $var + expr
                                            NodoAST *var_nodo = crear_nodo_variable((yyvsp[-2].ptr_simbolo)->nombre, yylineno);
                                            NodoAST *suma = crear_nodo_binario(OP_SUMA, var_nodo, (yyvsp[0].nodo), yylineno);
                                            (yyval.nodo) = crear_nodo_asignacion((yyvsp[-2].ptr_simbolo)->nombre, suma, yylineno);
                                        }
#line 1475 "php.tab.c"
    break;

  case 24: /* asignacion: VARIABLE MINUS_ASSIGN expresion  */
#line 173 "php.y"
                                        {
                                            simbolo *var = buscar(tabla, (yyvsp[-2].ptr_simbolo)->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", (yyvsp[-2].ptr_simbolo)->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("ASIGNACION_COMPUESTA", yylineno, "-=");

                                            // Crear AST: $var = $var - expr
                                            NodoAST *var_nodo = crear_nodo_variable((yyvsp[-2].ptr_simbolo)->nombre, yylineno);
                                            NodoAST *resta = crear_nodo_binario(OP_RESTA, var_nodo, (yyvsp[0].nodo), yylineno);
                                            (yyval.nodo) = crear_nodo_asignacion((yyvsp[-2].ptr_simbolo)->nombre, resta, yylineno);
                                        }
#line 1495 "php.tab.c"
    break;

  case 25: /* asignacion: VARIABLE INC  */
#line 188 "php.y"
                                        {
                                            simbolo *var = buscar(tabla, (yyvsp[-1].ptr_simbolo)->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", (yyvsp[-1].ptr_simbolo)->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("INCREMENTO", yylineno, "++");

                                            (yyval.nodo) = crear_nodo_incremento((yyvsp[-1].ptr_simbolo)->nombre, yylineno);
                                        }
#line 1512 "php.tab.c"
    break;

  case 26: /* asignacion: VARIABLE DEC  */
#line 200 "php.y"
                                        {
                                            simbolo *var = buscar(tabla, (yyvsp[-1].ptr_simbolo)->nombre);
                                            if (var == NULL) {
                                                char msg[256];
                                                snprintf(msg, sizeof(msg),
                                                        "Variable '%s' no declarada", (yyvsp[-1].ptr_simbolo)->nombre);
                                                yyerror(msg);
                                            }
                                            push_stack("DECREMENTO", yylineno, "--");

                                            (yyval.nodo) = crear_nodo_decremento((yyvsp[-1].ptr_simbolo)->nombre, yylineno);
                                        }
#line 1529 "php.tab.c"
    break;

  case 27: /* echo_stmt: TOK_ECHO expresion  */
#line 215 "php.y"
                                    {
                                        // Detectar si es un salto de línea
                                        char *descripcion = "Imprimir valor";
                                        if ((yyvsp[0].nodo)->tipo == AST_LITERAL &&
                                            (yyvsp[0].nodo)->datos.literal.tipo_dato == TYPE_STRING) {
                                            if (strcmp((yyvsp[0].nodo)->datos.literal.valor.valor_str, "\\n") == 0 ||
                                                strcmp((yyvsp[0].nodo)->datos.literal.valor.valor_str, "\n") == 0) {
                                                descripcion = "Salto de línea";
                                            } else if (strlen((yyvsp[0].nodo)->datos.literal.valor.valor_str) == 0) {
                                                descripcion = "Línea vacía";
                                            }
                                        }
                                        push_stack("ECHO", yylineno, descripcion);
                                        (yyval.nodo) = crear_nodo_echo((yyvsp[0].nodo), yylineno);
                                    }
#line 1549 "php.tab.c"
    break;

  case 28: /* if_stmt: IF '(' expresion ')' bloque  */
#line 233 "php.y"
                                    {
                                        push_stack("IF", yylineno, "Bloque condicional");
                                        (yyval.nodo) = crear_nodo_if((yyvsp[-2].nodo), (yyvsp[0].nodo), NULL, yylineno);
                                    }
#line 1558 "php.tab.c"
    break;

  case 29: /* if_stmt: IF '(' expresion ')' bloque ELSE bloque  */
#line 238 "php.y"
                                    {
                                        push_stack("IF-ELSE", yylineno, "Bloque condicional con else");
                                        (yyval.nodo) = crear_nodo_if((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1567 "php.tab.c"
    break;

  case 30: /* while_stmt: WHILE '(' expresion ')' bloque  */
#line 245 "php.y"
                                    {
                                        push_stack("WHILE", yylineno, "Ciclo while");
                                        (yyval.nodo) = crear_nodo_while((yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1576 "php.tab.c"
    break;

  case 31: /* do_while_stmt: DO bloque WHILE '(' expresion ')'  */
#line 253 "php.y"
                                    {
                                        push_stack("DO-WHILE", yylineno, "Ciclo do-while");
                                        (yyval.nodo) = crear_nodo_do_while((yyvsp[-4].nodo), (yyvsp[-1].nodo), yylineno);
                                    }
#line 1585 "php.tab.c"
    break;

  case 32: /* for_stmt: FOR '(' asignacion ';' expresion ';' asignacion ')' bloque  */
#line 261 "php.y"
                                    {
                                        push_stack("FOR", yylineno, "Ciclo for");
                                        (yyval.nodo) = crear_nodo_for((yyvsp[-6].nodo), (yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1594 "php.tab.c"
    break;

  case 33: /* expresion: expresion_aritmetica  */
#line 268 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1600 "php.tab.c"
    break;

  case 34: /* expresion: expresion_logica  */
#line 269 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1606 "php.tab.c"
    break;

  case 35: /* expresion: expresion_relacional  */
#line 270 "php.y"
                                    { (yyval.nodo) = (yyvsp[0].nodo); }
#line 1612 "php.tab.c"
    break;

  case 36: /* expresion: VARIABLE  */
#line 271 "php.y"
                                    {
                                        simbolo *var = buscar(tabla, (yyvsp[0].ptr_simbolo)->nombre);
                                        if (var == NULL) {
                                            char msg[256];
                                            snprintf(msg, sizeof(msg),
                                                    "Variable '%s' no declarada", (yyvsp[0].ptr_simbolo)->nombre);
                                            yyerror(msg);
                                        }
                                        (yyval.nodo) = crear_nodo_variable((yyvsp[0].ptr_simbolo)->nombre, yylineno);
                                    }
#line 1627 "php.tab.c"
    break;

  case 37: /* expresion: NUMERO  */
#line 281 "php.y"
                                    {
                                        ValorDato valor;
                                        valor.valor_int = (yyvsp[0].int_val);
                                        (yyval.nodo) = crear_nodo_literal(TYPE_INT, valor, yylineno);
                                    }
#line 1637 "php.tab.c"
    break;

  case 38: /* expresion: STRING  */
#line 286 "php.y"
                                    {
                                        ValorDato valor;
                                        strncpy(valor.valor_str, (yyvsp[0].string_val), sizeof(valor.valor_str) - 1);
                                        (yyval.nodo) = crear_nodo_literal(TYPE_STRING, valor, yylineno);
                                    }
#line 1647 "php.tab.c"
    break;

  case 39: /* expresion: TRUE  */
#line 291 "php.y"
                                    {
                                        ValorDato valor;
                                        valor.valor_bool = 1;
                                        (yyval.nodo) = crear_nodo_literal(TYPE_BOOL, valor, yylineno);
                                    }
#line 1657 "php.tab.c"
    break;

  case 40: /* expresion: FALSE  */
#line 296 "php.y"
                                    {
                                        ValorDato valor;
                                        valor.valor_bool = 0;
                                        (yyval.nodo) = crear_nodo_literal(TYPE_BOOL, valor, yylineno);
                                    }
#line 1667 "php.tab.c"
    break;

  case 41: /* expresion: '(' expresion ')'  */
#line 301 "php.y"
                                    { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 1673 "php.tab.c"
    break;

  case 42: /* expresion_aritmetica: expresion '+' expresion  */
#line 305 "php.y"
                                    {
                                        push_stack("SUMA", yylineno, "+");
                                        (yyval.nodo) = crear_nodo_binario(OP_SUMA, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1682 "php.tab.c"
    break;

  case 43: /* expresion_aritmetica: expresion '-' expresion  */
#line 309 "php.y"
                                    {
                                        push_stack("RESTA", yylineno, "-");
                                        (yyval.nodo) = crear_nodo_binario(OP_RESTA, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1691 "php.tab.c"
    break;

  case 44: /* expresion_aritmetica: expresion '*' expresion  */
#line 313 "php.y"
                                    {
                                        push_stack("MULTIPLICACION", yylineno, "*");
                                        (yyval.nodo) = crear_nodo_binario(OP_MULT, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1700 "php.tab.c"
    break;

  case 45: /* expresion_aritmetica: expresion '/' expresion  */
#line 317 "php.y"
                                    {
                                        push_stack("DIVISION", yylineno, "/");
                                        (yyval.nodo) = crear_nodo_binario(OP_DIV, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1709 "php.tab.c"
    break;

  case 46: /* expresion_aritmetica: expresion CONCAT expresion  */
#line 321 "php.y"
                                    {
                                        push_stack("CONCATENACION", yylineno, ".");
                                        (yyval.nodo) = crear_nodo_binario(OP_CONCAT, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1718 "php.tab.c"
    break;

  case 47: /* expresion_aritmetica: '-' expresion  */
#line 325 "php.y"
                                    {
                                        (yyval.nodo) = crear_nodo_unario(OP_UMINUS, (yyvsp[0].nodo), yylineno);
                                    }
#line 1726 "php.tab.c"
    break;

  case 48: /* expresion_relacional: expresion EQ expresion  */
#line 331 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, "==");
                                        (yyval.nodo) = crear_nodo_binario(OP_EQ, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1735 "php.tab.c"
    break;

  case 49: /* expresion_relacional: expresion NE expresion  */
#line 335 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, "!=");
                                        (yyval.nodo) = crear_nodo_binario(OP_NE, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1744 "php.tab.c"
    break;

  case 50: /* expresion_relacional: expresion LT expresion  */
#line 339 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, "<");
                                        (yyval.nodo) = crear_nodo_binario(OP_LT, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1753 "php.tab.c"
    break;

  case 51: /* expresion_relacional: expresion GT expresion  */
#line 343 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, ">");
                                        (yyval.nodo) = crear_nodo_binario(OP_GT, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1762 "php.tab.c"
    break;

  case 52: /* expresion_relacional: expresion LE expresion  */
#line 347 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, "<=");
                                        (yyval.nodo) = crear_nodo_binario(OP_LE, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1771 "php.tab.c"
    break;

  case 53: /* expresion_relacional: expresion GE expresion  */
#line 351 "php.y"
                                    {
                                        push_stack("COMPARACION", yylineno, ">=");
                                        (yyval.nodo) = crear_nodo_binario(OP_GE, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1780 "php.tab.c"
    break;

  case 54: /* expresion_logica: expresion AND expresion  */
#line 358 "php.y"
                                    {
                                        push_stack("AND_LOGICO", yylineno, "&&");
                                        (yyval.nodo) = crear_nodo_binario(OP_AND, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1789 "php.tab.c"
    break;

  case 55: /* expresion_logica: expresion OR expresion  */
#line 362 "php.y"
                                    {
                                        push_stack("OR_LOGICO", yylineno, "||");
                                        (yyval.nodo) = crear_nodo_binario(OP_OR, (yyvsp[-2].nodo), (yyvsp[0].nodo), yylineno);
                                    }
#line 1798 "php.tab.c"
    break;

  case 56: /* expresion_logica: NOT expresion  */
#line 366 "php.y"
                                    {
                                        push_stack("NOT_LOGICO", yylineno, "!");
                                        (yyval.nodo) = crear_nodo_unario(OP_NOT, (yyvsp[0].nodo), yylineno);
                                    }
#line 1807 "php.tab.c"
    break;


#line 1811 "php.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 372 "php.y"


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
