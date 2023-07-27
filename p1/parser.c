#include <stddef.h>                                                             /* for NULL */
#include <stdlib.h>                                                             /* for EXIT_SUCCESS and EXIT_FAILURE */
#include <stdbool.h>
#include "parser.h"

// yylex is used to get tokens from lex
extern int yylex();
int curr_tok;
void mainClass();
void statementRecur();
void varDecl();
void eqlExpr();
void varDeclTail();
void primeType();
void type();
void typeRecur();
void statement();
void Expr();
bool operators();
void Index();
void leftValue();
void leftValueRecur();

// advance current token
static void consume() {
    curr_tok = yylex();
    //printf("Current token: %d\n", curr_tok);
}

// consume next token if matches, else report a syntax error
void match(int expect_tok) {
    if(curr_tok == expect_tok) {
        consume();
    }
    else {
      syntax_error();
    }
}

// write code to perform recursive descent based on the grammar after
// rewriting it
void program() {
  consume();
  mainClass();
}
void mainClass() {
  match(KW_CLASS);
  match(TOK_ID);
  match(TOK_lCBRAC);
  match(KW_PUBLIC);
  match(KW_STATIC);
  match(KW_VOID);
  match(KW_MAIN);
  match(TOK_lBRAC);
  match(KW_STR);
  match(TOK_lSBRAC);
  match(TOK_rSBRAC);
  match(TOK_ID);
  match(TOK_rBRAC);
  match(TOK_lCBRAC);
  statementRecur();
  match(TOK_rCBRAC);
  match(TOK_rCBRAC);
}
void statementRecur() {
  if (curr_tok != TOK_rCBRAC) {
    statement();
    statementRecur();
  }
}
void varDecl() {
  type();
  match(TOK_ID);
  eqlExpr();
  varDeclTail();
  match(TOK_SEMICOLON);
}
void eqlExpr() {
  if (curr_tok == TOK_EQL) {
    match(TOK_EQL);
    Expr();
  }
}
void varDeclTail() {
  if (curr_tok == TOK_COMMA) {
    match(TOK_COMMA);
    match(TOK_ID);
    eqlExpr();
    varDeclTail();
  }
}
void primeType() {
  switch(curr_tok) {
    case KW_INT:
      match(KW_INT);
      break;
    case KW_STR:
      match(KW_STR);
      break;
    case KW_BOOL:
      match(KW_BOOL);
      break;
    default:
      syntax_error();
  }
}
void type() {
  primeType();
  typeRecur();
}
void typeRecur() {
  if (curr_tok == TOK_lSBRAC) {
    match(TOK_lSBRAC);
    match(TOK_rSBRAC);
    typeRecur();
  }
}
void statement() {
  switch (curr_tok) {
    case KW_INT:
    case KW_STR:
    case KW_BOOL:
      varDecl();
      break;
    case TOK_lCBRAC:
      match(TOK_lCBRAC);
      statementRecur();
      match(TOK_rCBRAC);
      break;
    case KW_IF:
      match(KW_IF);
      match(TOK_lBRAC);
      Expr();
      match(TOK_rBRAC);
      statement();
      match(KW_ELSE);
      statement();
      break;
    case KW_WHILE:
      match(KW_WHILE);
      match(TOK_lBRAC);
      Expr();
      match(TOK_rBRAC);
      statement();
      break;
    case KW_SYSTEM:
      match(KW_SYSTEM);
      match(TOK_DOT);
      match(KW_OUT);
      match(TOK_DOT);
      if (curr_tok == KW_PRINT) {
        match(KW_PRINT);
      } else if (curr_tok == KW_PRINTLN) {
        match(KW_PRINTLN);
      }
      match(TOK_lBRAC);
      Expr();
      match(TOK_rBRAC);
      match(TOK_SEMICOLON);
      break;
    case TOK_ID:
      leftValue();
      match(TOK_EQL);
      Expr();
      match(TOK_SEMICOLON);
      break;
    case KW_RETURN:
      match(KW_RETURN);
      Expr();
      match(TOK_SEMICOLON);
      break;
    default:
      syntax_error();
  }
}
void Expr() {
  switch (curr_tok) {
    case TOK_lBRAC:
      match(TOK_lBRAC);
      Expr();
      match(TOK_rBRAC);
      break;
    case TOK_ID:
      leftValue();
      if (curr_tok == TOK_DOT) {
        match(TOK_DOT);
        match(KW_LENGTH);
      }
      break;
    case TOK_INT:
      match(TOK_INT);
      break;
    case TOK_STR:
      match(TOK_STR);
      break;
    case TOK_TRUE:
      match(TOK_TRUE);
      break;
    case TOK_FALSE:
      match(TOK_FALSE);
      break;
    case KW_NEW:
      match(KW_NEW);
      primeType();
      Index();
      break;
    default:
      syntax_error();
  }
  if (operators()) {
    Expr();
  }
}
bool operators() {
  switch (curr_tok) {
    case TOK_AND:
      match(TOK_AND);
      break;
    case TOK_NEQ:
      match(TOK_NEQ);
      break;
    case TOK_OR:
      match(TOK_OR);
      break;
    case TOK_LES:
      match(TOK_LES);
      break;
    case TOK_GRT:
      match(TOK_GRT);
      break;
    case TOK_LEQ:
      match(TOK_LEQ);
      break;
    case TOK_GEQ:
      match(TOK_GEQ);
      break;
    case TOK_EQLEQL:
      match(TOK_EQLEQL);
      break;
    case TOK_ADD:
      match(TOK_ADD);
      break;
    case TOK_SUB:
      match(TOK_SUB);
      break;
    case TOK_MUL:
      match(TOK_MUL);
      break;
    case TOK_DIV:
      match(TOK_DIV);
      break;
    default:
      return false;
  }
  return true;
}
void Index() {
  match(TOK_lSBRAC);
  Expr();
  match(TOK_rSBRAC);
  if (curr_tok == TOK_lSBRAC) {
    Index();
  }
}
void leftValue() {
  match(TOK_ID);
  leftValueRecur();
}
void leftValueRecur() {
  if (curr_tok == TOK_lSBRAC) {
    match(TOK_lSBRAC);
    Expr();
    match(TOK_rSBRAC);
    leftValueRecur();
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
      char *path = argv[1];
      FILE *file = fopen(path, "r");
      if(file == NULL) {
          perror("Cannot open file");
          return EXIT_FAILURE;
      }

      set_instream(file);
  }

  // call the function to match the start non terminal here
  program();
  if (curr_tok != TOK_EOF) syntax_error();
  return EXIT_SUCCESS;
}
