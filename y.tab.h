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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    INT = 258,
    FLOAT = 259,
    ID = 260,
    TYPE = 261,
    FOR = 262,
    IF = 263,
    ELSE = 264,
    LT = 265,
    LE = 266,
    EQ = 267,
    NE = 268,
    GT = 269,
    GE = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    PRINT = 274,
    SCAN = 275,
    EXPR = 276,
    ATTR = 277,
    VAR = 278,
    STMT = 279,
    STMTS = 280,
    BLOCO = 281,
    PROGRAM = 282,
    ADD = 283,
    SUB = 284,
    MUL = 285,
    DIV = 286,
    MOD = 287,
    NUMBER = 288,
    UMINUS = 289
  };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define ID 260
#define TYPE 261
#define FOR 262
#define IF 263
#define ELSE 264
#define LT 265
#define LE 266
#define EQ 267
#define NE 268
#define GT 269
#define GE 270
#define AND 271
#define OR 272
#define NOT 273
#define PRINT 274
#define SCAN 275
#define EXPR 276
#define ATTR 277
#define VAR 278
#define STMT 279
#define STMTS 280
#define BLOCO 281
#define PROGRAM 282
#define ADD 283
#define SUB 284
#define MUL 285
#define DIV 286
#define MOD 287
#define NUMBER 288
#define UMINUS 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
