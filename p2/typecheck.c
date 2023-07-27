#include "typecheck.h"
#include "node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Important! At each nested level, a symbol_table is passed down from upper
// levels. However, variables created in current level should not be visible
// from upper levels, so local variables should get a new symbol_table.
// Still need to typecheck with the symbol_table passed down, and also need to
// typecheck with the current symbol_table created for local variables.

/*
 * Need to give a parameter to almost every function, especially lower levels
 * ones like exp, so that they can find symbol using the correct local table.
 */

int num_method = 0;
struct MethodTable *method_table[50];
int num_forward = 0;
struct MethodTable *forward_table[50];
bool if_forward = true;

static void report(int line_number) {
    fprintf(stderr, "Type violation in line %d\n", line_number);
}

void checkProgram(struct ASTNode *program) {
    checkMainClass(program->children[program->num_children-1]);
}
void checkMainClass(struct ASTNode *mainClass) {
    struct TableTree *root = create_tree_node(NULL);
    char *name = mainClass->data.value.string_value;
    root->current_scope = name;
    forwardStaticMethodDecl(mainClass->children[1], root);
    checkStaticVarDecl(mainClass->children[0], root);
    checkStaticMethodDecl(mainClass->children[1], root);
    if_forward = false;
    checkMainMethod(mainClass->children[2], root);
}
expression checkType(struct ASTNode *type, int dim) {
    enum NodeType typeNodeType = type->node_type;
    if (typeNodeType == NODETYPE_PRIMETYPE) {
        return checkPrimeType(type->children[0], dim);
    } else if (typeNodeType == NODETYPE_TYPE) {
        return checkType(type->children[0], dim + 1);
    }
}
expression checkPrimeType(struct ASTNode *primeType, int dim) {
    enum DataType primeDataType = primeType->data.type;
    expression new_node = { DATATYPE_UNDEFINED, dim };
    if (primeDataType == DATATYPE_INT) {
        new_node.type = DATATYPE_INT;
        return new_node;
    }
    if (primeDataType == DATATYPE_STR) {
        new_node.type = DATATYPE_STR;
        return new_node;
    }
    if (primeDataType == DATATYPE_BOOLEAN) {
        new_node.type = DATATYPE_BOOLEAN;
        return new_node;
    }
}

void checkStaticVarDecl(struct ASTNode *staticVarDecl, struct TableTree *root) {
    if (if_epsilon(staticVarDecl)) return;
    checkStaticVarDecl(staticVarDecl->children[0], root);
    char *name = staticVarDecl->data.value.string_value;
    struct SymbolTableEntry *ptr = find_symbol(name, root);
    expression type_dim = checkType(staticVarDecl->children[1], 0);
    if (ptr) {
        if (ptr->type != DATATYPE_UNDEFINED) {
            if (ptr->type != type_dim.type) {
                change_type(name, DATATYPE_UNDEFINED, root);
            }
            report(staticVarDecl->lineno);
        }
    } else {
        add(name, type_dim.type, root, type_dim.dimension);
        ptr = find_symbol(name, root);
    }
    expression type_dim2 = checkEqlExp(staticVarDecl->children[2], root);
    if (type_dim2.type == EPSILON) {}
    else if ((ptr->type != DATATYPE_UNDEFINED) && (type_dim2.type != DATATYPE_UNDEFINED)) {
        if (!type_check_new(ptr->type, type_dim2.type)) {
            report(staticVarDecl->lineno);
        } else if (type_dim2.dimension != ptr->dimension) {
            report(staticVarDecl->lineno);
        }
    }
    checkStaticVarDeclTail(staticVarDecl->children[3], type_dim, root);
}
expression checkEqlExp(struct ASTNode *eqlExp, struct TableTree *tree_node) {
    if (if_epsilon(eqlExp)) {
        expression temp = { EPSILON, 0 };
        return temp;
    }
    return checkExpOr(eqlExp->children[0], tree_node);
}
void checkStaticVarDeclTail(struct ASTNode *staticVarDeclTail, expression type_dim, struct TableTree *tree_node) {
    if (if_epsilon(staticVarDeclTail)) return;
    checkStaticVarDeclTail(staticVarDeclTail->children[0], type_dim, tree_node);
    char *name = staticVarDeclTail->data.value.string_value;
    struct SymbolTableEntry *ptr = find_symbol(name, tree_node);
    if (ptr) {
        if (ptr->type != DATATYPE_UNDEFINED) {
            if (ptr->type != type_dim.type) {
                change_type(name, DATATYPE_UNDEFINED, tree_node);
            }
            report(staticVarDeclTail->lineno);
        }
    } else {
        add(name, type_dim.type, tree_node, type_dim.dimension);
        ptr = find_symbol(name, tree_node);
    }
    expression type_dim2 = checkEqlExp(staticVarDeclTail->children[1], tree_node);
    if (type_dim2.type == EPSILON) {
        return;
    }
    else if ((ptr->type != DATATYPE_UNDEFINED) && (type_dim2.type != DATATYPE_UNDEFINED)) {
        if (!type_check_new(ptr->type, type_dim2.type)) {
            report(staticVarDeclTail->lineno);
        } else if (ptr->dimension != type_dim2.dimension) {
            report(staticVarDeclTail->lineno);
        }
    }
}

