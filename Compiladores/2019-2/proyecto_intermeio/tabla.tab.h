/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 109 "tabla.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TABLA_TAB_H_INCLUDED  */
