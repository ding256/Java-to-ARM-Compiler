/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_AND = 258,
    TOK_NEQ = 259,
    TOK_OR = 260,
    TOK_LEQ = 261,
    TOK_GEQ = 262,
    TOK_EQLEQL = 263,
    MAIN = 264,
    KW_PUBLIC = 265,
    KW_PRIVATE = 266,
    KW_STATIC = 267,
    KW_CLASS = 268,
    KW_VOID = 269,
    KW_INT = 270,
    KW_BOOL = 271,
    KW_STR = 272,
    KW_IF = 273,
    KW_ELSE = 274,
    KW_WHILE = 275,
    KW_NEW = 276,
    KW_RETURN = 277,
    KW_SYSTEM = 278,
    KW_OUT = 279,
    KW_PRINT = 280,
    KW_PRINTLN = 281,
    KW_TRUE = 282,
    KW_FALSE = 283,
    CLASS_INTEGER = 284,
    INTEGER_PARSEINT = 285,
    STRING_LENGTH = 286,
    INT_LIT = 287,
    STR_LIT = 288,
    ID = 289,
    Unary = 290,
    Paren = 291
  };
#endif
/* Tokens.  */
#define TOK_AND 258
#define TOK_NEQ 259
#define TOK_OR 260
#define TOK_LEQ 261
#define TOK_GEQ 262
#define TOK_EQLEQL 263
#define MAIN 264
#define KW_PUBLIC 265
#define KW_PRIVATE 266
#define KW_STATIC 267
#define KW_CLASS 268
#define KW_VOID 269
#define KW_INT 270
#define KW_BOOL 271
#define KW_STR 272
#define KW_IF 273
#define KW_ELSE 274
#define KW_WHILE 275
#define KW_NEW 276
#define KW_RETURN 277
#define KW_SYSTEM 278
#define KW_OUT 279
#define KW_PRINT 280
#define KW_PRINTLN 281
#define KW_TRUE 282
#define KW_FALSE 283
#define CLASS_INTEGER 284
#define INTEGER_PARSEINT 285
#define STRING_LENGTH 286
#define INT_LIT 287
#define STR_LIT 288
#define ID 289
#define Unary 290
#define Paren 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "parser.y"

    struct ASTNode* node;
    int integer;
    char * string;

#line 135 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
