/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "tabla.y"

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

using namespace std;

char lexema[60];
int yylex();
void yyerror(char *msg);
void actualiza();

int bucle_activado[100];
int bucleF=0;
int while_activado[100];
int whileI = 0;
map<int, int> whileMap;

int VERBOSE = 0;
int VERBOSE_ACTUALIZA = 0;

typedef struct{
  char nombre [60];
  double valor ;
  int token;
}tipoTS;

tipoTS TablaSim[100];
int nSim=0;

typedef struct{
	string nombre;
	int inicio;
	int fin;
}tipoFunc;

tipoFunc TablaFunc[100];
int nFunc=0;
map<int, int> funciones_pos;   // NO LLEGO A USAR ESTO
map<string, vector<int>> funciones_posiciones;   // NOMBRE DE LA FUNCION, DONDE EMPIEZA, DONDE ACABAM A DONDE REGRESA
map<int, string> llamada_info;
string tmp_name;
string tmp_call_name;
string current_function;

string tmp_func_arg;
map<string,vector<int>> funcion_argumentos;

int nmbr=0;


int retornoFunc = 0 ;


typedef struct{
  int op;
  int a1;
  int a2;
  int a3;
}tipocodigo;

int posicion_while[100];
int posicion_while_I = 0;
int posicion_for = 0;
int cotaI = 0;
int cota_inferior[100];
int cota_superior[100];

map<int, int> cotas;

int cx=-1;
tipocodigo TCodigo[100];
void generarCodigo(int , int ,int , int);
int localizaSimb(char *,int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();

void asignar_cotas(int x,int d){
	cota_inferior[cotaI] = (int)TablaSim[x].valor;
	cota_superior[cotaI] = (int)TablaSim[d].valor;
}


#line 163 "tabla.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_TABLA_TAB_H_INCLUDED
# define YY_YY_TABLA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAMA = 258,
    PROG_INICIO = 259,
    PROG_FIN = 260,
    DESDE = 261,
    FIN_DESDE = 262,
    HASTA = 263,
    HACER = 264,
    BUCLE = 265,
    BUCLE_1 = 266,
    BUCLE_2 = 267,
    SALTARF3 = 268,
    MIENTRAS = 269,
    FIN_MIENTRAS = 270,
    SALTARF4 = 271,
    SALTARF5 = 272,
    WHILE = 273,
    SI = 274,
    FIN_SI = 275,
    SINO = 276,
    SALTARF1 = 277,
    SALTARF2 = 278,
    SUMAR = 279,
    RESTAR = 280,
    MULTIPLICAR = 281,
    DIVIDIR = 282,
    MODULO = 283,
    PARENTESIS = 284,
    RAIZ = 285,
    POT = 286,
    MAYOR = 287,
    MENOR = 288,
    IGUAL = 289,
    MAYOR_IGUAL = 290,
    MENOR_IGUAL = 291,
    IMPRIMIR = 292,
    ASIGNAR = 293,
    DEF = 294,
    CALL = 295,
    POSFUNCION = 296,
    SALIRFUNCION = 297,
    LLAMADAFUNC = 298,
    NUM = 299,
    ID = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 94 "tabla.y"

	float ftype;
	char *stype;
	int itype;

#line 258 "tabla.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TABLA_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

#define YYUNDEFTOK  2
#define YYMAXUTOK   300

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    59,     2,     2,     2,     2,
      48,    49,    60,    57,    53,    58,    47,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    52,
      56,    54,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   119,   120,   121,   122,   123,   124,   125,
     126,   128,   128,   144,   144,   147,   148,   149,   150,   151,
     154,   156,   153,   168,   169,   175,   179,   167,   187,   193,
     194,   186,   208,   214,   218,   207,   226,   226,   229,   231,
     233,   235,   241,   249,   250,   248,   255,   257,   259,   261,
     262,   264,   266,   267,   268,   270,   277,   279,   280
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAMA", "PROG_INICIO", "PROG_FIN",
  "DESDE", "FIN_DESDE", "HASTA", "HACER", "BUCLE", "BUCLE_1", "BUCLE_2",
  "SALTARF3", "MIENTRAS", "FIN_MIENTRAS", "SALTARF4", "SALTARF5", "WHILE",
  "SI", "FIN_SI", "SINO", "SALTARF1", "SALTARF2", "SUMAR", "RESTAR",
  "MULTIPLICAR", "DIVIDIR", "MODULO", "PARENTESIS", "RAIZ", "POT", "MAYOR",
  "MENOR", "IGUAL", "MAYOR_IGUAL", "MENOR_IGUAL", "IMPRIMIR", "ASIGNAR",
  "DEF", "CALL", "POSFUNCION", "SALIRFUNCION", "LLAMADAFUNC", "NUM", "ID",
  "':'", "'.'", "'('", "')'", "'{'", "'}'", "';'", "','", "'='", "'>'",
  "'<'", "'+'", "'-'", "'#'", "'*'", "'/'", "'['", "']'", "$accept", "s",
  "listaInstr", "defFunc", "@1", "callFunc", "$@2", "args", "asignacion",
  "@3", "$@4", "bucle_for", "$@5", "@6", "@7", "$@8", "bucle_while", "@9",
  "@10", "$@11", "bloque_if", "@12", "@13", "$@14", "otro", "condicion",
  "imprimir", "$@15", "$@16", "expresion", "producto", "agrupacion",
  "valor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    58,    46,    40,    41,
     123,   125,    59,    44,    61,    62,    60,    43,    45,    35,
      42,    47,    91,    93
};
# endif

