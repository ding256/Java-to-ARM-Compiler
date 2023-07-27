#ifndef NODE_H
#define NODE_H
#define MAX_NUM_CHILDREN 5

#include <stdbool.h>

enum DataType {
    DATATYPE_UNDEFINED,
    DATATYPE_STR,
    DATATYPE_INT,
    DATATYPE_BOOLEAN,
    EPSILON,
    INT_LITERAL,
    STR_LITERAL,
    BOOL_LITERAL,
    PRINT,
    STATIC_INT,
    STATIC_BOOL,
    METHODCALL,
    RETURN,
    ARRAY,
};

// Returns the name of the given data type.
static inline const char *type_string(enum DataType t) {
    static const char *names[] = {"Undefined", "String", "Integer", "Boolean"};
    return names[t % 4];
}

enum NodeType {
    NODETYPE_EPSILON,
    NODETYPE_PROGRAM,
    NODETYPE_MAINCLASS,
    NODETYPE_MAINMETHOD,
    NODETYPE_STATICVARDECL,
    NODETYPE_STATICMETHODDECL,
    NODETYPE_FORMALLIST,
    NODETYPE_STATEMENT,
    NODETYPE_STATEMENTLIST,
    NODETYPE_METHODCALL,
    NODETYPE_EQLEXP,
    NODETYPE_STATICVARDECLTAIL,
    NODETYPE_EXPLISTTAIL,
    NODETYPE_OPERATORS,
    NODETYPE_FACTOR,
    NODETYPE_FORMALLISTTAIL,
    NODETYPE_IFFORMALLIST,

    NODETYPE_VARDECL,
    NODETYPE_PRINT,
    NODETYPE_PRINTLN,

    NODETYPE_TYPE,
    NODETYPE_PRIMETYPE,
    NODETYPE_INDEX,
    NODETYPE_EXPLIST,
    NODETYPE_LEFTVALUE,
    NODETYPE_EXPOR,
    NODETYPE_EXPAND,
    NODETYPE_EXPEQL,
    NODETYPE_EXPNEQ,
    NODETYPE_EXPINEQL,
    NODETYPE_EXPLES,
    NODETYPE_EXPGRT,
    NODETYPE_EXPLEQ,
    NODETYPE_EXPGEQ,
    NODETYPE_EXPPLUSMINUS,
    NODETYPE_EXPPLUS,
    NODETYPE_EXPMINUS,
    NODETYPE_EXPMULDIV,
    NODETYPE_EXPMUL,
    NODETYPE_EXPDIV,
    NODETYPE_EXPFACTOR,
    NODETYPE_IF,
    NODETYPE_WHILE,
    NODETYPE_PARSEINT,
    NODETYPE_RETURN,

    NODETYPE_INDEXRECUR,
    NODETYPE_LEFTVALUERECUR,
    NODETYPE_NEG,
    NODETYPE_PLUS,
    NODETYPE_MINUS,
    NODETYPE_FACTORRECUR,
    NODETYPE_LEFTVALUELENGTH,
    NODETYPE_INT,
    NODETYPE_STR,
    NODETYPE_TRUE,
    NODETYPE_FALSE,
    NODETYPE_NEW,
    NODETYPE_ID,
};

struct SemanticData {
    enum DataType type;
    union value_t {
        char* string_value;
        int int_value;
        bool boolean_value;
    } value;
};

struct ASTNode {
    int num_children;
    enum NodeType node_type;
    struct SemanticData data;
    int lineno;
    struct ASTNode* children[MAX_NUM_CHILDREN];
};

// Creates a new node with 0 children on the heap using `malloc()`.
struct ASTNode* new_node(enum NodeType t);
// Adds the given children to the parent node. Returns -1 if the capacity is full.
int add_child(struct ASTNode* parent, struct ASTNode* child);
// Set the line number for each node
void set_lineno(struct ASTNode *node, int lineno);

// Sets the data of the node to the given value and the corresponding type.

void set_string_value(struct ASTNode* node, char* s);
void set_int_value(struct ASTNode* node, int i);
void set_boolean_value(struct ASTNode* node, bool b);

#endif
