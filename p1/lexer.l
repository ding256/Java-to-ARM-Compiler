%option noyywrap
%option yylineno

%{
#include <stdio.h>                                                              /* for fprintf() */
#include <stdlib.h>                                                             /* for EXIT_FAILURE */

#include "parser.h"

void syntax_error() {
    fprintf(stderr, "Syntax errors in %d\n", yylineno);
    exit(EXIT_FAILURE);
}
%}

%%


    /* write regex to match all terminals */
    /* a few example are given below */



[ \t\r\n]*                   { }                                                /* whitespace */

"//".*                       { }                                                /* inline comments */
"/*"([^*]|"*"+[^*/])*"*"+"/" { }                                                /* block comments */

"&&"                   { return TOK_AND; }                                      /* operators */
"!="                   { return TOK_NEQ; }
"||"                   { return TOK_OR; }
"<"                    { return TOK_LES; }
">"                    { return TOK_GRT; }
"<="                   { return TOK_LEQ; }
">="                   { return TOK_GEQ; }
"=="                   { return TOK_EQLEQL; }
"+"                    { return TOK_ADD; }
"-"                    { return TOK_SUB; }
"*"                    { return TOK_MUL; }
"/"                    { return TOK_DIV; }
"++"                   { syntax_error(); }
"--"                   { syntax_error(); }

"public"               { return KW_PUBLIC; }                                    /* keywords */
"private"              { return KW_PRIVATE; }
"static"               { return KW_STATIC; }
"class"                { return KW_CLASS; }
"main"                 { return KW_MAIN; }
"void"                 { return KW_VOID; }
"int"                  { return KW_INT; }
"String"               { return KW_STR; }
"boolean"              { return KW_BOOL; }
"if"                   { return KW_IF; }
"else"                 { return KW_ELSE; }
"while"                { return KW_WHILE; }
"new"                  { return KW_NEW; }
"return"               { return KW_RETURN; }
"System"               { return KW_SYSTEM; }
"out"                  { return KW_OUT; }
"print"                { return KW_PRINT; }
"println"              { return KW_PRINTLN; }
"length"               { return KW_LENGTH; }


[0-9]+                 { return TOK_INT; }                                      /* integer literal */
"true"                 { return TOK_TRUE; }                                     /* boolean literals */
"false"                { return TOK_FALSE; }
\"([^\\\"]|\\.)*\"     { return TOK_STR; }                                      /* string literal */
[_a-zA-Z][_a-zA-Z0-9]* { return TOK_ID; }                                       /* identifiers */

"."                    { return TOK_DOT; }                                      /* other terminals */
";"                    { return TOK_SEMICOLON; }
","                    { return TOK_COMMA; }
"="                    { return TOK_EQL; }
"("                    { return TOK_lBRAC; }
")"                    { return TOK_rBRAC; }
"{"                    { return TOK_lCBRAC; }
"}"                    { return TOK_rCBRAC; }
"["                    { return TOK_lSBRAC; }
"]"                    { return TOK_rSBRAC; }

.                      { syntax_error(); }                                      /* all other characters */

<<EOF>>                { return TOK_EOF; }

%%

// yyin is the input stream for lex, not providing a file defaults to
// standard input
void set_instream(FILE *file) {
  yyin = file;
}