#define YYPACT_NINF -40

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       6,   -29,    31,    33,   -40,     1,   -16,    -9,    14,    23,
      25,    49,   -40,    45,     1,     1,     1,     1,     1,     1,
       1,   -40,   -40,    71,    23,    23,    39,    41,    23,    40,
     -26,   -40,   -40,   -40,   -40,    48,    57,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -16,    46,    34,    56,    23,    23,
     -36,    23,    23,    23,   -40,    23,    23,    58,    59,    23,
     -40,    99,   -40,    55,   -12,    21,   -40,   -33,     2,   -40,
     -26,   -26,   -26,    60,   -40,   -40,    12,    12,    40,   -40,
      64,    23,    23,    40,    23,    40,    65,   -40,    23,   -40,
     -40,   -40,   -39,   -37,    61,   -40,     1,    40,    40,    40,
       1,    15,    66,    32,    62,   -40,    72,   102,   100,   -40,
       1,   -40,   -40,   -40,     1,   -40,   -40,    68,   114,   -40,
     -40,   -40,   -40,   -40,   101,   -40,    73,   -40,   -40,     1,
      74,   -40
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,    10,     0,     0,     0,     0,
       0,     0,    20,     0,    10,    10,    10,    10,    10,    10,
      10,    57,    58,     0,     0,     0,     0,     0,     0,    43,
      49,    52,    56,    11,    13,     0,     0,     8,     9,     3,
       5,     6,     4,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       2,     0,    28,     0,     0,     0,    32,     0,     0,    55,
      46,    47,    48,     0,    50,    51,    19,    19,    21,    23,
       0,     0,     0,    38,     0,    39,     0,    53,     0,    45,
      18,    16,     0,     0,     0,    24,    10,    40,    41,    42,
      10,     0,     0,     0,     0,    22,     0,     0,     0,    54,
      10,    17,    15,    14,    10,    29,    33,     0,     0,    30,
      34,    12,    25,    31,    37,    26,     0,    35,    27,    10,
       0,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -14,   -40,   -40,   -40,   -40,    47,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   103,   -40,   -40,   -40,    -1,
      -8,    29,     5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    13,    14,    57,    15,    58,    92,    16,    35,
      94,    17,    95,   106,   125,   128,    18,    80,   119,   123,
      19,    86,   120,   124,   127,    45,    20,    54,    73,    46,
      30,    31,    32
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    38,    39,    40,    41,    42,    43,     6,    29,     1,
     102,    23,   104,    69,   103,     7,   103,     3,    26,    27,
       8,    51,    52,    53,    51,    52,    53,    50,    21,    22,
      87,     4,    21,    22,    55,    56,    28,     5,     9,    24,
      10,    11,    82,    70,    71,    72,    12,    67,    68,    61,
      36,    26,    27,    26,    27,    88,    90,    91,    78,    51,
      52,    53,    25,    83,    85,    21,    22,    21,    22,    28,
      33,    28,    51,    52,    53,    84,   111,   112,   109,    44,
      97,    98,   107,    99,    74,    75,   108,   101,    63,    64,
      65,    51,    52,    53,    34,    62,   117,    51,    52,    53,
     118,    48,    59,    49,    60,    66,    76,    77,    79,    81,
      96,   100,    89,   105,   113,   130,   110,   115,   114,   121,
     116,   122,   126,   129,    93,   131,     0,     0,    47
};