void checkStaticMethodDecl(struct ASTNode *staticMethodDecl, struct TableTree *tree_node) {
    if (if_epsilon(staticMethodDecl)) return;
    checkStaticMethodDecl(staticMethodDecl->children[0], tree_node);
    char *name = staticMethodDecl->data.value.string_value;
    expression type_dim = checkType(staticMethodDecl->children[1], 0);
    struct MethodTable *ptr = find_method(name);
    if (ptr) {
        if (ptr->type_dim.type != DATATYPE_UNDEFINED) {
            if (ptr->type_dim.type != type_dim.type) {
                change_method_type(name, DATATYPE_UNDEFINED);
            }
            report(staticMethodDecl->lineno);
        }
    } else {
        add_to_method_table(name, type_dim);
    }
    checkIfFormalList(staticMethodDecl->children[2], name);
    struct TableTree *new_tree_node = create_tree_node(tree_node);
    new_tree_node->current_scope = name;
    checkStatementList(staticMethodDecl->children[3], new_tree_node);
}
void checkIfFormalList(struct ASTNode *ifFormalList, char *method_id) {
    if (if_epsilon(ifFormalList)) return;
    checkFormalList(ifFormalList->children[0], method_id);
}
void checkFormalList(struct ASTNode *formalList, char *method_id) {
    char *name = formalList->data.value.string_value;
    expression type_dim = checkType(formalList->children[0], 0);
    struct MethodTable *method = find_method(method_id);
    add_parameter(method, name, type_dim);
    checkFormalListTail(formalList->children[1], method_id);
    if (if_undefined_param(method)) report(formalList->lineno);
}
void checkFormalListTail(struct ASTNode *formalListTail, char *method_id) {
    if (if_epsilon(formalListTail)) return;
    checkFormalListTail(formalListTail->children[0], method_id);
    char *name = formalListTail->data.value.string_value;
    expression type_dim = checkType(formalListTail->children[1], 0);
    struct MethodTable *method = find_method(method_id);
    struct SymbolTableEntry *ptr = find_parameter(name, method); // Find in own method symbol_table
    if (ptr) {
        if (ptr->type != DATATYPE_UNDEFINED) {
            change_parameter_type(name, DATATYPE_UNDEFINED, method);
        }
        type_dim.type = DATATYPE_UNDEFINED;
        add_parameter(method, name, type_dim);
    } else {
        add_parameter(method, name, type_dim); // Add to own method symbol table
    }
}
void forwardStaticMethodDecl(struct ASTNode *staticMethodDecl, struct TableTree *tree_node) {
    if (if_epsilon(staticMethodDecl)) return;
    forwardStaticMethodDecl(staticMethodDecl->children[0], tree_node);
    char *name = staticMethodDecl->data.value.string_value;
    expression type_dim = checkType(staticMethodDecl->children[1], 0);
    struct MethodTable *ptr = find_forward_method(name);
    if (ptr) {
        if (ptr->type_dim.type != DATATYPE_UNDEFINED) {
            if (ptr->type_dim.type != type_dim.type) {
                change_forward_method_type(name, DATATYPE_UNDEFINED);
            }
        }
    } else {
        add_to_forward_table(name, type_dim);
    }
    forwardIfFormalList(staticMethodDecl->children[2], name);
}
void forwardIfFormalList(struct ASTNode *ifFormalList, char *method_id) {
    if (if_epsilon(ifFormalList)) return;
    forwardFormalList(ifFormalList->children[0], method_id);
}
void forwardFormalList(struct ASTNode *formalList, char *method_id) {
    char *name = formalList->data.value.string_value;
    expression type_dim = checkType(formalList->children[0], 0);
    struct MethodTable *method = find_forward_method(method_id);
    add_parameter(method, name, type_dim);
    forwardFormalListTail(formalList->children[1], method_id);
}
void forwardFormalListTail(struct ASTNode *formalListTail, char *method_id) {
    if (if_epsilon(formalListTail)) return;
    forwardFormalListTail(formalListTail->children[0], method_id);
    char *name = formalListTail->data.value.string_value;
    expression type_dim = checkType(formalListTail->children[1], 0);
    struct MethodTable *method = find_forward_method(method_id);
    struct SymbolTableEntry *ptr = find_parameter(name, method); // Find in own method symbol_table
    if (ptr) {
        if (ptr->type != DATATYPE_UNDEFINED) {
            change_parameter_type(name, DATATYPE_UNDEFINED, method);
        }
        type_dim.type = DATATYPE_UNDEFINED;
        add_parameter(method, name, type_dim);
    } else {
        add_parameter(method, name, type_dim); // Add to own method symbol table
    }
}

