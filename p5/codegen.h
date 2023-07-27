#ifndef TYPE_CHECK_H
#define TYPE_CHECK_H

#include "node.h"

typedef struct Expression {
    enum DataType type;
    int dimension;
} expression;

typedef struct VarEntry {
    char *id;
    int offset;
    enum DataType type;
    enum DataType array_type;
} local_var;

typedef struct CompilerTemp {
    int reg;
    int offset;
} compiler_temp;

typedef struct StaticInt {
    char *name;
    int value;
} static_int;

typedef struct String {
    char *name;
    char *content;
} str_format;

typedef struct CommandNode {
    char *cmd_name;
    int num_param;
    int parameters[3];
    char *print_format;
    enum DataType type;
    enum DataType return_type;
    enum DataType array_type;
    struct CommandNode *left;
    struct CommandNode *right;
} cmd_node;

typedef struct MethodTable {
    char *method_name;
    int num_param;
    int total_bytes;
    int num_register;
    enum DataType return_type;
    char *return_str;
    int return_value;
    cmd_node* cmd_table[100];
    int num_commands;
    local_var *local_vars[100];
    int num_local_vars;
    compiler_temp *intermediate_vars[100];
    int num_intermediate_vars;
} method_scope;

void checkProgram(struct ASTNode*, char *);
void checkMainClass(struct ASTNode*);

enum DataType checkType(struct ASTNode *);
enum DataType checkPrimeType(struct ASTNode *);

void checkStaticVarDecl(struct ASTNode*, method_scope *);
cmd_node *checkEqlExp(struct ASTNode *, method_scope *);
void checkStaticVarDeclTail(struct ASTNode*, method_scope *);

void forwardStaticMethodDecl(struct ASTNode *);
void forwardIfFormalList(struct ASTNode *, method_scope *);
void forwardFormalList(struct ASTNode *, method_scope *);
void forwardFormalListTail(struct ASTNode *, method_scope *);

void checkStaticMethodDecl(struct ASTNode*);
void checkIfFormalList(struct ASTNode*, method_scope *);
void checkFormalList(struct ASTNode*, method_scope *);
void checkFormalListTail(struct ASTNode*, method_scope *);

void checkMainMethod(struct ASTNode*);
void checkStatementList(struct ASTNode*, method_scope*);
void checkStatement(struct ASTNode*, method_scope*);

void checkVarDecl(struct ASTNode*, method_scope *);
void checkVarDeclTail(struct ASTNode *, method_scope *);

cmd_node *checkMethodCall(struct ASTNode*, method_scope *);
cmd_node *preCheckExpList(struct ASTNode*, method_scope *);
cmd_node *preCheckExpListTail(struct ASTNode*, method_scope *);
cmd_node *checkExpList(struct ASTNode*, method_scope *);
cmd_node *checkExpListTail(struct ASTNode*, method_scope *, int);

cmd_node *checkExpOr(struct ASTNode *, method_scope *);
cmd_node *checkExpAnd(struct ASTNode *, method_scope *);
cmd_node *checkExpEql(struct ASTNode *, method_scope *);
cmd_node *checkExpIneql(struct ASTNode *, method_scope *);
cmd_node *checkExpPlusMinus(struct ASTNode*, method_scope *);
cmd_node *checkExpMulDiv(struct ASTNode*, method_scope *);
cmd_node *checkExpFactor(struct ASTNode*, method_scope *);
cmd_node *checkFactor(struct ASTNode*, method_scope *);

cmd_node *checkIndex(struct ASTNode *index, method_scope *);
cmd_node *checkLeftValue(struct ASTNode*, method_scope *);

/* Helper functions */
bool if_epsilon(struct ASTNode *);
char *name_generator(char *, int);

method_scope *create_method_scope(char *name);
cmd_node *create_command_node(char *cmd_name, enum DataType type);
cmd_node *create_command_node_one_param(char *cmd_name, int param1, enum DataType type);
cmd_node *create_command_node_two_param(char *cmd_name, int param1, int param2, enum DataType type);
cmd_node *create_command_node_three_param(char *cmd_name, int param1, int param2, int param3, enum DataType type);

void add_method(method_scope *method);
void add_cmd_to_table(method_scope *, cmd_node *node);
void add_local_var(method_scope *, char* id, enum DataType type);
void add_local_var_with_offset(method_scope *method, char* id, enum DataType type, int offset);
void add_compiler_temp(method_scope *, int id);
void add_compiler_temp_with_offset(method_scope *, int id, int offset);
void add_static_int(char *name, int value);
void add_string(char *name, char *content);
void add_static_bool(char *name, int value);

method_scope *find_method(char *name);
local_var *find_local_var(method_scope *, char* id);
int find_int_lit_offset(method_scope *, int id);
static_int *find_static_int(char *id);
str_format *find_string(char *id);
static_int *find_static_bool(char *id);

#endif
