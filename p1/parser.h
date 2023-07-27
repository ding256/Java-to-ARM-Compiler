#ifndef parser_h
#define parser_h

#include <stdio.h>

// enumerate all tokens (terminals) here
enum Token {
    TOK_AND,                                                                    // operators
    TOK_NEQ,
    TOK_OR,
    TOK_LES,
    TOK_GRT,//4
    TOK_LEQ,
    TOK_GEQ,
    TOK_EQLEQL,
    TOK_ADD,
    TOK_SUB,//9
    TOK_MUL,
    TOK_DIV,
    TOK_INC,
    TOK_DEC,

    KW_PUBLIC,                                                                  // keywords
    KW_PRIVATE,//15
    KW_STATIC,
    KW_CLASS,
    KW_MAIN,
    KW_VOID,
    KW_INT,//20
    KW_STR,
    KW_BOOL,
    KW_IF,
    KW_ELSE,
    KW_WHILE,//25
    KW_NEW,
    KW_RETURN,
    KW_SYSTEM,
    KW_OUT,
    KW_PRINT,//30
    KW_PRINTLN,
    KW_LENGTH,

    TOK_ID,                                                                     // identifier

    TOK_INT,                                                                    // literals
    TOK_STR,//35
    TOK_TRUE,
    TOK_FALSE,

    TOK_DOT,                                                                    // other terminals
    TOK_SEMICOLON,
    TOK_COMMA,//40
    TOK_EQL,
    TOK_lBRAC,
    TOK_rBRAC,
    TOK_lCBRAC,
    TOK_rCBRAC,//45
    TOK_lSBRAC,
    TOK_rSBRAC,

    TOK_EOF
};

void syntax_error();
void set_instream(FILE*);

#endif