void checkMainMethod(struct ASTNode *mainMethod, struct TableTree *tree_node) {
    char *name = mainMethod->data.value.string_value;
    // Create new level and pass it down
    struct TableTree *new_tree_node = create_tree_node(tree_node);
    add(name, DATATYPE_STR, new_tree_node, 1);
    new_tree_node->current_scope = malloc(5);
    strncpy(new_tree_node->current_scope, "main", 4);
    new_tree_node->current_scope[4] = '\0';
    checkStatementList(mainMethod->children[0], new_tree_node);
}
void checkStatementList(struct ASTNode *statementList, struct TableTree *tree_node) {
    if (if_epsilon(statementList)) return;
    checkStatementList(statementList->children[0], tree_node);
    checkStatement(statementList->children[1], tree_node);
}
void checkStatement(struct ASTNode *statement, struct TableTree *tree_node) {
    enum NodeType statementType = statement->node_type;
    expression type, type1, type2;
    struct TableTree *new_tree_node;
    switch (statementType) {
        case NODETYPE_VARDECL:
            checkVarDecl(statement->children[0], tree_node);
            break;
        case NODETYPE_STATEMENTLIST:
            new_tree_node = create_tree_node(tree_node);
            new_tree_node->current_scope = tree_node->current_scope;
            checkStatementList(statement->children[0], new_tree_node);
            break;
        case NODETYPE_IF:
            type = checkExpOr(statement->children[0], tree_node);
            if ((type.type != DATATYPE_BOOLEAN ) && (type.type != DATATYPE_UNDEFINED)) {
                report(statement->lineno);
            }
            checkStatement(statement->children[1], tree_node);
            checkStatement(statement->children[2], tree_node);
            break;
        case NODETYPE_WHILE:
            type = checkExpOr(statement->children[0], tree_node);
            if ((type.type != DATATYPE_BOOLEAN ) && (type.type != DATATYPE_UNDEFINED)) {
                report(statement->lineno);
            }
            checkStatement(statement->children[1], tree_node);
            break;
        case NODETYPE_PRINTLN:
            type = checkExpOr(statement->children[0], tree_node);
            if (type.type != DATATYPE_UNDEFINED) {
                if ((type.type != DATATYPE_INT) && (type.type != DATATYPE_STR) && (type.type != DATATYPE_BOOLEAN)) {
                    report(statement->lineno);
                }
            }
            break;
        case NODETYPE_PRINT:
            type = checkExpOr(statement->children[0], tree_node);
            if (type.type != DATATYPE_UNDEFINED) {
                if ((type.type != DATATYPE_INT) && (type.type != DATATYPE_STR) && (type.type != DATATYPE_BOOLEAN)) {
                    report(statement->lineno);
                }
            }
            break;
        case NODETYPE_LEFTVALUE: // TODO
            type1 = checkLeftValue(statement->children[0], tree_node, 0);
            if (type1.type == DATATYPE_UNDEFINED) {
                return;
            }
            type2 = checkExpOr(statement->children[1], tree_node);
            if (type2.type == DATATYPE_UNDEFINED) {
                return;
            }
            if ((type1.type != type2.type) || (type1.dimension != type2.dimension)) {
                report(statement->lineno);
                return;
            }
            break;
        case NODETYPE_RETURN: // TODO: array things
            type = checkExpOr(statement->children[0], tree_node);
            if (strcmp(tree_node->current_scope, "main") == 0) {
                report(statement->lineno);
                return;
            }
            struct MethodTable *curr_method = find_method(tree_node->current_scope);
            if ((curr_method->type_dim.type != DATATYPE_UNDEFINED) && (type.type != DATATYPE_UNDEFINED)) {
                if ((type.type != curr_method->type_dim.type) || (type.dimension != curr_method->type_dim.dimension)) {
                    report(statement->lineno);
                }
            }
            break;
        case NODETYPE_METHODCALL:
            checkMethodCall(statement->children[0], tree_node);
            break;
    }
}
void checkVarDecl(struct ASTNode *varDecl, struct TableTree *tree_node) {
    char *name = varDecl->data.value.string_value;
    expression type1 = checkType(varDecl->children[0], 0);
    struct SymbolTableEntry *ptr = find_symbol(name, tree_node); // Own symbol_table
    if (ptr) {
        if (ptr->type != DATATYPE_UNDEFINED) {
            if (ptr->type != type1.type) {
                change_type(name, DATATYPE_UNDEFINED, tree_node);
            }
            report(varDecl->lineno);
        }
    } else {
        add(name, type1.type, tree_node, type1.dimension);
        ptr = find_symbol(name, tree_node);
    }
    expression type2 = checkEqlExp(varDecl->children[1], tree_node);
    if (type2.type == EPSILON) {}
    else if ((ptr->type != DATATYPE_UNDEFINED) && (type2.type != DATATYPE_UNDEFINED)) {
        if (!type_check_new(ptr->type, type2.type)) {
            report(varDecl->lineno);
        } else if (ptr->dimension != type2.dimension) {
            report(varDecl->lineno);
        }
    }
    checkStaticVarDeclTail(varDecl->children[2], type1, tree_node);
}

