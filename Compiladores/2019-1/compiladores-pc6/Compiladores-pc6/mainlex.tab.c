/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mainlex.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char lexema[60];
void yyerror(char *msg);

//tabla de simbolos
typedef struct{
  char nombre [60];
  double valor ;
  int token;
}tipoTS;


tipoTS TablaSim[100];
int nSim=0;

//tabla de codigo
typedef struct{
  int op;
  int a1;
  int a2;
  int a3;
}tipocodigo;

int cx=-1;
tipocodigo TCodigo[100];
void generarCodigo(int , int ,int , int);
int localizaSimb(char *,int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();
int generar=1;


#line 105 "mainlex.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "mainlex.tab.h".  */
#ifndef YY_YY_MAINLEX_TAB_H_INCLUDED
# define YY_YY_MAINLEX_TAB_H_INCLUDED
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
    MAYOR = 258,
    MENOR = 259,
    ESIGUAL = 260,
    MAYOR_IGUAL = 261,
    MENOR_IGUAL = 262,
    AND = 263,
    OR = 264,
    Q = 265,
    MAS = 266,
    MENOS = 267,
    POR = 268,
    ENTRE = 269,
    POWER = 270,
    SUMAE = 271,
    RESTAE = 272,
    MASMAS = 273,
    MENOSMENOS = 274,
    MASIGUAL = 275,
    MENOSIGUAL = 276,
    DOUBLE_DOTS = 277,
    SEMICOLON = 278,
    COMA = 279,
    EQUAL = 280,
    IGUAL = 281,
    CORCHS_INIT = 282,
    CORCHS_FIN = 283,
    PARENTS_INIT = 284,
    PARENTS_FIN = 285,
    KEYS_INIT = 286,
    KEYS_FIN = 287,
    NUMBER = 288,
    TEXT = 289,
    QUOTES = 290,
    SEMIQUOTES = 291,
    CONST = 292,
    LET = 293,
    NUMBER_TYPE = 294,
    STRING_TYPE = 295,
    VOID_TYPE = 296,
    BOOL_TYPE = 297,
    OF = 298,
    CONTINUE = 299,
    BREAK = 300,
    NEW = 301,
    STATIC = 302,
    PUBLIC = 303,
    PRIVATE = 304,
    IF = 305,
    ELSE = 306,
    DO = 307,
    WHILE = 308,
    FOR = 309,
    SWITCH = 310,
    CASE = 311,
    DEFAULT = 312,
    FUNCTION = 313,
    CLASS = 314,
    RETURN = 315,
    CLASS_TYPE = 316,
    FUNCTION_TYPE = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAINLEX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 219 "mainlex.tab.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   76

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  84

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,    71,    67,    63,     2,    64,     2,    68,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    66,
      75,    65,    74,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    73,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    73,    73,    74,    75,    76,    79,    80,    81,    83,
      83,    84,    84,    85,    85,    87,    88,    89,    90,    91,
      92,    93,    95,    97,    98,    99,   101,   102,   103,   104,
     107,   108,   109,   111,   111,   113,   113,   114,   115,   116,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     129
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAYOR", "MENOR", "ESIGUAL",
  "MAYOR_IGUAL", "MENOR_IGUAL", "AND", "OR", "Q", "MAS", "MENOS", "POR",
  "ENTRE", "POWER", "SUMAE", "RESTAE", "MASMAS", "MENOSMENOS", "MASIGUAL",
  "MENOSIGUAL", "DOUBLE_DOTS", "SEMICOLON", "COMA", "EQUAL", "IGUAL",
  "CORCHS_INIT", "CORCHS_FIN", "PARENTS_INIT", "PARENTS_FIN", "KEYS_INIT",
  "KEYS_FIN", "NUMBER", "TEXT", "QUOTES", "SEMIQUOTES", "CONST", "LET",
  "NUMBER_TYPE", "STRING_TYPE", "VOID_TYPE", "BOOL_TYPE", "OF", "CONTINUE",
  "BREAK", "NEW", "STATIC", "PUBLIC", "PRIVATE", "IF", "ELSE", "DO",
  "WHILE", "FOR", "SWITCH", "CASE", "DEFAULT", "FUNCTION", "CLASS",
  "RETURN", "CLASS_TYPE", "FUNCTION_TYPE", "'+'", "'-'", "'='", "';'",
  "'*'", "'/'", "'^'", "'('", "')'", "'{'", "'}'", "'>'", "'<'", "$accept",
  "main_line", "main_line_type", "asign_all", "asign", "@1",
  "asignSuma_algo", "@2", "asignResta_algo", "@3", "asign_end", "sumaE",
  "restaE", "E", "T", "F", "P", "valor_operable", "valor_asignable",
  "ifelse", "$@4", "if", "$@5", "if_header", "if_body", "condition",
  "comparision", "else", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,    43,    45,    61,    59,    42,    47,    94,
      40,    41,   123,   125,    62,    60
};
# endif

