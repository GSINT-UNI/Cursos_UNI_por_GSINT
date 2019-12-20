/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_BISONMON_TAB_H_INCLUDED
# define YY_YY_BISONMON_TAB_H_INCLUDED
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
    ID = 258,
    NUM = 259,
    RAIZ = 260,
    SI = 261,
    SINO = 262,
    PARA = 263,
    MIENTRAS = 264,
    ENTER = 265,
    COM = 266,
    STRING = 267,
    TRUEASSIGN = 268,
    ASSIGN = 269,
    SUM = 270,
    RES = 271,
    MUL = 272,
    DIV = 273,
    EVAL = 274,
    EQ = 275,
    NEQ = 276,
    LES = 277,
    MOR = 278,
    LEQ = 279,
    MEQ = 280,
    ITERLIMIT = 281,
    AND = 282,
    OR = 283,
    POW = 284,
    SQRT = 285,
    PROG = 286,
    VARS = 287,
    ELSE = 288,
    OTHERCASE = 289,
    DESDE = 290,
    HASTA = 291,
    AUMENTANDO = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 60 "bisonmon.y" /* yacc.c:1909  */

	float ftype;
	char *stype;
	int itype;

#line 98 "bisonmon.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISONMON_TAB_H_INCLUDED  */
