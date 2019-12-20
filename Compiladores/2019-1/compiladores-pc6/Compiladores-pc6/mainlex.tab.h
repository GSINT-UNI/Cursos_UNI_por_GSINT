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