expression checkMethodCall(struct ASTNode *methodCall, struct TableTree *tree_node) {
    enum NodeType methodCallNodeType = methodCall->node_type;
    char *name;
    if (methodCallNodeType == NODETYPE_EXPLIST) {
        name = methodCall->data.value.string_value;
        struct MethodTable *ptr;
        if (if_forward) {
            ptr = find_forward_method(name);
        } else {
            ptr = find_method(name);
        }
        if (!ptr) {
            report(methodCall->lineno);
            expression temp = { DATATYPE_UNDEFINED, 0 };
            return temp;
        }
        checkExpList(methodCall->children[0], ptr, tree_node);
        return ptr->type_dim;
    } else if (methodCallNodeType == NODETYPE_ID) {
        name = methodCall->data.value.string_value;
        struct MethodTable *ptr;
        if (if_forward) {
            ptr = find_forward_method(name);
        } else {
            ptr = find_method(name);
        }
        if (!ptr) {
            report(methodCall->lineno);
            expression temp = { DATATYPE_UNDEFINED, 0 };
            return temp;
        }
        return ptr->type_dim;
    } else if (methodCallNodeType == NODETYPE_PARSEINT) {
        expression type1 = checkExpOr(methodCall->children[0], tree_node);
        if ((type1.type != DATATYPE_UNDEFINED) && (type1.type != DATATYPE_STR)) {
            if (type1.dimension != 0) {
                report(methodCall->lineno);
            }
        }
        type1.type = DATATYPE_STR;
        type1.dimension = 0;
        return type1;
    }
}