static const yytype_int16 yycheck[] =
{
      14,    15,    16,    17,    18,    19,    20,     6,     9,     3,
      49,     6,    49,    49,    53,    14,    53,    46,    30,    31,
      19,    57,    58,    59,    57,    58,    59,    28,    44,    45,
      63,     0,    44,    45,    60,    61,    48,     4,    37,    48,
      39,    40,    54,    51,    52,    53,    45,    48,    49,    44,
       5,    30,    31,    30,    31,    53,    44,    45,    59,    57,
      58,    59,    48,    64,    65,    44,    45,    44,    45,    48,
      45,    48,    57,    58,    59,    54,    44,    45,    63,     8,
      81,    82,    96,    84,    55,    56,   100,    88,    54,    55,
      56,    57,    58,    59,    45,    49,   110,    57,    58,    59,
     114,    62,    54,    62,    47,    49,    48,    48,     9,    54,
      46,    46,    52,    52,    52,   129,    50,    15,    46,    51,
      20,     7,    21,    50,    77,    51,    -1,    -1,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    65,    46,     0,     4,     6,    14,    19,    37,
      39,    40,    45,    66,    67,    69,    72,    75,    80,    84,
      90,    44,    45,    96,    48,    48,    30,    31,    48,    93,
      94,    95,    96,    45,    45,    73,     5,    66,    66,    66,
      66,    66,    66,    66,     8,    89,    93,    89,    62,    62,
      93,    57,    58,    59,    91,    60,    61,    68,    70,    54,
      47,    96,    49,    54,    55,    56,    49,    93,    93,    49,
      94,    94,    94,    92,    95,    95,    48,    48,    93,     9,
      81,    54,    54,    93,    54,    93,    85,    63,    53,    52,
      44,    45,    71,    71,    74,    76,    46,    93,    93,    93,
      46,    93,    49,    53,    49,    52,    77,    66,    66,    63,
      50,    44,    45,    52,    46,    15,    20,    66,    66,    82,
      86,    51,     7,    83,    87,    78,    21,    88,    79,    50,
      66,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    68,    67,    70,    69,    71,    71,    71,    71,    71,
      73,    74,    72,    76,    77,    78,    79,    75,    81,    82,
      83,    80,    85,    86,    87,    84,    88,    88,    89,    89,
      89,    89,    89,    91,    92,    90,    93,    93,    93,    93,
      94,    94,    94,    95,    95,    95,    95,    96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     2,     2,     2,     2,     2,     2,     2,
       0,     0,     9,     0,     7,     3,     1,     3,     1,     0,
       0,     0,     6,     0,     0,     0,     0,    12,     0,     0,
       0,    10,     0,     0,     0,    11,     4,     0,     3,     3,
       4,     4,     4,     0,     0,     5,     3,     3,     3,     1,
       3,     3,     1,     4,     6,     3,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
  case 11:
#line 128 "tabla.y"
    {
					tmp_name = (yyvsp[0].stype);
					generarCodigo(POSFUNCION,cx+1,'-','-');
							(yyval.itype)=cx;
						}
#line 1450 "tabla.tab.c"
    break;

  case 12:
#line 134 "tabla.y"
    {
						generarCodigo(SALIRFUNCION,cx+1,'-','-');
						TCodigo[(yyvsp[-6].itype)].a2=cx;
						funciones_posiciones.insert({tmp_name,{TCodigo[(yyvsp[-6].itype)].a1,TCodigo[(yyvsp[-6].itype)].a2,0}});
							
														(yyval.itype) = cx;
	
						if(VERBOSE) printf("SALIRFUNCION saliendo ... \n");(yyval.itype) = cx;
						}
#line 1464 "tabla.tab.c"
    break;

  case 13:
#line 144 "tabla.y"
    {tmp_call_name=(yyvsp[0].stype);}
#line 1470 "tabla.tab.c"
    break;

  case 14:
#line 144 "tabla.y"
    {llamada_info.insert({cx+1,tmp_call_name});
			generarCodigo(LLAMADAFUNC,'-','-','-');}
#line 1477 "tabla.tab.c"
    break;

  case 15:
#line 147 "tabla.y"
    {(yyval.itype)=localizaSimb((yyvsp[0].stype),ID);}
#line 1483 "tabla.tab.c"
    break;

  case 16:
#line 148 "tabla.y"
    {(yyval.itype)=localizaSimb((yyvsp[0].stype),NUM);}
#line 1489 "tabla.tab.c"
    break;

  case 17:
#line 149 "tabla.y"
    { (yyval.itype)=localizaSimb((yyvsp[0].stype),NUM); }
#line 1495 "tabla.tab.c"
    break;

  case 18:
#line 150 "tabla.y"
    { (yyval.itype)=localizaSimb((yyvsp[0].stype),NUM); }
#line 1501 "tabla.tab.c"
    break;

  case 20:
#line 154 "tabla.y"
    {(yyval.ftype) = localizaSimb((yyvsp[0].stype),ID); }
#line 1507 "tabla.tab.c"
    break;

  case 21:
#line 156 "tabla.y"
    { 
					  if(VERBOSE){ printf("generando en asignacion...\n");
					  printf("$2 es %f y $4 es %f \n");
					  //printf("TCodigo[%d].valor es %f \n",$2,TCodigo[$2].a1);

					}
					  generarCodigo(ASIGNAR,(yyvsp[-2].ftype),(yyvsp[0].ftype),'-');
					}
#line 1520 "tabla.tab.c"
    break;

  case 23:
#line 168 "tabla.y"
    { bucleF=100; }
#line 1526 "tabla.tab.c"
    break;

  case 24:
#line 169 "tabla.y"
    { 
							generarCodigo(SALTARF3,(yyvsp[-4].ftype),(yyvsp[-2].ftype),'-');
							posicion_for=cx; 
							(yyval.itype) = cx; 
						}
#line 1536 "tabla.tab.c"
    break;

  case 25:
#line 175 "tabla.y"
    { 
							generarCodigo(BUCLE,'?','-','-'); 
							(yyval.itype) = cx;
						}
#line 1545 "tabla.tab.c"
    break;

  case 26:
#line 179 "tabla.y"
    { TCodigo[(yyvsp[-4].itype)].a3=cx; }
#line 1551 "tabla.tab.c"
    break;

  case 27:
#line 180 "tabla.y"
    { 
							//if(VERBOSE) printf("$11 es %d \n",$11);
							TCodigo[(yyvsp[-1].itype)].a1=cx+1 ;
							TCodigo[(yyvsp[-1].itype)].a2=posicion_for ;
						}
#line 1561 "tabla.tab.c"
    break;

  case 28:
#line 187 "tabla.y"
    {
							generarCodigo(SALTARF4,(yyvsp[-1].itype),'-','-');
							posicion_while[posicion_while_I++]=cx;
							(yyval.itype)=cx;
						}
#line 1571 "tabla.tab.c"
    break;

  case 29:
#line 193 "tabla.y"
    {generarCodigo(WHILE,'?','-','-');(yyval.itype)=cx;}
#line 1577 "tabla.tab.c"
    break;

  case 30:
#line 194 "tabla.y"
    {
							if(VERBOSE) printf("$5 es %d TCodigo[$5].a2 sera %d\n",(yyvsp[-4].itype),cx);
							TCodigo[(yyvsp[-4].itype)].a2=cx;}
#line 1585 "tabla.tab.c"
    break;

  case 31:
#line 197 "tabla.y"
    {
							if(VERBOSE) printf("$9 es %d , TCodigo[$9].a1 sera %d \n",(yyvsp[-1].itype),cx+1);
							TCodigo[(yyvsp[-1].itype)].a1=cx+1;
							TCodigo[(yyvsp[-1].itype)].a2=posicion_while[--posicion_while_I];
						}
#line 1595 "tabla.tab.c"
    break;

  case 32:
#line 208 "tabla.y"
    {
						if(VERBOSE) printf("generando En el bloque_if...\n");
						generarCodigo(SALTARF1,(yyvsp[-1].itype),'-','-');
						if(VERBOSE) printf("$3 es %d\n",(yyvsp[-1].itype));(yyval.itype) = cx;
					}
#line 1605 "tabla.tab.c"
    break;

  case 33:
#line 214 "tabla.y"
    { 
						generarCodigo(SALTARF2,'?','-','-');
						if(VERBOSE) printf("Saltarf2 generando en bloque_if, ? es %d\n",'?');(yyval.itype) = cx;
					}
#line 1614 "tabla.tab.c"
    break;

  case 34:
#line 218 "tabla.y"
    {
						TCodigo[(yyvsp[-4].itype)].a2=cx+1;
						if(VERBOSE) printf("Valor de $5: %d Valor de cx: %d TCodigo[$5].a2 es %f \n",(yyvsp[-4].itype),cx,(double)cx+1);
					}
#line 1623 "tabla.tab.c"
    break;

  case 35:
#line 223 "tabla.y"
    { if(VERBOSE) printf("$9 es %d, TCodigo[$9].a1 sera %d\n",(yyvsp[-2].itype),cx+1);TCodigo[(yyvsp[-2].itype)].a1=cx+1; }
#line 1629 "tabla.tab.c"
    break;

  case 38:
#line 230 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(MAYOR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.itype) = i; }
#line 1635 "tabla.tab.c"
    break;

  case 39:
#line 232 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(MENOR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.itype) = i; }
#line 1641 "tabla.tab.c"
    break;

  case 40:
#line 234 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(IGUAL,i,(yyvsp[-3].ftype),(yyvsp[0].ftype)); (yyval.itype) = i; }
#line 1647 "tabla.tab.c"
    break;

  case 41:
#line 236 "tabla.y"
    { 
						int i = GenVarTemp(); 
						generarCodigo(MAYOR_IGUAL,i,(yyvsp[-3].ftype),(yyvsp[0].ftype)); 
						(yyval.itype)=i;
					}
#line 1657 "tabla.tab.c"
    break;

  case 42:
#line 242 "tabla.y"
    { 
						if(VERBOSE) printf("genero codigo En la condicion...\n");
						int i = GenVarTemp(); 
						generarCodigo(MENOR_IGUAL,i,(yyvsp[-3].ftype),(yyvsp[0].ftype)); (yyval.itype)=i;
					}
#line 1667 "tabla.tab.c"
    break;

  case 43:
#line 249 "tabla.y"
    { generarCodigo(IMPRIMIR,(yyvsp[0].ftype),'-','-'); }
#line 1673 "tabla.tab.c"
    break;

  case 44:
#line 250 "tabla.y"
    { if(VERBOSE) printf("Visualizando:=%d\n",(yyvsp[-1].ftype)); }
#line 1679 "tabla.tab.c"
    break;

  case 46:
#line 256 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(SUMAR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.ftype) = i;}
#line 1685 "tabla.tab.c"
    break;

  case 47:
#line 258 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(RESTAR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.ftype) = i;}
#line 1691 "tabla.tab.c"
    break;

  case 48:
#line 260 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(MODULO,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.ftype) = i;}
#line 1697 "tabla.tab.c"
    break;

  case 50:
#line 263 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(MULTIPLICAR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.ftype)=i;}
#line 1703 "tabla.tab.c"
    break;

  case 51:
#line 265 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(DIVIDIR,i,(yyvsp[-2].ftype),(yyvsp[0].ftype)); (yyval.ftype)=i;}
#line 1709 "tabla.tab.c"
    break;

  case 53:
#line 267 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(RAIZ,i,(yyvsp[-1].ftype),'-'); (yyval.ftype) = i; }
#line 1715 "tabla.tab.c"
    break;

  case 54:
#line 268 "tabla.y"
    { int i = GenVarTemp(); generarCodigo(POT,i,(yyvsp[-3].ftype),(yyvsp[-1].ftype)); (yyval.ftype) = i; }
#line 1721 "tabla.tab.c"
    break;

  case 55:
#line 271 "tabla.y"
    {
					if(VERBOSE) printf("Generando en parentesis...\n");
					int i = GenVarTemp(); 
					generarCodigo(PARENTESIS,i,(yyvsp[-1].ftype),'-'); 
					(yyval.ftype)=i;
				}
#line 1732 "tabla.tab.c"
    break;

  case 56:
#line 277 "tabla.y"
    {(yyval.ftype)=(yyvsp[0].ftype);}
#line 1738 "tabla.tab.c"
    break;

  case 57:
#line 279 "tabla.y"
    { (yyval.ftype)=localizaSimb((yyvsp[0].stype),NUM);}
#line 1744 "tabla.tab.c"
    break;

  case 58:
#line 280 "tabla.y"
    { (yyval.ftype)=localizaSimb((yyvsp[0].stype),ID);}
#line 1750 "tabla.tab.c"
    break;


#line 1754 "tabla.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 283 "tabla.y"


map<int, string> operaName = {{MAYOR, "mayor"}, {MENOR, "menor"}, {MAYOR_IGUAL, "mayor igual"}, 
    {MENOR_IGUAL, "menor igual"}, {IGUAL, "igual"}, {SUMAR, "sumar"}, {RESTAR, "restar"}, {MODULO, "modulo"},
    {MULTIPLICAR, "multiplicar"}, {DIVIDIR, "dividir"}, {PARENTESIS, "parentesis"}, 
	{RAIZ, "raiz"}, {POT, "pot"},
    {SALTARF1, "saltar f1"}, {SALTARF2, "saltar f2"}, {SALTARF3, "saltar f3"},
    {SALTARF4, "saltar f4"}, {SALTARF5, "saltar f5"},
    {BUCLE, "bucle"}, {WHILE, "while"}, {ASIGNAR, "asignar"}, {IMPRIMIR, "imprimir"} ,{POSFUNCION,"definir"} , {SALIRFUNCION,"salirFuncion"}, {LLAMADAFUNC,"llamandoFuncion"}};

int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,ID);
}

