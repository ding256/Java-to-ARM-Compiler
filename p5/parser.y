%{
#include <stdio.h>
#include <string.h>
#include "codegen.h"
#include "node.h"
void yyerror(char *);

extern int yylex();

// Global variables defined by lex.yy.c.
extern int yylineno;
extern char* yytext;
extern FILE *yyin;

struct ASTNode* root;
%}

// Declares all variants of semantic values. Yacc/Bison copies all variants
// to the generated header file (y.tab.h) enclosed in a C-language union
// declaration, named `YYSTYPE`. Check out the header file to see it.
%union {
    struct ASTNode* node;
    int integer;
    char * string;
}

// Left hand non-terminals. They are all associated to the `node` variant
// declared in the %union section, which is of type `ASTNode *`.
%type <node> Program MainClass MainMethod VarDecl StaticVarDecl StaticMethodDecl
%type <node> FormalList PrimeType Type Statement MethodCall ExpList Index
%type <node> LeftValue StatementList EqlExp StaticVarDeclTail ExpListTail Factor
%type <node> FormalListTail IfFormalList Exp_or Exp_and Exp_eql Exp_ineql
%type <node> Exp_plusminus Exp_muldiv Exp_factor

// Declares tokens. In the generated y.tab.h file, each token gets declared as
// a enum constant and assigned with a unique number. These enum constants are
// used in the lex file, returned by `yylex()` to denote the symbolic tokens.
%token TOK_AND TOK_NEQ TOK_OR TOK_LEQ TOK_GEQ TOK_EQLEQL

// These keyword-like tokens doesn't need to have a semantic value.
%token MAIN KW_PUBLIC KW_PRIVATE KW_STATIC KW_CLASS KW_VOID KW_INT KW_BOOL
%token KW_STR KW_IF KW_ELSE KW_WHILE KW_NEW KW_RETURN KW_SYSTEM KW_OUT
%token KW_PRINT KW_PRINTLN KW_TRUE KW_FALSE

// These are wrapper classes or corresponding embedded functions
%token CLASS_INTEGER INTEGER_PARSEINT STRING_LENGTH

// These tokens have additional information aside from what kind of token it
// is, so they carry semantic information.
%token <integer> INT_LIT
%token <string> STR_LIT ID

%right '='
%left TOK_OR
%left TOK_AND
%left TOK_NEQ TOK_EQLEQL
%left '<' '>' TOK_LEQ TOK_GEQ
%left '+' '-'
%left '*' '/'
%right KW_NEW
%right Unary
%left Paren

%start Program

%%

Program:
    MainClass {
        $$ = new_node(NODETYPE_PROGRAM);
        root = $$;
        add_child($$, $1);
    };

MainClass:
    KW_CLASS ID '{' StaticVarDecl StaticMethodDecl MainMethod '}' {
        $$ = new_node(NODETYPE_MAINCLASS);
        set_string_value($$, $2);
        set_lineno($$, yylineno);
        add_child($$, $4);
        add_child($$, $5);
        add_child($$, $6);
    };

MainMethod:
    KW_PUBLIC KW_STATIC KW_VOID MAIN '(' KW_STR '[' ']' ID ')' '{' StatementList '}' {
        $$ = new_node(NODETYPE_MAINMETHOD);
        set_lineno($$, yylineno);
        set_string_value($$, $9);
        add_child($$, $12);
    };