expression checkExpOr(struct ASTNode *expOr, struct TableTree *tree_node) {
    enum NodeType nodeType = expOr->node_type;
    if (nodeType == NODETYPE_EXPOR) {
        expression type1 = checkExpOr(expOr->children[0], tree_node);
        expression type2 = checkExpAnd(expOr->children[1], tree_node);
        return type_check(expOr, type1, type2, DATATYPE_BOOLEAN, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPAND) {
        return checkExpAnd(expOr->children[0], tree_node);
    }
}
expression checkExpAnd(struct ASTNode *expAnd, struct TableTree *tree_node) {
    enum NodeType nodeType = expAnd->node_type;
    if (nodeType == NODETYPE_EXPAND) {
        expression type1 = checkExpAnd(expAnd->children[0], tree_node);
        expression type2 = checkExpEql(expAnd->children[1], tree_node);
        return type_check(expAnd, type1, type2, DATATYPE_BOOLEAN, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPEQL) {
        return checkExpEql(expAnd->children[0], tree_node);
    }
}
expression checkExpEql(struct ASTNode *expEql, struct TableTree *tree_node) {
    enum NodeType nodeType = expEql->node_type;
    if (nodeType == NODETYPE_EXPEQL) {
        expression type1 = checkExpEql(expEql->children[0], tree_node);
        expression type2 = checkExpIneql(expEql->children[1], tree_node);
        return type_check(expEql, type1, type2, DATATYPE_STR, 1, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPNEQ) {
        expression type1 = checkExpEql(expEql->children[0], tree_node);
        expression type2 = checkExpIneql(expEql->children[1], tree_node);
        return type_check(expEql, type1, type2, DATATYPE_STR, 1, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPINEQL) {
        return checkExpIneql(expEql->children[0], tree_node);
    }
}
expression checkExpIneql(struct ASTNode *expIneql, struct TableTree *tree_node) {
    enum NodeType nodeType = expIneql->node_type;
    if (nodeType == NODETYPE_EXPLES) {
        expression type1 = checkExpIneql(expIneql->children[0], tree_node);
        expression type2 = checkExpPlusMinus(expIneql->children[1], tree_node);
        return type_check(expIneql, type1, type2, DATATYPE_INT, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPGRT) {
        expression type1 = checkExpIneql(expIneql->children[0], tree_node);
        expression type2 = checkExpPlusMinus(expIneql->children[1], tree_node);
        return type_check(expIneql, type1, type2, DATATYPE_INT, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPLEQ) {
        expression type1 = checkExpIneql(expIneql->children[0], tree_node);
        expression type2 = checkExpPlusMinus(expIneql->children[1], tree_node);
        return type_check(expIneql, type1, type2, DATATYPE_INT, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPGEQ) {
        expression type1 = checkExpIneql(expIneql->children[0], tree_node);
        expression type2 = checkExpPlusMinus(expIneql->children[1], tree_node);
        return type_check(expIneql, type1, type2, DATATYPE_INT, 0, DATATYPE_BOOLEAN);
    } else if (nodeType == NODETYPE_EXPPLUSMINUS) {
        return checkExpPlusMinus(expIneql->children[0], tree_node);
    }
}
expression checkExpPlusMinus(struct ASTNode *expPM, struct TableTree *tree_node) {
    enum NodeType nodeType = expPM->node_type;
    if (nodeType == NODETYPE_EXPPLUS) {
        expression type1 = checkExpPlusMinus(expPM->children[0], tree_node);
        expression type2 = checkExpMulDiv(expPM->children[1], tree_node);
        return type_check(expPM, type1, type2, DATATYPE_INT, 0, type1.type);
    } else if (nodeType == NODETYPE_EXPMINUS) {
        expression type1 = checkExpPlusMinus(expPM->children[0], tree_node);
        expression type2 = checkExpMulDiv(expPM->children[1], tree_node);
        return type_check(expPM, type1, type2, DATATYPE_INT, 0, type1.type);
    } else if (nodeType == NODETYPE_EXPMULDIV) {
        return checkExpMulDiv(expPM->children[0], tree_node);
    }
}
expression checkExpMulDiv(struct ASTNode *expMD, struct TableTree *tree_node) {
    enum NodeType nodeType = expMD->node_type;
    if (nodeType == NODETYPE_EXPMUL) {
        expression type1 = checkExpMulDiv(expMD->children[0], tree_node);
        expression type2 = checkExpFactor(expMD->children[1], tree_node);
        return type_check(expMD, type1, type2, DATATYPE_INT, 0, type1.type);
    } else if (nodeType == NODETYPE_EXPDIV) {
        expression type1 = checkExpMulDiv(expMD->children[0], tree_node);
        expression type2 = checkExpFactor(expMD->children[1], tree_node);
        return type_check(expMD, type1, type2, DATATYPE_INT, 0, type1.type);
    } else if (nodeType == NODETYPE_EXPFACTOR) {
        return checkExpFactor(expMD->children[0], tree_node);
    }
}
expression checkExpFactor(struct ASTNode *expFactor, struct TableTree *tree_node) {
    return checkFactor(expFactor->children[0], tree_node);
}
expression checkFactor(struct ASTNode *factor, struct TableTree *tree_node) {
    enum NodeType nodeType = factor->node_type;
    expression type1, type2;
    switch (nodeType) {
        case NODETYPE_NEG:
            type1 = checkFactor(factor->children[0], tree_node);
            if (type1.dimension != 0) {
                type1.type = DATATYPE_UNDEFINED;
                return type1;
            }
            type2.type = DATATYPE_BOOLEAN;
            return type_check(factor, type1, type2, DATATYPE_BOOLEAN, 0, DATATYPE_BOOLEAN);
        case NODETYPE_PLUS:
            type1 = checkFactor(factor->children[0], tree_node);
            if (type1.dimension != 0) {
                type1.type = DATATYPE_UNDEFINED;
                return type1;
            }
            type2.type = DATATYPE_INT;
            return type_check(factor, type1, type2, DATATYPE_INT, 0, DATATYPE_INT);
        case NODETYPE_MINUS:
            type1 = checkFactor(factor->children[0], tree_node);
            if (type1.dimension != 0) {
                type1.type = DATATYPE_UNDEFINED;
                return type1;
            }
            type2.type = DATATYPE_INT;
            return type_check(factor, type1, type2, DATATYPE_INT, 0, DATATYPE_INT);
        case NODETYPE_FACTORRECUR:
            return checkExpOr(factor->children[0], tree_node);
        case NODETYPE_LEFTVALUE:
            return checkLeftValue(factor->children[0], tree_node, 0);
        case NODETYPE_LEFTVALUELENGTH:
            type1 = checkLeftValue(factor->children[0], tree_node, 0);
            if (type1.type == DATATYPE_UNDEFINED) return type1;
            expression temp = { DATATYPE_UNDEFINED, 0 };
            if (type1.dimension == 0) {
                report(factor->lineno);
                return temp;
            }
            temp.type = DATATYPE_INT;
            temp.dimension = 0;
            return temp;
        case NODETYPE_INT:
            type1.type = DATATYPE_INT;
            type1.dimension = 0;
            return type1;
        case NODETYPE_STR:
            type1.type = DATATYPE_STR;
            type1.dimension = 0;
            return type1;
        case NODETYPE_TRUE:
            type1.type = DATATYPE_BOOLEAN;
            type1.dimension = 0;
            return type1;
        case NODETYPE_FALSE:
            type1.type = DATATYPE_BOOLEAN;
            type1.dimension = 0;
            return type1;
        case NODETYPE_METHODCALL:
            return checkMethodCall(factor->children[0], tree_node);
        case NODETYPE_NEW:
            type1 = checkPrimeType(factor->children[0], 0);
            type2 = checkIndex(factor->children[1], tree_node, 1);
            if (type2.type == DATATYPE_UNDEFINED) {
                return type2;
            }
            switch (type1.type) {
                case DATATYPE_INT:
                    type1.type = NEW_INT;
                    break;
                case DATATYPE_STR:
                    type1.type = NEW_STR;
                    break;
                case DATATYPE_BOOLEAN:
                    type1.type = NEW_BOOL;
                    break;
            }
            type1.dimension = type2.dimension;
            return type1;
    }
}

expression checkIndex(struct ASTNode *index, struct TableTree *tree_node, int dim) {
    enum NodeType nodeType = index->node_type;
    if (nodeType == NODETYPE_INDEXRECUR) {
        expression type_dim1 = checkIndex(index->children[0], tree_node, dim + 1);
        expression type_dim2 = checkExpOr(index->children[1], tree_node);
        if (type_dim1.type == DATATYPE_UNDEFINED) {
            return type_dim1;
        }
        if ((type_dim2.type != DATATYPE_INT) || (type_dim2.dimension != 0)) {
            if (type_dim2.type != DATATYPE_UNDEFINED) {
                report(index->lineno);
                type_dim2.type = DATATYPE_UNDEFINED;
                return type_dim2;
            }
            return type_dim2;
        }
        type_dim1.dimension += 1;
        return type_dim1;
    } else if (nodeType == NODETYPE_INDEX) {
        expression type_dim = checkExpOr(index->children[0], tree_node);
        if ((type_dim.type != DATATYPE_INT) || (type_dim.dimension != 0)) {
            if (type_dim.type != DATATYPE_UNDEFINED) {
                report(index->lineno);
                type_dim.type = DATATYPE_UNDEFINED;
            }
            return type_dim;
        }
        type_dim.dimension = dim;
        return type_dim;
    }
}
void checkExpList(struct ASTNode *expList, struct MethodTable *method, struct TableTree *tree_node) {
    expression type_dim = checkExpOr(expList->children[0], tree_node);
    int if_violation = check_parameter(expList, method, 0, type_dim);
    if (if_violation != 0) {
        return;
    }
    int ret = checkExpListTail(expList->children[1], method, 1, tree_node);
    if (ret == -2) report(expList->lineno);
}
int checkExpListTail(struct ASTNode *expListTail, struct MethodTable *method, int index, struct TableTree *tree_node) {
    if (if_epsilon(expListTail)) {
        if (index + 1 == method->num_param) return -2;
        return 0;
    }
    int ret = checkExpListTail(expListTail->children[0], method, index + 1, tree_node);
    if (ret == -1) {
        return -1;
    }
    if (ret == -2) {
        return -2;
    }
    expression type_dim = checkExpOr(expListTail->children[1], tree_node);
    int if_report = check_parameter(expListTail, method, index, type_dim);
    return if_report;
}
expression checkLeftValue(struct ASTNode *leftValue, struct TableTree *tree_node, int dimension) {
    enum NodeType nodeType = leftValue->node_type;
    if (nodeType == NODETYPE_LEFTVALUE) {
        char *name = leftValue->data.value.string_value;
        struct SymbolTableEntry *var = find_symbol(name, tree_node);
        if (var) {
            expression temp = { var->type, dimension };
            if (dimension != 0) {
                if (dimension != var->dimension) {
                    if (dimension > var->dimension) {
                        report(leftValue->lineno);
                        temp.type = DATATYPE_UNDEFINED;
                        temp.dimension = 0;
                        return temp;
                    } else {
                        temp.dimension = var->dimension - dimension;
                        return temp;
                    }
                } else {
                    temp.dimension = 0;
                    return temp;
                }
            }
            temp.dimension = var->dimension;
            return temp;
        } else {
            report(leftValue->lineno);
            expression temp = { DATATYPE_UNDEFINED, 0 };
            return temp;
        }
    } else if (nodeType == NODETYPE_LEFTVALUERECUR) {
        expression type_dim1 = checkLeftValue(leftValue->children[0], tree_node, dimension + 1);
        expression type_dim2 = checkExpOr(leftValue->children[1], tree_node);
        if ((type_dim2.type != DATATYPE_INT) && (type_dim1.type != DATATYPE_UNDEFINED)) {
            report(leftValue->lineno);
            expression temp = { DATATYPE_UNDEFINED, 0 };
            return temp;
        }
        return type_dim1;
    }
}

/* ---------Helper functions--------- */

struct TableTree *create_tree_node(struct TableTree *parent){
    struct TableTree* new_node = malloc(sizeof(struct TableTree));
    new_node->parent = parent;
    new_node->num_entries = 0;
    new_node->current_scope = NULL;
    return new_node;
}
void add(char* id, enum DataType type, struct TableTree *tree_node, int dim){
    struct SymbolTableEntry *entry = malloc(sizeof(struct SymbolTableEntry));
    entry->id =id;
    entry->type = type;
    entry->dimension = dim;
    tree_node->table[tree_node->num_entries] = entry;
    tree_node->num_entries += 1;
}
void add_to_method_table(char *id, expression type_dim) {
    struct MethodTable *entry = malloc(sizeof(struct MethodTable));
    entry->id = id;
    entry->type_dim.type = type_dim.type;
    entry->type_dim.dimension = type_dim.dimension;
    entry->num_param = 0;
    method_table[num_method] = entry;
    num_method++;
}
void add_parameter(struct MethodTable *method, char *param_name, expression param_type_dim) {
    struct SymbolTableEntry *param = malloc(sizeof(struct SymbolTableEntry));
    param->id = param_name;
    param->type = param_type_dim.type;
    param->dimension = param_type_dim.dimension;
    method->parameters[method->num_param] = param;
    method->num_param += 1;
}
void add_to_forward_table(char *id, expression type_dim) {
    struct MethodTable *entry = malloc(sizeof(struct MethodTable));
    entry->id = id;
    entry->type_dim.type = type_dim.type;
    entry->type_dim.dimension = type_dim.dimension;
    entry->num_param = 0;
    forward_table[num_forward] = entry;
    num_forward++;
}

struct SymbolTableEntry *find_symbol(char* id, struct TableTree *tree_node){
    struct SymbolTableEntry *found = NULL;
    for (int i = 0; i < tree_node->num_entries; ++i) {
        if(strcmp(id, tree_node->table[i]->id) == 0){
            found = tree_node->table[i];
        }
    }
    if (found) {
        return found;
    } else {
        if (tree_node->parent) {
            return find_symbol(id, tree_node->parent);
        }
    }
    return found;
}
struct MethodTable *find_method(char *id) {
    for (int i = 0; i < num_method; i++) {
        if(strcmp(id, method_table[i]->id) == 0){
            return method_table[i];
        }
    }
    return NULL;
}
struct SymbolTableEntry *find_parameter(char *id, struct MethodTable *method) {
    for (int i = 0; i < method->num_param; i++) {
        if(strcmp(id, method->parameters[i]->id) == 0){
            return method->parameters[i];
        }
    }
    return NULL;
}
struct MethodTable *find_forward_method(char *id) {
    for (int i = 0; i < num_forward; i++) {
        if(strcmp(id, forward_table[i]->id) == 0){
            return forward_table[i];
        }
    }
    return NULL;
}

void change_type(char *id, enum DataType newType, struct TableTree *tree_node) {
    struct SymbolTableEntry *temp = find_symbol(id, tree_node);
    if (temp) temp->type = newType;
}
void change_method_type(char *id, enum DataType newType) {
    struct MethodTable *method = find_method(id);
    method->type_dim.type = newType;
}
void change_parameter_type(char *id, enum DataType newType, struct MethodTable *method) {
    struct SymbolTableEntry *param = find_parameter(id, method);
    param->type = newType;
}
void change_forward_method_type(char *id, enum DataType newType) {
    struct MethodTable *method = find_forward_method(id);
    method->type_dim.type = newType;
}

int check_parameter(struct ASTNode *node, struct MethodTable *method, int index, expression type_dim) {
    if (type_dim.type == DATATYPE_UNDEFINED) {
        return -1;
    }
    if (index >= method->num_param) {
        report(node->lineno);
        return -1;
    }
    if (method->parameters[index]->type != type_dim.type) {
        if (method->parameters[index]->type != DATATYPE_UNDEFINED) {
            report(node->lineno);
            return -1;
        }
    }
    if (method->parameters[index]->dimension != type_dim.dimension) {
        if (method->parameters[index]->type != DATATYPE_UNDEFINED) {
            report(node->lineno);
            return -1;
        }
    }
    return 0;
}
bool if_epsilon(struct ASTNode *node) {
    if (node->node_type == NODETYPE_EPSILON) {
        return true;
    }
    else {
        return false;
    }
}
expression type_check(struct ASTNode *node, expression type1, expression type2, enum DataType requirement, int lever, enum DataType return_value) {
    expression ret = { return_value, 0 };
    expression undefined = { DATATYPE_UNDEFINED, 0 };
    if (lever == 0) {
        if ((type1.type != DATATYPE_UNDEFINED) && (type2.type != DATATYPE_UNDEFINED)) {
            if (type1.dimension != type2.dimension) {
                report(node->lineno);
                return undefined;
            }
            if (type1.type != type2.type) {
                report(node->lineno);
                return undefined;
            } else {
                if ((type1.type != requirement) || (type2.type != requirement)) {
                    report(node->lineno);
                    return undefined;
                }
                return ret;
            }
        } else {
            return undefined;
        }
    } else {
        if ((type1.type != DATATYPE_UNDEFINED) && (type2.type != DATATYPE_UNDEFINED)) {
            if (type1.dimension != type2.dimension) {
                report(node->lineno);
                return undefined;
            }
            if (type1.type != type2.type) {
                report(node->lineno);
                return undefined;
            } else {
                if ((type1.type == requirement) || (type2.type == requirement) ||
            (type1.type == NEW_INT) || (type1.type == NEW_STR) || (type1.type == NEW_BOOL) ||
        (type2.type == NEW_INT) || (type2.type == NEW_STR) || (type2.type == NEW_BOOL)) {
                    report(node->lineno);
                    return undefined;
                }
                return ret;
            }
        } else {
            return undefined;
        }
    }
}
bool type_check_new(enum DataType type1, enum DataType type2) {
    if ((type1 == DATATYPE_INT) && (type2 == NEW_INT)) return true;
    if ((type1 == DATATYPE_INT) && (type2 == DATATYPE_INT)) return true;
    if ((type1 == DATATYPE_STR) && (type2 == NEW_STR)) return true;
    if ((type1 == DATATYPE_STR) && (type2 == DATATYPE_STR)) return true;
    if ((type1 == DATATYPE_BOOLEAN) && (type2 == NEW_BOOL)) return true;
    if ((type1 == DATATYPE_BOOLEAN) && (type2 == DATATYPE_BOOLEAN)) return true;
    return false;
}
bool if_undefined_param(struct MethodTable *method) {
    for (int i = 0; i < method->num_param; i++) {
        if (method->parameters[i]->type == DATATYPE_UNDEFINED){
            return true;
        }
    }
    return false;
}