void imprimeTablaSim(){
  int i;
  for ( i=0;i<nSim;i++){
    printf("%d nombre=%s tok=%d valor=%lf\n", i , TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for ( i=0;i<=cx;i++){
    printf("%03d %s a1=%d a2=%d a3=%d\n", i, operaName[TCodigo[i].op].c_str(),TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);

  }
}

void generarCodigo(int op, int a1,int a2, int a3){
  cx++;
  //printf("XD %d\n",cx);
  //printf("Poniendo en la tabla de codigo:\n");
  //printf("op=%d a1=%d a2=%d a3=%d \n",op,a1,a2,a3);
  TCodigo[cx].op=op;
  TCodigo[cx].a1=a1;
  TCodigo[cx].a2=a2;
  TCodigo[cx].a3=a3;
  //printf("Despues de modificar la tabla de codigo...\n");
  //imprimeTablaCod();
}

int localizaSimb(char *nom,int tok){
  int i;
  for (i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token=tok;
  if (tok==ID) {  /*
  	printf("Parece que es un ID .... \n");
  	cout << "Tenemos... " << tok << "\n"; 
	cout << "TablaSim[nSim].nombre = **  " << TablaSim[nSim].nombre << " ** esto\n";*/
	TablaSim[nSim].valor=0.0;
	}
  if (tok==NUM) {  
  	sscanf(nom,"%lf",&TablaSim[nSim].valor);
	}
 	 nSim++;
  return nSim-1;
}



void yyerror(char *msg){
  printf("ERROR:%s \n",msg);
}



void actualiza(){
	
	string name_function;
	int i,a1,a2,a3,op,j,temp;
	if(VERBOSE_ACTUALIZA) printf("######## cx = %d ######\n",cx);

	for( i=0; i<=cx; i++ ){

		if(VERBOSE_ACTUALIZA) printf("******* Iteracion %d \n: ********",i);
		op = TCodigo[i].op;
		a1 = TCodigo[i].a1;
		a2 = TCodigo[i].a2;
		a3 = TCodigo[i].a3;

        if(VERBOSE_ACTUALIZA) cout << "operacion : " << operaName[op] << " " << TablaSim[a1].nombre << " " << TablaSim[a2].nombre << " " << TablaSim[a3].nombre << endl;

		if(op==MAYOR){
			if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}
		if(op==MENOR){
			if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}
		if(op==MAYOR_IGUAL){
			if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}
		if(op==MENOR_IGUAL){
			if (TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}
		if(op==IGUAL){
			if (abs(TablaSim[a2].valor-TablaSim[a3].valor) < 0.0001) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}

		if(op==SUMAR){
			TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
		}
		if(op==RESTAR){TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;}
        if(op==MODULO){TablaSim[a1].valor = fmod(round(TablaSim[a2].valor), round(TablaSim[a3].valor));}
		//if(op==MODULO){TablaSim[a1].valor = (int) round(TablaSim[a2].valor) % (int) round(TablaSim[a3].valor);}
		if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
		if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
		if(op==RAIZ) TablaSim[a1].valor = sqrt(TablaSim[a2].valor);
		if(op==POT) TablaSim[a1].valor = pow(TablaSim[a2].valor, TablaSim[a3].valor);
		if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;

		if(op==SALTARF1){
			printf("Bloque if, SALTARF1\n");
			printf("a1=%d a2=%d TablaSim[a1].valor=%f\n",a1,a2,TablaSim[a1].valor);

        	if(TablaSim[a1].valor==0){printf("En saltar f1, la condicion no se cumplio"); i=a2-1;printf("i es %d , a2 es %d \n",i,a2); };
        	printf("##Ahora i vale %d ##\n",i);
    		printf("La siguiente operacion: %d\n",TCodigo[i+1].op);
		}
		if(op==SALTARF2){ 
			i=a1-1;
			printf("##### SALTARF2 ahora i vale %d \n #####",i);
		}
		if(op==SALTARF3){
			if(!bucle_activado[cotas[i]])
				cotas.insert({i, cotaI});
				asignar_cotas(a1,a2);
				cotaI++;
			bucle_activado[cotas[i]] = 1;
			if(cota_inferior[cotas[i]] <= cota_superior[cotas[i]]){
				cota_inferior[cotas[i]]++;	
			}
			else{
				bucle_activado[cotas[i]] = 0;
				i = a3 - 1;
			}
		}
		if(op==BUCLE) {
			if(bucle_activado[cotas[i]]){
				i = a2-1;
			}
			else{
				i = a1-1;
			}
		}

		if(op==SALTARF4){
			if(whileMap.size() == 0) whileMap.insert({i, whileI++});
			if(whileMap.insert({i, whileI}).second == true) whileI++;
			
			while_activado[whileMap[i]]=1;
			if(TablaSim[a1].valor==0){while_activado[whileMap[i]]=0;i = a2-1;}
		}
		if(op==WHILE){
			if(while_activado[whileMap[a2]]){
				i = a2-2;
			}
		}

if(op==POSFUNCION){

			i = a2;
		}

		if(op==LLAMADAFUNC){
			name_function = llamada_info[i];
			current_function = llamada_info[i];
			funciones_posiciones[name_function][2] = i;

			i = funciones_posiciones[name_function][0];
		}

		if(op==SALIRFUNCION){
			i = funciones_posiciones[current_function][2];
		}


		if(op==ASIGNAR) {
			if(VERBOSE){
				printf("Se procedera con la asignacion...\n");
				printf("op es %d a1 es %d a2 es %d a3 es %d\n",op,a1,a2,a3);
				printf("TablaSim[a1].valor sera TablaSim[a2].valor, que es %f\n", TablaSim[a2].valor);
				}
			TablaSim[a1].valor = TablaSim[a2].valor;
		}

		if(op==IMPRIMIR) {
			printf("# %F\n", TablaSim[a1].valor);
		}

		if(VERBOSE_ACTUALIZA) printf("tabla de simbolos antes de actualizarse\n");
		if(VERBOSE_ACTUALIZA) imprimeTablaSim();

		if(VERBOSE_ACTUALIZA) printf("********************************\n\n");

	}

	/*
	for(auto k : whileMap) {
		printf("---- i : %d  whileI : %d\n", k.first, k.second);
	}
	*/

}


int main(int argc, char *argv[]) {
	if(argc > 1 && argv[1][0] == '-') {
		for(int i = 1; argv[1][i] != '\0'; i++) {
			if(argv[1][i] == 'A') VERBOSE_ACTUALIZA = 1;
			if(argv[1][i] == 'V') VERBOSE = 1;
		}
		
	} 

	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
	//printf("tabla de codigos\n");
	/*		imprimeTablaCod();

	printf("tabla de simbolos antes de actualizarse\n");
	imprimeTablaSim();	
	printf("*********************");
	*/
	actualiza();
	printf("tabla de codigos\n");
	imprimeTablaCod();
	printf("tabla de simbolos\n");
	imprimeTablaSim();
	
    
	return 0;
}