StaticVarDecl:
    StaticVarDecl KW_PRIVATE KW_STATIC Type ID EqlExp StaticVarDeclTail ';' {
        $$ = new_node(NODETYPE_STATICVARDECL);
        set_lineno($$, yylineno);
        set_string_value($$, $5);
        add_child($$, $1);
        add_child($$, $4);
        add_child($$, $6);
        add_child($$, $7);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

EqlExp:
    '=' Exp_or {
        $$ = new_node(NODETYPE_EQLEXP);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

StaticVarDeclTail:
    StaticVarDeclTail ',' ID EqlExp {
        $$ = new_node(NODETYPE_STATICVARDECLTAIL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        set_string_value($$, $3);
        add_child($$, $4);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

StaticMethodDecl:
    StaticMethodDecl KW_PUBLIC KW_STATIC Type ID '(' IfFormalList ')' '{' StatementList '}' {
        $$ = new_node(NODETYPE_STATICMETHODDECL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $4);
        set_string_value($$, $5);
        add_child($$, $7);
        add_child($$, $10);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

IfFormalList:
    FormalList {
        $$ = new_node(NODETYPE_IFFORMALLIST);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

StatementList:
    StatementList Statement {
        $$ = new_node(NODETYPE_STATEMENTLIST);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

VarDecl:
    Type ID EqlExp StaticVarDeclTail ';' {
        $$ = new_node(NODETYPE_VARDECL);
        set_lineno($$, yylineno);
        set_string_value($$, $2);
        add_child($$, $1);
        add_child($$, $3);
        add_child($$, $4);
    };

FormalList:
    Type ID FormalListTail {
        $$ = new_node(NODETYPE_FORMALLIST);
        set_lineno($$, yylineno);
        add_child($$, $1);
        set_string_value($$, $2);
        add_child($$, $3);
    };

FormalListTail:
    FormalListTail ',' Type ID {
        $$ = new_node(NODETYPE_FORMALLISTTAIL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
        set_string_value($$, $4);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

PrimeType:
    KW_INT {
        $$ = new_node(NODETYPE_PRIMETYPE);
        set_lineno($$, yylineno);
        $$ -> data.type = DATATYPE_INT;
    }
    | KW_BOOL {
        $$ = new_node(NODETYPE_PRIMETYPE);
        set_lineno($$, yylineno);
        $$ -> data.type = DATATYPE_BOOLEAN;
    }
    | KW_STR {
        $$ = new_node(NODETYPE_PRIMETYPE);
        set_lineno($$, yylineno);
        $$ -> data.type = DATATYPE_STR;
    };

Type:
    PrimeType {
        $$ = new_node(NODETYPE_PRIMETYPE);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | Type '[' ']' {
        $$ = new_node(NODETYPE_TYPE);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Statement:
    VarDecl {
        $$ = new_node(NODETYPE_VARDECL);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | '{' StatementList '}' {
        $$ = new_node(NODETYPE_STATEMENTLIST);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | KW_IF '(' Exp_or ')' Statement KW_ELSE Statement {
        $$ = new_node(NODETYPE_IF);
        set_lineno($$, yylineno);
        add_child($$, $3);
        add_child($$, $5);
        add_child($$, $7);
    }
    | KW_WHILE '(' Exp_or ')' Statement {
        $$ = new_node(NODETYPE_WHILE);
        set_lineno($$, yylineno);
        add_child($$, $3);
        add_child($$, $5);
    }
    | KW_SYSTEM '.' KW_OUT '.' KW_PRINTLN '(' Exp_or ')' ';' {
        $$ = new_node(NODETYPE_PRINTLN);
        set_lineno($$, yylineno);
        add_child($$, $7);
    }
    | KW_SYSTEM '.' KW_OUT '.' KW_PRINT '(' Exp_or ')' ';' {
        $$ = new_node(NODETYPE_PRINT);
        set_lineno($$, yylineno);
        add_child($$, $7);
    }
    | LeftValue '=' Exp_or ';' {
        $$ = new_node(NODETYPE_LEFTVALUE);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | KW_RETURN Exp_or ';' {
        $$ = new_node(NODETYPE_RETURN);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | MethodCall ';' {
        $$ = new_node(NODETYPE_METHODCALL);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

MethodCall:
    ID '(' ExpList ')' {
        $$ = new_node(NODETYPE_EXPLIST);
        set_lineno($$, yylineno);
        set_string_value($$, $1);
        add_child($$, $3);
    }
    | ID '(' ')' {
        $$ = new_node(NODETYPE_ID);
        set_lineno($$, yylineno);
        set_string_value($$, $1);
    }
    | CLASS_INTEGER '.' INTEGER_PARSEINT '(' Exp_or ')' {
        $$ = new_node(NODETYPE_PARSEINT);
        set_lineno($$, yylineno);
        add_child($$, $5);
    };

Exp_or:
    Exp_or TOK_OR Exp_and {
        $$ = new_node(NODETYPE_EXPOR);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_and {
        $$ = new_node(NODETYPE_EXPAND);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_and:
    Exp_and TOK_AND Exp_eql {
        $$ = new_node(NODETYPE_EXPAND);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_eql {
        $$ = new_node(NODETYPE_EXPEQL);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_eql:
    Exp_eql TOK_EQLEQL Exp_ineql {
        $$ = new_node(NODETYPE_EXPEQL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_eql TOK_NEQ Exp_ineql {
        $$ = new_node(NODETYPE_EXPNEQ);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_ineql {
        $$ = new_node(NODETYPE_EXPINEQL);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_ineql:
    Exp_ineql '<' Exp_plusminus {
        $$ = new_node(NODETYPE_EXPLES);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_ineql '>' Exp_plusminus {
        $$ = new_node(NODETYPE_EXPGRT);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_ineql TOK_LEQ Exp_plusminus {
        $$ = new_node(NODETYPE_EXPLEQ);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_ineql TOK_GEQ Exp_plusminus {
        $$ = new_node(NODETYPE_EXPGEQ);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_plusminus {
        $$ = new_node(NODETYPE_EXPPLUSMINUS);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_plusminus:
    Exp_plusminus '+' Exp_muldiv {
        $$ = new_node(NODETYPE_EXPPLUS);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_plusminus '-' Exp_muldiv {
        $$ = new_node(NODETYPE_EXPMINUS);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_muldiv {
        $$ = new_node(NODETYPE_EXPMULDIV);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_muldiv:
    Exp_muldiv '*' Exp_factor {
        $$ = new_node(NODETYPE_EXPMUL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | Exp_factor {
        $$ = new_node(NODETYPE_EXPFACTOR);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Exp_factor:
    Factor {
        $$ = new_node(NODETYPE_FACTOR);
        set_lineno($$, yylineno);
        add_child($$, $1);
    };

Factor:
    '!' Factor {
        $$ = new_node(NODETYPE_NEG);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | '+' Factor {
        $$ = new_node(NODETYPE_PLUS);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | '-' Factor {
        $$ = new_node(NODETYPE_MINUS);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | '(' Exp_or ')' %prec Paren {
        $$ = new_node(NODETYPE_FACTORRECUR);
        set_lineno($$, yylineno);
        add_child($$, $2);
    }
    | LeftValue {
        $$ = new_node(NODETYPE_LEFTVALUE);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | LeftValue '.' STRING_LENGTH {
        $$ = new_node(NODETYPE_LEFTVALUELENGTH);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | INT_LIT {
        $$ = new_node(NODETYPE_INT);
        set_lineno($$, yylineno);
        set_int_value($$, $1);
    }
    | STR_LIT {
        $$ = new_node(NODETYPE_STR);
        set_lineno($$, yylineno);
        set_string_value($$, $1);
    }
    | KW_TRUE {
        $$ = new_node(NODETYPE_TRUE);
        set_lineno($$, yylineno);
        set_boolean_value($$, true);
    }
    | KW_FALSE {
        $$ = new_node(NODETYPE_FALSE);
        set_lineno($$, yylineno);
        set_boolean_value($$, false);
    }
    | MethodCall {
        $$ = new_node(NODETYPE_METHODCALL);
        set_lineno($$, yylineno);
        add_child($$, $1);
    }
    | KW_NEW PrimeType Index {
        $$ = new_node(NODETYPE_NEW);
        set_lineno($$, yylineno);
        add_child($$, $2);
        add_child($$, $3);
    };

ExpList:
    Exp_or ExpListTail {
        $$ = new_node(NODETYPE_EXPLIST);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $2);
    };

ExpListTail:
    ExpListTail ',' Exp_or {
        $$ = new_node(NODETYPE_EXPLISTTAIL);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | { $$ = new_node(NODETYPE_EPSILON); };

Index:
    Index '[' Exp_or ']'{
        $$ = new_node(NODETYPE_INDEXRECUR);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    }
    | '[' Exp_or ']' {
        $$ = new_node(NODETYPE_INDEX);
        set_lineno($$, yylineno);
        add_child($$, $2);
    };

LeftValue:
    ID {
        $$ = new_node(NODETYPE_LEFTVALUE);
        set_lineno($$, yylineno);
        set_string_value($$, $1);
    }
    | LeftValue '[' Exp_or ']' {
        $$ = new_node(NODETYPE_LEFTVALUERECUR);
        set_lineno($$, yylineno);
        add_child($$, $1);
        add_child($$, $3);
    };

%%

void yyerror(char* s) {
    fprintf(stderr, "Syntax errors in line %d\n", yylineno);
}

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");
    if (yyin) {
        // Checks for syntax errors and construct AST
        if (yyparse() != 0) return 1;

        // Create the name for the .s file
        int name_len = strlen(argv[1]) - 2;
        char file_name[name_len];
        strncpy(file_name, argv[1], name_len);
        file_name[name_len - 2] = 's';
        file_name[name_len - 1] = '\0';

        // Traverse the AST to check for semantic errors if no syntax errors, then execute semantic actions
        checkProgram(root, file_name);
        return 0;
    }
    printf("Failed to open target java file!\n");
    return -1;
}