#define YYPACT_NINF -59

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-59)))

#define YYTABLE_NINF -14

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -59,     3,   -59,   -38,   -54,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -44,   -40,   -26,   -22,   -11,   -28,   -22,
     -59,   -58,   -29,   -59,   -59,   -22,   -46,    -1,   -27,   -59,
     -59,    -8,   -59,   -28,   -59,   -59,   -59,   -59,     5,   -19,
      -6,   -22,   -59,    10,   -22,   -59,   -32,   -22,   -22,   -16,
     -24,   -20,   -22,   -22,   -22,   -22,   -22,   -59,   -59,   -30,
     -59,   -59,    -7,   -59,    -2,   -59,    -1,    -1,   -22,   -22,
       5,   -22,     5,   -27,   -27,   -59,   -59,   -59,   -59,   -59,
     -59,     5,     5,     5
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     9,     0,     2,     4,     6,     7,     8,
       5,    33,    35,     0,     0,     0,    43,     0,     0,     0,
      10,     0,     0,    30,    31,     0,    49,    22,    25,    26,
      28,     0,    42,     0,    34,     3,    39,    36,    32,     0,
       0,     0,    12,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    50,     0,
      15,    17,     0,    19,     0,    29,    20,    21,     0,     0,
      44,     0,    45,    23,    24,    27,    40,    41,    38,    16,
      18,    46,    47,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,    30,    -3,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -17,    23,    20,     1,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,    25,   -59,    19,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     5,     6,     7,    13,     8,    14,     9,    15,
      20,    42,    45,    26,    27,    28,    29,    30,    39,    10,
      17,    11,    18,    12,    37,    31,    32,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      55,    56,    38,     2,     3,    40,     3,    41,    46,    23,
      24,    23,    24,    23,    24,    36,    16,    47,    48,    49,
       4,    19,     4,    21,    62,   -11,   -13,    64,    50,    51,
      36,    47,    48,    70,    72,    43,    44,     3,    22,    65,
      33,    69,    54,    78,    35,    71,    25,    60,    25,    68,
      25,    81,    82,     4,    83,    75,    47,    48,    58,    79,
      61,    47,    48,    57,    80,    59,    52,    53,    47,    48,
      66,    67,    73,    74,    76,    77,    63
};

