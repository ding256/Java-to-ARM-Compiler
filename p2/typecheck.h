#ifndef TYPE_CHECK_H
#define TYPE_CHECK_H

#include "node.h"

typedef struct Expression {
    enum DataType type;
    int dimension;
} expression;

struct SymbolTableEntry {
    char *id;
    enum DataType type;
    int dimension;
};

struct TableTree {
    struct TableTree *parent;
    struct SymbolTableEntry *table[50];
    int num_entries;
    char *current_scope;
};

struct MethodTable {
    char *id;
    expression type_dim;
    struct SymbolTableEntry *parameters[50];
    int num_param;
};

void checkProgram(struct ASTNode*);
void checkMainClass(struct ASTNode*);
expression checkType(struct ASTNode*, int);
expression checkPrimeType(struct ASTNode*, int);

void checkStaticVarDecl(struct ASTNode*, struct TableTree*);
expression checkEqlExp(struct ASTNode *, struct TableTree*);
void checkStaticVarDeclTail(struct ASTNode*, expression, struct TableTree*);

void checkStaticMethodDecl(struct ASTNode*, struct TableTree*);
void checkIfFormalList(struct ASTNode*, char*);
void checkFormalList(struct ASTNode*, char*);
void checkFormalListTail(struct ASTNode*, char*);
void forwardStaticMethodDecl(struct ASTNode *staticMethodDecl, struct TableTree *tree_node);
void forwardIfFormalList(struct ASTNode *ifFormalList, char *method_id);
void forwardFormalList(struct ASTNode *formalList, char *method_id);
void forwardFormalListTail(struct ASTNode *formalListTail, char *method_id);

void checkMainMethod(struct ASTNode*, struct TableTree*);
void checkStatementList(struct ASTNode*, struct TableTree*);
void checkStatement(struct ASTNode*, struct TableTree*);
void checkVarDecl(struct ASTNode*, struct TableTree*);

expression checkMethodCall(struct ASTNode*, struct TableTree*);

expression checkExpOr(struct ASTNode*, struct TableTree*);
expression checkExpAnd(struct ASTNode*, struct TableTree*);
expression checkExpEql(struct ASTNode*, struct TableTree*);
expression checkExpIneql(struct ASTNode*, struct TableTree*);
expression checkExpPlusMinus(struct ASTNode*, struct TableTree*);
expression checkExpMulDiv(struct ASTNode*, struct TableTree*);
expression checkExpFactor(struct ASTNode*, struct TableTree*);
expression checkFactor(struct ASTNode*, struct TableTree*);

expression checkIndex(struct ASTNode*, struct TableTree*, int);
void checkExpList(struct ASTNode*, struct MethodTable*, struct TableTree*);
int checkExpListTail(struct ASTNode*, struct MethodTable*, int, struct TableTree*);
expression checkLeftValue(struct ASTNode*, struct TableTree*, int);

/* Helper functions */

struct TableTree *create_tree_node(struct TableTree *parent);
void add(char* id, enum DataType type, struct TableTree *tree_node, int dim);
void add_to_method_table(char *id, expression type_dim);
void add_parameter(struct MethodTable *method, char *param_name, expression param_type_dim);
void add_to_forward_table(char *id, expression type_dim);

struct SymbolTableEntry *find_symbol(char* id, struct TableTree *tree_node);
struct MethodTable *find_method(char *id);
struct SymbolTableEntry *find_parameter(char *id, struct MethodTable *method);
struct MethodTable *find_forward_method(char *id);

void change_type(char *id, enum DataType newType, struct TableTree *tree_node);
void change_method_type(char *id, enum DataType newType);
void change_parameter_type(char *id, enum DataType newType, struct MethodTable *method);
void change_forward_method_type(char *id, enum DataType newType);

int check_parameter(struct ASTNode *node, struct MethodTable *method, int index, expression type_dim);
bool if_epsilon(struct ASTNode *node);
expression type_check(struct ASTNode *node, expression type1, expression type2, enum DataType requirement, int lever, enum DataType return_value);
bool type_check_new(enum DataType type1, enum DataType type2);
bool if_undefined_param(struct MethodTable *method);

extern int num_errors;
extern int num_entries;

#endif