static const yytype_uint8 yycheck[] =
{
       8,     9,    19,     0,    34,    63,    34,    65,    25,    33,
      34,    33,    34,    33,    34,    18,    70,    63,    64,    65,
      50,    65,    50,    63,    41,    63,    64,    44,    74,    75,
      33,    63,    64,    50,    51,    64,    65,    34,    64,    71,
      51,    65,    69,    73,    72,    65,    70,    66,    70,    65,
      70,    68,    69,    50,    71,    54,    63,    64,    33,    66,
      66,    63,    64,    71,    66,    35,    67,    68,    63,    64,
      47,    48,    52,    53,    55,    56,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,     0,    34,    50,    78,    79,    80,    82,    84,
      95,    97,    99,    81,    83,    85,    70,    96,    98,    65,
      86,    63,    64,    33,    34,    70,    89,    90,    91,    92,
      93,   101,   102,    51,   103,    72,    78,   100,    89,    94,
      63,    65,    87,    64,    65,    88,    89,    63,    64,    65,
      74,    75,    67,    68,    69,     8,     9,    71,   100,    77,
      66,    66,    89,    66,    89,    71,    90,    90,    65,    65,
      89,    65,    89,    91,    91,    92,   102,   102,    73,    66,
      66,    89,    89,    89
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    77,    78,    78,    79,    79,    79,    81,
      80,    83,    82,    85,    84,    86,    87,    87,    88,    88,
      89,    89,    89,    90,    90,    90,    91,    91,    92,    92,
      93,    93,    94,    96,    95,    98,    97,    99,   100,   100,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     0,
       3,     0,     4,     0,     4,     3,     3,     2,     3,     2,
       3,     3,     1,     3,     3,     1,     1,     3,     1,     3,
       1,     1,     1,     0,     3,     0,     3,     4,     3,     1,
       3,     3,     1,     0,     3,     3,     4,     4,     4,     1,
       2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
| yyreduce -- Do a reduction.  |
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
        case 9:
#line 83 "mainlex.y" /* yacc.c:1646  */
    {printf("lexema:%c\n",yychar);(yyval)=localizaSimb(lexema,TEXT);}
#line 1368 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 83 "mainlex.y" /* yacc.c:1646  */
    {printf("lexema:%s\n",lexema);generarCodigo(EQUAL,(yyvsp[-1]),(yyvsp[0]),'-');}
#line 1374 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 84 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=localizaSimb(lexema,TEXT);}
#line 1380 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 84 "mainlex.y" /* yacc.c:1646  */
    {generarCodigo(SUMAE,(yyvsp[-2]),(yyvsp[0]),'=');}
#line 1386 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 85 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=localizaSimb(lexema,TEXT);}
#line 1392 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "mainlex.y" /* yacc.c:1646  */
    {generarCodigo(RESTAE,(yyvsp[-2]),(yyvsp[0]),'=');}
#line 1398 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 87 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1404 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 88 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1410 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 89 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=-1;}
#line 1416 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 90 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1422 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 91 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=-1;}
#line 1428 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 92 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MAS,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1434 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 93 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MENOS,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1440 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 97 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(POR,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1446 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 98 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(ENTRE,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1452 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 102 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(POWER,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1458 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 104 "mainlex.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]);}
#line 1464 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 107 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=localizaSimb(lexema,NUMBER);}
#line 1470 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 108 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=localizaSimb(lexema,TEXT);}
#line 1476 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 111 "mainlex.y" /* yacc.c:1646  */
    {generar=(generar+1)%2;}
#line 1482 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "mainlex.y" /* yacc.c:1646  */
    {if(TablaSim[(yyvsp[0])].valor==0) generar=0;}
#line 1488 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 114 "mainlex.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1494 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 118 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(AND,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1500 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 119 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(OR,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1506 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 122 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MAYOR,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1512 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 123 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MENOR,i,(yyvsp[-2]),(yyvsp[0]));(yyval)=i;}
#line 1518 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 124 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(ESIGUAL,i,(yyvsp[-3]),(yyvsp[0]));(yyval)=i;}
#line 1524 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 125 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MAYOR_IGUAL,i,(yyvsp[-3]),(yyvsp[0]));(yyval)=i;}
#line 1530 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 126 "mainlex.y" /* yacc.c:1646  */
    { int i=GenVarTemp();generarCodigo(MENOR_IGUAL,i,(yyvsp[-3]),(yyvsp[0]));(yyval)=i;}
#line 1536 "mainlex.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 129 "mainlex.y" /* yacc.c:1646  */
    {generar=1;}
#line 1542 "mainlex.tab.c" /* yacc.c:1646  */
    break;


#line 1546 "mainlex.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 130 "mainlex.y" /* yacc.c:1906  */


int GenVarTemp(){
	if(generar==0) return;
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,TEXT);
}

void generarCodigo(int op, int a1,int a2, int a3){
	if(generar==0) return;
	imprimeTablaSim();

	if(op == EQUAL) TablaSim[a1].valor = TablaSim[a2].valor;

	if(op == MAS)	TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
	if(op == MENOS)	TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;

	if(op == POR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
	if(op == ENTRE) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
	if(op == POWER) TablaSim[a1].valor = pow(TablaSim[a2].valor, TablaSim[a3].valor);

	if(op == SUMAE){
		if(a2 < 0 ) { op=MASMAS; TablaSim[a1].valor++;}
		else {op == MASIGUAL; TablaSim[a1].valor+=TablaSim[a2].valor;}
	}
	if(op == RESTAE){
		if(a2 < 0 ) { op=MENOSMENOS; TablaSim[a1].valor--;}
		else {op == MENOSIGUAL; TablaSim[a1].valor-=TablaSim[a2].valor;}
	}

	if(op == MAYOR){ 
		if(TablaSim[a2].valor > TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MENOR) { 
		if(TablaSim[a2].valor < TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == ESIGUAL) {
		if(TablaSim[a2].valor == TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MAYOR_IGUAL) {
		if(TablaSim[a2].valor >= TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MENOR_IGUAL) {
		if(TablaSim[a2].valor >= TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}

	if(op == AND){
		if(TablaSim[a2].valor*TablaSim[a3].valor == 1) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == OR)
		if(TablaSim[a2].valor+TablaSim[a3].valor == 0) TablaSim[a1].valor = 0;
		else TablaSim[a1].valor = 1;

  cx++;
  TCodigo[cx].op=op;
  TCodigo[cx].a1=a1;
  TCodigo[cx].a2=a2;
  TCodigo[cx].a3=a3;

	imprimeTablaCod();
	imprimeTablaSim();
	printf("fin %d \n",op);
}

int localizaSimb(char *nom,int tok){
	if(generar==0) return;
  int i;
  for (i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token=tok;
  if (tok==TEXT) TablaSim[nSim].valor=0.0;
  if (tok==NUMBER) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim-1;
}

void imprimeTablaSim(){
	printf("tabla de simbolos----------------\n");
  int i;
  for ( i=0;i<nSim;i++){
    printf("%d nombre=%s tok=%d valor=%lf\n", i , TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
	printf("tabla de codigos------------------\n");
  int i;
  for ( i=0;i<=cx;i++){
    printf("%d a1=%d a2=%d a3=%d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void yyerror(char *msg){
  printf("ERROR:%s \n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera may y minusc
  //strcasecmp ignora may de min
	if(strcmp(lexema, "If") == 0) return IF;
	if(strcmp(lexema, "Else") == 0) return ELSE;

	if(strcmp(lexema, "and") == 0) return AND;
  if(strcmp(lexema, "or") == 0) return OR;
	
	if(strcmp(lexema, "continue") == 0) return CONTINUE;
  if(strcmp(lexema, "break") == 0) return BREAK;
  if(strcmp(lexema, "Number") == 0) return NUMBER_TYPE;
	//printf("retlexb:%s\n	",lexema);
  return TEXT;
}

/*
int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(c=='\t') continue;
		
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalpha(c));
			ungetc(c, stdin);
			lexema[i]=0;
			
			return EsPalabraReservada(lexema);
		}
		if(isdigit(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c, stdin);
			lexema[i]=0;
			return NUMBER;
		}
		return c;
	}
}
*/

int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
//	printf("tabla de simbolos\n");
	imprimeTablaSim();
//	printf("tabla de codigos\n");
	imprimeTablaCod();
	
	return 0;
}





