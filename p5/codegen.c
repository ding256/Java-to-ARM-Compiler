#include "codegen.h"
#include "node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Global fields
FILE *fp = NULL;
char if_count = 47;
char loop_count = 47;

static_int *static_ints[50];
int num_static_int = 0;

str_format *strings[50];
int num_strings = 0;

static_int *static_bools[50];
int num_static_bool = 0;

method_scope *methods[50];
int num_methods = 0;

void postOrderTraverse(method_scope *method, cmd_node *node, int left_or_right) {
    if (!node) return;
    postOrderTraverse(method, node->left, 0);
    postOrderTraverse(method, node->right, 1);
    if (strcmp(node->cmd_name, "amxhdastr") == 0) {
        if (node->type == METHODCALL) {
            if (node->parameters[1] != -1) {
                fprintf(fp, "\tstr r%d, [r%d, #%d]\n", node->parameters[0], node->parameters[1], node->parameters[2]);
            } else {
                fprintf(fp, "\tstr r0, [SP, #%d]\n", node->parameters[2]);
            }
        } else {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
            fprintf(fp, "\tstr r0, [SP, #%d]\n", node->parameters[2]);
        }
    } else if (strcmp(node->cmd_name, "amxhdaldr") == 0) {
        if (node->type == METHODCALL) {
            if (node->num_param == 3) {
                if (node->parameters[1] == -1) {
                    fprintf(fp, "\tldr r%d, [SP, #%d]\n", node->parameters[0], node->parameters[2]);
                } else {
                    fprintf(fp, "\tldr r%d, [r%d, #%d]\n", node->parameters[0], node->parameters[1], node->parameters[2]);
                }
            } else if (node->num_param == 2) {
                fprintf(fp, "\tmov r%d, #%d\n", node->parameters[0], node->parameters[1]);
                fprintf(fp, "\tstr r%d, [SP, #%d]\n", node->parameters[0], find_int_lit_offset(method, node->parameters[0]));
            } else if (node->num_param == 1) {
                fprintf(fp, "\tldr r%d, =%s\n", node->parameters[0], node->print_format);
            }
        }else if (node->num_param == 3) {
            if (node->parameters[1] == -1) {
                fprintf(fp, "\tldr r%d, [SP, #%d]\n", left_or_right, node->parameters[2]);
            } else if (node->return_type == ARRAY) {
                fprintf(fp, "\tldr r%d, [r%d, #%d]\n", left_or_right, node->parameters[1], node->parameters[2]);
                fprintf(fp, "\tldr r%d, [SP, #%d]\n", left_or_right, find_int_lit_offset(method, node->parameters[0]));
            } else {
                fprintf(fp, "\tldr r%d, [r%d, #%d]\n", left_or_right, left_or_right, node->parameters[2]);
            }
        } else if (node->num_param == 2) {
            fprintf(fp, "\tmov r%d, #%d\n", left_or_right, node->parameters[1]);
            fprintf(fp, "\tstr r%d, [SP, #%d]\n", left_or_right, find_int_lit_offset(method, node->parameters[0]));
        } else if (node->num_param == 1) {
            if (node->type == STATIC_INT) {
                fprintf(fp, "\tldr r%d, =%s\n", left_or_right, node->print_format);
                fprintf(fp, "\tldr r%d, [r%d, #0]\n", left_or_right, left_or_right);
            } else {
                fprintf(fp, "\tldr r%d, =%s\n", left_or_right, node->print_format);
            }
        }
    } else if (strcmp(node->cmd_name, "amxhdaldrrrr") == 0) {
        fprintf(fp, "\tldr r%d, [r%d, r%d]\n", node->parameters[0], node->parameters[1], node->parameters[2]);
    } else if (strcmp(node->cmd_name, "amxhdastrrrr") == 0) {
        fprintf(fp, "\tstr r%d, [r%d, r%d]\n", node->parameters[0], node->parameters[1], node->parameters[2]);
    } else if (strcmp(node->cmd_name, "amxhdamov") == 0) {
        fprintf(fp, "\tmov r%d, #%d\n", node->parameters[0], node->parameters[1]);
    } else if (strcmp(node->cmd_name, "amxhdamovmov") == 0) {
        fprintf(fp, "\tmov r%d, r%d\n", node->parameters[0], node->parameters[1]);
    } else if (strcmp(node->cmd_name, "amxhdaadd") == 0) {
        if ((node->left->type != STATIC_INT) && (node->left->type != ARRAY)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        if ((node->right->type != STATIC_INT) && (node->right->type != ARRAY)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[2]));
        }
        fprintf(fp, "\tadd r2, r0, r1\n");
        fprintf(fp, "\tstr r2, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdasub") == 0) {
        if ((node->left->type != STATIC_INT) && (node->left->type != METHODCALL)  && (node->left->type != ARRAY)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        if ((node->right->type != STATIC_INT) && (node->right->type != METHODCALL)  && (node->right->type != ARRAY)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[2]));
        }
        fprintf(fp, "\tsub r2, r0, r1\n");
        fprintf(fp, "\tstr r2, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamul") == 0) {
        if ((node->left->type != STATIC_INT) && (node->left->type != METHODCALL)  && (node->left->type != ARRAY)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        if ((node->right->type != STATIC_INT) && (node->right->type != METHODCALL)  && (node->right->type != ARRAY)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[2]));
        }
        fprintf(fp, "\tmul r2, r0, r1\n");
        fprintf(fp, "\tstr r2, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdacmp") == 0) {
        if ((node->left->type != STATIC_BOOL)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
        }
        if ((node->right->type != STATIC_BOOL)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        fprintf(fp, "\tcmp r0, r1\n");
    } else if (strcmp(node->cmd_name, "amxhdacmpcmp") == 0) {
        if ((node->left->type != STATIC_BOOL)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
        }
        fprintf(fp, "\tcmp r0, #%d\n", node->parameters[1]);
    } else if (strcmp(node->cmd_name, "amxhdaorr") == 0) {
        if ((node->left->type != STATIC_BOOL) && (node->left->type != METHODCALL)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        if ((node->right->type != STATIC_BOOL) && (node->right->type != METHODCALL)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[2]));
        }
        fprintf(fp, "\torr r2, r0, r1\n");
        fprintf(fp, "\tstr r2, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdaand") == 0) {
        if ((node->left->type != STATIC_BOOL) && (node->left->type != METHODCALL)) {
            fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        }
        if ((node->right->type != STATIC_BOOL) && (node->right->type != METHODCALL)) {
            fprintf(fp, "\tldr r1, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[2]));
        }
        fprintf(fp, "\tand r2, r0, r1\n");
        fprintf(fp, "\tstr r2, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamoveq") == 0) {
        fprintf(fp, "\tmoveq r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamovne") == 0) {
        fprintf(fp, "\tmovne r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamovgt") == 0) {
        fprintf(fp, "\tmovgt r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamovlt") == 0) {
        fprintf(fp, "\tmovlt r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamovge") == 0) {
        fprintf(fp, "\tmovge r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamovle") == 0) {
        fprintf(fp, "\tmovle r0, #1\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdamvn") == 0) {
        fprintf(fp, "\tldr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[1]));
        fprintf(fp, "\tmvn r0, r0\n");
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (strcmp(node->cmd_name, "amxhdabne") == 0) {
        fprintf(fp, "\tbne %s\n", node->print_format);
    } else if (strcmp(node->cmd_name, "amxhdab") == 0) {
        fprintf(fp, "\tb %s\n", node->print_format);
    } else if (strcmp(node->cmd_name, "amxhdatag") == 0) {
        fprintf(fp, "%s: @ here is a tag ---------- %s\n", node->print_format, node->print_format);
    } else if (strcmp(node->cmd_name, "bl printf") == 0) {
        fprintf(fp, "\tbl printf\n");
    } else if (node->type == METHODCALL) {
        fprintf(fp, "\tbl %s\n", node->cmd_name);
        fprintf(fp, "\tstr r0, [SP, #%d]\n", find_int_lit_offset(method, node->parameters[0]));
    } else if (node->type == RETURN) {
        //fprintf(fp, "\tadd SP, SP, #%d\n", method->total_bytes);
        fprintf(fp, "\tb %s_return\n", method->method_name);
    }
}

void printFormats() {
    fprintf(fp, "%s\n\n", "printInt: .asciz \"%d\"");
    fprintf(fp, "%s\n\n", "printStr: .asciz \"%s\"");
    fprintf(fp, "%s\n\n", "printlnInt: .asciz \"%d\\n\"");
    fprintf(fp, "%s\n\n", "printlnStr: .asciz \"%s\\n\"");
}
void printStrings() {
    for (size_t i = 0; i < num_strings; i++) {
        fprintf(fp, "%s: .asciz \"%s\"\n\n", strings[i]->name, strings[i]->content);
    }
}
void printStaticInts() {
    for (size_t i = 0; i < num_static_int; i++) {
        fprintf(fp, "%s: .word %d\n\n", static_ints[i]->name, static_ints[i]->value);
    }
}
void printStaticBools() {
    for (size_t i = 0; i < num_static_bool; i++) {
        fprintf(fp, "%s: .word %d @static_bool\n\n", static_bools[i]->name, static_bools[i]->value);
    }
}
void printMethod(method_scope *method) {
    fprintf(fp, "\n%s:\n", method->method_name);
    fprintf(fp, "\tpush {lr}\n");
    fprintf(fp, "\tsub SP, SP, #%d\n", method->total_bytes);
    if (strcmp(method->method_name, "main") == 0) {
        fprintf(fp, "\tstr r0, [SP, #0]\n");
        fprintf(fp, "\tstr r1, [SP, #4]\n");
        fprintf(fp, "\tsub r0, r0, #1\n");
        fprintf(fp, "\tstr r0, [r1, #0]\n");
        /*for (size_t i = 0; i < 900; i++) {
            fprintf(fp, "\tmov r0, r0\n");
        }*/
    } else {
        if (method->num_param > 0) {
            for (int i = 0; i < method->num_param; i++) {
                fprintf(fp, "\tstr r%d, [SP, #%d]\n", i, i * 4);
            }
        }
    }
    for (int i = 0; i < method->num_commands; i++) {
        postOrderTraverse(method, method->cmd_table[i], 0);
    }
    fprintf(fp, "%s_return:\n", method->method_name);
    fprintf(fp, "\tadd SP, SP, #%d\n", method->total_bytes);
    fprintf(fp, "\tpop {pc}\n");
}

void checkProgram(struct ASTNode *program, char *file_name) {
    fp = fopen(file_name, "w");
    checkMainClass(program->children[program->num_children - 1]);
    fprintf(fp, ".section .text\n");
    printStaticInts();
    printStaticBools();
    printFormats();
    printStrings();
    fprintf(fp, ".global main\n");
    fprintf(fp, ".balign 4\n");
    for (size_t i = 1; i < num_methods; i++) {
        printMethod(methods[i]);
    }
    fclose(fp);
    fp = NULL;
}
void checkMainClass(struct ASTNode *mainClass) {
    method_scope *global = create_method_scope("global");
    add_method(global);
    checkStaticVarDecl(mainClass->children[0], global);
    forwardStaticMethodDecl(mainClass->children[1]);
    checkStaticMethodDecl(mainClass->children[1]);
    checkMainMethod(mainClass->children[2]);
}

enum DataType checkType(struct ASTNode *type) {
    enum NodeType typeNodeType = type->node_type;
    if (typeNodeType == NODETYPE_PRIMETYPE) {
        return checkPrimeType(type->children[0]);
    } else if (typeNodeType == NODETYPE_TYPE) {
        //return checkType(type->children[0], method);
    }
}
enum DataType checkPrimeType(struct ASTNode *primeType) {
    enum DataType primeDataType = primeType->data.type;
    if (primeDataType == DATATYPE_INT) {
        return DATATYPE_INT;
    } else if (primeDataType == DATATYPE_STR) {
        return DATATYPE_STR;
    } else if (primeDataType == DATATYPE_BOOLEAN) {
        return DATATYPE_BOOLEAN;
    }
}

void checkStaticVarDecl(struct ASTNode *staticVarDecl, method_scope *global) {
    if (if_epsilon(staticVarDecl)) return;
    checkStaticVarDecl(staticVarDecl->children[0], global);
    char *id = staticVarDecl->data.value.string_value;
    cmd_node *ret = checkEqlExp(staticVarDecl->children[2], global);
    if (!ret) return;
    if (ret->type == INT_LITERAL) {
        add_static_int(id, ret->parameters[1]);
    } else if (ret->type == STR_LITERAL) {
        add_string(id, ret->cmd_name + 1);
    } else if (ret->type == BOOL_LITERAL) {
        add_static_bool(id, ret->parameters[1]);
    }
    checkStaticVarDeclTail(staticVarDecl->children[3], global);
}
cmd_node *checkEqlExp(struct ASTNode *eqlExp, method_scope *global) {
    if (if_epsilon(eqlExp)) return NULL;
    return checkExpOr(eqlExp->children[0], global);
}
void checkStaticVarDeclTail(struct ASTNode *staticVarDeclTail, method_scope *global) {
    if (if_epsilon(staticVarDeclTail)) return;
    checkStaticVarDeclTail(staticVarDeclTail->children[0], global);
    char *id = staticVarDeclTail->data.value.string_value;
    cmd_node *ret = checkEqlExp(staticVarDeclTail->children[1], global);
    if (!ret) return;
    if (ret->type == INT_LITERAL) {
        add_static_int(id, ret->parameters[1]);
    } else if (ret->type == STR_LITERAL) {
        add_string(id, ret->cmd_name + 1);
    } else if (ret->type == BOOL_LITERAL) {
        add_static_bool(id, ret->parameters[1]);
    }
}

void forwardStaticMethodDecl(struct ASTNode *staticMethodDecl) {
    if (if_epsilon(staticMethodDecl)) return;
    forwardStaticMethodDecl(staticMethodDecl->children[0]);
    char *name = staticMethodDecl->data.value.string_value;
    method_scope *method = create_method_scope(name);
    add_method(method);
    method->return_type = checkType(staticMethodDecl->children[1]);
    checkIfFormalList(staticMethodDecl->children[2], method);
    method->num_register = method->num_param;
}
void checkIfFormalList(struct ASTNode *ifFormalList, method_scope *method) {
    if (if_epsilon(ifFormalList)) return;
    checkFormalList(ifFormalList->children[0], method);
}
void checkFormalList(struct ASTNode *formalList, method_scope *method) {
    char *name = formalList->data.value.string_value;
    method->num_param += 1;
    add_local_var(method, name, checkType(formalList->children[0]));
    checkFormalListTail(formalList->children[1], method);
}
void checkFormalListTail(struct ASTNode *formalListTail, method_scope *method) {
    if (if_epsilon(formalListTail)) return;
    checkFormalListTail(formalListTail->children[0], method);
    char *name = formalListTail->data.value.string_value;
    add_local_var(method, name, checkType(formalListTail->children[1]));
    method->num_param += 1;
}

void checkStaticMethodDecl(struct ASTNode *staticMethodDecl) {
    if (if_epsilon(staticMethodDecl)) return;
    checkStaticMethodDecl(staticMethodDecl->children[0]);
    char *name = staticMethodDecl->data.value.string_value;
    method_scope *method = find_method(name);
    checkStatementList(staticMethodDecl->children[3], method);
}

/******************************************************************************/

void checkMainMethod(struct ASTNode *mainMethod) {
    method_scope *main = create_method_scope("main");
    add_method(main);
    main->total_bytes = 4;
    main->num_register = 3;
    add_local_var(main, mainMethod->data.value.string_value, ARRAY);
    find_local_var(main, mainMethod->data.value.string_value)->array_type = DATATYPE_STR;
    checkStatementList(mainMethod->children[0], main);
}
void checkStatementList(struct ASTNode *statementList, method_scope *method) {
    if (if_epsilon(statementList)) return;
    checkStatementList(statementList->children[0], method);
    checkStatement(statementList->children[1], method);
}
void checkStatement(struct ASTNode *statement, method_scope *method) {
    enum NodeType statementType = statement->node_type;
    cmd_node *temp, *temp2, *temp3;
    int local_if_count, local_loop_count;
    switch (statementType) {
        case NODETYPE_VARDECL:
            checkVarDecl(statement->children[0], method);
            break;
        case NODETYPE_STATEMENTLIST:
            checkStatementList(statement->children[0], method);
            break;
        case NODETYPE_IF:
            if_count += 1;
            local_if_count = if_count;
            temp = create_command_node("amxhdabne", DATATYPE_UNDEFINED);
            temp->print_format = name_generator("if", local_if_count);
            temp->left = create_command_node_two_param("amxhdacmpcmp", -100, 1, DATATYPE_UNDEFINED);
            temp->left->left = checkExpOr(statement->children[0], method);
            temp->left->parameters[0] = temp->left->left->parameters[0];
            add_cmd_to_table(method, temp);
            checkStatement(statement->children[1], method); // if content
            temp3 = create_command_node("amxhdab", DATATYPE_UNDEFINED);
            temp3->print_format = name_generator("endif", local_if_count);
            add_cmd_to_table(method, temp3);
            temp2 = create_command_node("amxhdatag", DATATYPE_UNDEFINED);
            temp2->print_format = name_generator("if", local_if_count);
            add_cmd_to_table(method, temp2);
            checkStatement(statement->children[2], method); // else content
            temp2 = create_command_node("amxhdatag", DATATYPE_UNDEFINED);
            temp2->print_format = name_generator("endif", local_if_count);
            add_cmd_to_table(method, temp2);
            break;
        case NODETYPE_WHILE:
            loop_count += 1;
            local_loop_count = loop_count;
            temp2 = create_command_node("amxhdatag", DATATYPE_UNDEFINED);
            temp2->print_format = name_generator("loop", local_loop_count);
            add_cmd_to_table(method, temp2);
            temp = create_command_node("amxhdabne", DATATYPE_UNDEFINED);
            temp->print_format = name_generator("endloop", local_loop_count);
            temp->left = create_command_node_two_param("amxhdacmpcmp", -100, 1, DATATYPE_UNDEFINED);
            temp->left->left = checkExpOr(statement->children[0], method);
            temp->left->parameters[0] = temp->left->left->parameters[0];
            add_cmd_to_table(method, temp);
            checkStatement(statement->children[1], method); // if content
            temp3 = create_command_node("amxhdab", DATATYPE_UNDEFINED);
            temp3->print_format = name_generator("loop", local_loop_count);
            add_cmd_to_table(method, temp3);
            temp2 = create_command_node("amxhdatag", DATATYPE_UNDEFINED);
            temp2->print_format = name_generator("endloop", local_loop_count);
            add_cmd_to_table(method, temp2);
            break;
        case NODETYPE_PRINTLN:
            temp = checkExpOr(statement->children[0], method);
            if ((temp->type == DATATYPE_STR) || (temp->type == STR_LITERAL)) {
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                cmd_node *r0 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                cmd_node *r1 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                r0->print_format = malloc(11);
                strncpy(r0->print_format, "printlnStr", 10);
                r0->print_format[10] = '\0';
                r1->print_format = temp->cmd_name;
                r0->right = r1;
                print_node->left = r0;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == INT_LITERAL) {
                cmd_node *format = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                cmd_node *left = create_command_node_three_param("amxhdaldr", method->num_register++, -1, find_int_lit_offset(method, temp->parameters[0]), DATATYPE_UNDEFINED);
                format->print_format = malloc(11);
                strncpy(format->print_format, "printlnInt", 10);
                format->print_format[10] = '\0';
                left->left = temp;
                format->right = left;
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = format;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == METHODCALL) {
                cmd_node *format = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                if (temp->return_type == DATATYPE_INT) {
                    format->print_format = malloc(11);
                    strncpy(format->print_format, "printlnInt", 10);
                    format->print_format[10] = '\0';
                } else if (temp->return_type == DATATYPE_STR) {
                    format->print_format = malloc(11);
                    strncpy(format->print_format, "printlnStr", 10);
                    format->print_format[10] = '\0';
                }
                cmd_node *left = create_command_node_two_param("amxhdamovmov", 1, 0, DATATYPE_UNDEFINED);
                left->left = temp;
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = left;
                print_node->right = format;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == ARRAY) {
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                cmd_node *r0 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                r0->print_format = malloc(11);
                if (temp->array_type == DATATYPE_STR) {
                    strncpy(r0->print_format, "printlnStr", 10);
                } else {
                    strncpy(r0->print_format, "printlnInt", 10);
                }
                r0->print_format[10] = '\0';
                r0->right = create_command_node_three_param("amxhdaldrrrr", 1, 1, 0, DATATYPE_UNDEFINED);
                r0->right->right = temp;
                print_node->left = r0;
                add_cmd_to_table(method, print_node);
            } else {
                cmd_node *format = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                format->print_format = malloc(11);
                strncpy(format->print_format, "printlnInt", 10);
                format->print_format[10] = '\0';
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = format;
                print_node->right = temp;
                add_cmd_to_table(method, print_node);
            }
            break;
        case NODETYPE_PRINT:
            temp = checkExpOr(statement->children[0], method);
            if ((temp->type == DATATYPE_STR) || (temp->type == STR_LITERAL)) {
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                cmd_node *r0 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                cmd_node *r1 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                r0->print_format = malloc(9);
                strncpy(r0->print_format, "printStr", 8);
                r0->print_format[8] = '\0';
                r1->print_format = temp->cmd_name;
                r0->right = r1;
                print_node->left = r0;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == INT_LITERAL) {
                cmd_node *format = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                cmd_node *left = create_command_node_three_param("amxhdaldr", method->num_register++, -1, find_int_lit_offset(method, temp->parameters[0]), DATATYPE_UNDEFINED);
                format->print_format = malloc(9);
                strncpy(format->print_format, "printInt", 8);
                format->print_format[8] = '\0';
                left->left = temp;
                format->right = left;
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = format;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == METHODCALL) {
                cmd_node *format = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                if (temp->return_type == DATATYPE_INT) {
                    format->print_format = malloc(9);
                    strncpy(format->print_format, "printInt", 8);
                    format->print_format[8] = '\0';
                } else if (temp->return_type == DATATYPE_STR) {
                    format->print_format = malloc(9);
                    strncpy(format->print_format, "printStr", 8);
                    format->print_format[8] = '\0';
                }
                cmd_node *left = create_command_node_two_param("amxhdamovmov", 1, 0, DATATYPE_UNDEFINED);
                left->left = temp;
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = left;
                print_node->right = format;
                add_cmd_to_table(method, print_node);
            } else if (temp->type == ARRAY) {
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                cmd_node *r0 = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                r0->print_format = malloc(9);
                if (temp->array_type == DATATYPE_STR) {
                    strncpy(r0->print_format, "printStr", 8);
                } else {
                    strncpy(r0->print_format, "printInt", 8);
                }
                r0->print_format[8] = '\0';
                r0->right = create_command_node_three_param("amxhdaldrrrr", 1, 1, 0, DATATYPE_UNDEFINED);
                r0->right->right = temp;
                print_node->left = r0;
                add_cmd_to_table(method, print_node);
            } else {
                cmd_node *format = create_command_node_one_param("amxhdaldr", method->num_register++, PRINT);
                format->print_format = malloc(9);
                strncpy(format->print_format, "printInt", 8);
                format->print_format[8] = '\0';
                cmd_node *print_node = create_command_node("bl printf", DATATYPE_UNDEFINED);
                print_node->left = format;
                print_node->right = temp;
                add_cmd_to_table(method, print_node);
            }
            break;
        case NODETYPE_LEFTVALUE:
            temp = checkLeftValue(statement->children[0], method);
            temp2 = checkExpOr(statement->children[1], method);
            if (temp->type == ARRAY) {
                if (temp2->type == ARRAY) {

                } else if (temp2->type == METHODCALL) {

                } else {
                    temp3 = create_command_node_three_param("amxhdastrrrr", 2, 1, 0, METHODCALL);
                    temp3->right = create_command_node_three_param("amxhdaldr", 2, -1, find_int_lit_offset(method, temp2->parameters[0]), METHODCALL);
                    temp3->right->right = create_command_node_three_param("amxhdaldr", 0, -1, find_int_lit_offset(method, temp->left->parameters[0]), METHODCALL);
                    temp3->left = temp2;
                    temp3->left->left = temp;
                    add_cmd_to_table(method, temp3);
                    return;
                }
            }
            if (temp2->type == INT_LITERAL) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == STR_LITERAL) {
                // TODO
            } else if (temp2->type == BOOL_LITERAL) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == DATATYPE_INT) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == DATATYPE_STR) {
                // TODO
            } else if (temp2->type == DATATYPE_BOOLEAN) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == STATIC_INT) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == STATIC_BOOL) {
                temp3 = create_command_node_three_param("amxhdastr", temp2->parameters[0], -1, temp->parameters[2], DATATYPE_UNDEFINED);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            } else if (temp2->type == METHODCALL) {
                temp3 = create_command_node_three_param("amxhdastr", 0, -1, temp->parameters[2], METHODCALL);
                temp3->left = temp2;
                add_cmd_to_table(method, temp3);
            }
            break;
        case NODETYPE_RETURN:
            temp = checkExpOr(statement->children[0], method);
            if (temp->type == INT_LITERAL) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
                temp2->left = temp;
                add_cmd_to_table(method, temp2);
            } else if (temp->type == STR_LITERAL) {
                temp2 = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                temp2->print_format = temp->cmd_name;
                add_cmd_to_table(method, temp2);
                method->return_str = find_string(temp->cmd_name)->content;
            } else if (temp->type == BOOL_LITERAL) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
                temp2->left = temp;
                add_cmd_to_table(method, temp2);
            } else if (temp->type == DATATYPE_INT) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, -1, temp->parameters[2], METHODCALL);
                add_cmd_to_table(method, temp2);
            } else if (temp->type == DATATYPE_STR) {
                temp2 = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                temp2->print_format = temp->cmd_name;
                add_cmd_to_table(method, temp2);
                method->return_str = find_string(temp->cmd_name)->content;
            } else if (temp->type == DATATYPE_BOOLEAN) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, -1, temp->parameters[2], METHODCALL);
                add_cmd_to_table(method, temp2);
            } else if (temp->type == STATIC_INT) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, 0, 0, METHODCALL);
                temp2->left = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                temp2->left->print_format = temp->print_format;
                add_cmd_to_table(method, temp2);
            } else if (temp->type == STATIC_BOOL) {
                temp2 = create_command_node_three_param("amxhdaldr", 0, 0, 0, METHODCALL);
                temp2->left = create_command_node_one_param("amxhdaldr", 0, METHODCALL);
                temp2->left->print_format = temp->print_format;
                add_cmd_to_table(method, temp2);
            } else if (temp->type == METHODCALL) {
                add_cmd_to_table(method, temp);
            }
            cmd_node *ret = create_command_node("amxhdaret", RETURN);
            add_cmd_to_table(method, ret);
            break;
        case NODETYPE_METHODCALL:
            temp = checkMethodCall(statement->children[0], method);
            add_cmd_to_table(method, temp);
            break;
        default:
            return;
    }
}

void checkVarDecl(struct ASTNode *varDecl, method_scope *method) {
    char *name = varDecl->data.value.string_value;
    enum DataType type = checkType(varDecl->children[0]);
    cmd_node *temp = checkEqlExp(varDecl->children[1], method);
    cmd_node *assign = NULL;
    if (temp) {
        if (temp->type == DATATYPE_INT) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_INT);
        } else if ((temp->type == INT_LITERAL) || (temp->type == STATIC_INT)) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_INT);
            assign->left = temp;
        } else if (temp->type == DATATYPE_BOOLEAN) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_BOOLEAN);
        } else if ((temp->type == BOOL_LITERAL) || (temp->type == STATIC_BOOL)) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_BOOLEAN);
            assign->left = temp;
        } else if ((temp->type == STR_LITERAL) || (temp->type == DATATYPE_STR)) {
            add_string(name, find_string(temp->cmd_name)->content);
        } else if (temp->type == ARRAY) {
            add_local_var_with_offset(method, name, ARRAY, temp->parameters[2]);
            add_cmd_to_table(method, temp);
        } else if (temp->type == METHODCALL) {
            if (temp->return_type == DATATYPE_STR) {
                add_string(name, find_method(temp->cmd_name)->return_str);
            } else if (temp->return_type == ARRAY) {
                add_local_var(method, name, ARRAY);
                assign = create_command_node_three_param("amxhdastr", 0, -1, find_local_var(method, name)->offset, METHODCALL);
                assign->left = temp;
            } else if (temp->return_type == DATATYPE_INT) {
                assign = create_command_node_three_param("amxhdastr", 0, -1, method->total_bytes, METHODCALL);
                add_local_var(method, name, temp->return_type);
                assign->left = temp;
            } else {
                add_local_var(method, name, ARRAY);
                add_cmd_to_table(method, temp);
            }
        }
        if (assign) {
            add_cmd_to_table(method, assign);
        }
    }
    checkVarDeclTail(varDecl->children[2], method);
}
void checkVarDeclTail(struct ASTNode *varDeclTail, method_scope *method) {
    if (if_epsilon(varDeclTail)) return;
    checkVarDeclTail(varDeclTail->children[0], method);
    char *name = varDeclTail->data.value.string_value;
    cmd_node *temp = checkEqlExp(varDeclTail->children[1], method);
    cmd_node *assign = NULL;
    if (temp) {
        if (temp->type == DATATYPE_INT) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_INT);
        } else if ((temp->type == INT_LITERAL) || (temp->type == STATIC_INT)) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_INT);
            assign->left = temp;
        } else if (temp->type == DATATYPE_BOOLEAN) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_BOOLEAN);
        } else if ((temp->type == BOOL_LITERAL) || (temp->type == STATIC_BOOL)) {
            assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, DATATYPE_UNDEFINED);
            add_local_var(method, name, DATATYPE_BOOLEAN);
            assign->left = temp;
        } else if ((temp->type == STR_LITERAL) || (temp->type == DATATYPE_STR)) {
            add_string(name, find_string(temp->cmd_name)->content);
        } else if (temp->type == ARRAY) {
            add_local_var_with_offset(method, name, ARRAY, temp->parameters[2]);
            add_cmd_to_table(method, temp);
        } else if (temp->type == METHODCALL) {
            if (temp->return_type == DATATYPE_STR) {
                add_string(name, find_method(temp->cmd_name)->return_str);
            } else if (temp->return_type == ARRAY) {
                add_local_var(method, name, ARRAY);
                assign = create_command_node_three_param("amxhdastr", 0, -1, find_local_var(method, name)->offset, METHODCALL);
                assign->left = temp;
            } else if (temp->return_type == DATATYPE_INT) {
                assign = create_command_node_three_param("amxhdastr", temp->parameters[0], -1, method->total_bytes, METHODCALL);
                add_local_var(method, name, temp->return_type);
                assign->left = temp;
            } else {
                add_local_var(method, name, ARRAY);
                add_cmd_to_table(method, temp);
            }
        }
        if (assign) {
            add_cmd_to_table(method, assign);
        }
    }
}

cmd_node *checkMethodCall(struct ASTNode *methodCall, method_scope *method) {
    enum NodeType type = methodCall->node_type;
    if (type == NODETYPE_EXPLIST) {
        char *method_name = methodCall->data.value.string_value;
        method_scope *callee = find_method(method_name);
        cmd_node *method_call = create_command_node_one_param(method_name, method->num_register, METHODCALL);
        add_compiler_temp(method, method->num_register++);
        cmd_node *check = checkExpList(methodCall->children[0], method);
        cmd_node *temp, *temp2;
        temp2 = create_command_node_two_param("amxhdamovmov", 0, 5, METHODCALL);
        for (size_t i = 1; i < callee->num_param; i++) {
            temp = create_command_node_two_param("amxhdamovmov", callee->num_param - i, 9 - i, METHODCALL);
            temp->right = temp2;
            temp2 = temp;
        }
        method_call->left = check;
        method_call->right = temp2;
        method_call->return_type = callee->return_type;
        return method_call;
    } else if (type == NODETYPE_ID) {
        char *method_name = methodCall->data.value.string_value;
        method_scope *callee = find_method(method_name);
        cmd_node *method_call = create_command_node_one_param(method_name, 0, METHODCALL);
        method_call->return_type = callee->return_type;
        return method_call;
    } else if (type == NODETYPE_PARSEINT) {
        cmd_node *method_call = create_command_node_one_param("atoi", 0, METHODCALL);
        method_call->return_type = DATATYPE_INT;
        cmd_node *exp = checkExpOr(methodCall->children[0], method);
        if (exp->type != ARRAY) {
            cmd_node *load_exp = create_command_node_one_param("amxhdaldr", method->num_register++, DATATYPE_UNDEFINED);
            load_exp->print_format = exp->cmd_name;
            method_call->left = load_exp;
        } else {
            cmd_node *mov = create_command_node_two_param("amxhdamovmov", 0, 1, DATATYPE_UNDEFINED);
            method_call->left = exp;
            method_call->right = mov;
            mov->right = create_command_node_three_param("amxhdaldrrrr", 1, 1, 0, DATATYPE_UNDEFINED);
        }
        return method_call;
    }
}
cmd_node *checkExpList(struct ASTNode *expList, method_scope *method) {
    cmd_node *temp = checkExpOr(expList->children[0], method);
    cmd_node *arg2 = checkExpListTail(expList->children[1], method, 8);
    cmd_node *arg1;
    if (temp->type == DATATYPE_INT) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, -1, temp->parameters[2], METHODCALL);
    } else if (temp->type == DATATYPE_STR) {
        // TODO
    } else if (temp->type == DATATYPE_BOOLEAN) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, -1, temp->parameters[2], METHODCALL);
    } else if (temp->type == STATIC_INT) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, 5, 0, METHODCALL);
        arg1->right = create_command_node_one_param("amxhdaldr", 5, METHODCALL);
        arg1->right->print_format = temp->print_format;
    } else if (temp->type == STATIC_BOOL) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, 5, 0, METHODCALL);
        arg1->right = create_command_node_one_param("amxhdaldr", 5, METHODCALL);
        arg1->right->print_format = temp->print_format;
    } else if (temp->type == INT_LITERAL) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
        arg1->right = temp;
    } else if (temp->type == STR_LITERAL) {
        arg1 = create_command_node_one_param("amxhdaldr", 5, METHODCALL);
        arg1->print_format = temp->cmd_name;
    } else if (temp->type == BOOL_LITERAL) {
        arg1 = create_command_node_three_param("amxhdaldr", 5, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
        arg1->right = temp;
    } else if (temp->type == METHODCALL) {
        temp->left = arg2;
        return temp;
    }
    arg1->left = arg2;
    return arg1;
}
cmd_node *checkExpListTail(struct ASTNode *expListTail, method_scope *method, int reg) {
    if (if_epsilon(expListTail)) return NULL;
    cmd_node *arg = checkExpListTail(expListTail->children[0], method, reg - 1);
    cmd_node *temp = checkExpOr(expListTail->children[1], method);
    cmd_node *arg1, *arg2;
    if (temp->type == DATATYPE_INT) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, -1, temp->parameters[2], METHODCALL);
    } else if (temp->type == DATATYPE_STR) {
        // TODO
    } else if (temp->type == DATATYPE_BOOLEAN) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, -1, temp->parameters[2], METHODCALL);
    } else if (temp->type == STATIC_INT) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, reg, 0, METHODCALL);
        arg1->right = create_command_node_one_param("amxhdaldr", reg, METHODCALL);
        arg1->right->print_format = temp->print_format;
    } else if (temp->type == STATIC_BOOL) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, reg, 0, METHODCALL);
        arg1->right = create_command_node_one_param("amxhdaldr", reg, METHODCALL);
        arg1->right->print_format = temp->print_format;
    } else if (temp->type == INT_LITERAL) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
        arg1->right = temp;
    } else if (temp->type == STR_LITERAL) {
        arg1 = create_command_node_one_param("amxhdaldr", reg, METHODCALL);
        arg1->print_format = temp->cmd_name;
    } else if (temp->type == BOOL_LITERAL) {
        arg1 = create_command_node_three_param("amxhdaldr", reg, -1, find_int_lit_offset(method, temp->parameters[0]), METHODCALL);
        arg1->right = temp;
    } else if (temp->type == METHODCALL) {
        arg2 = create_command_node_two_param("amxhdamovmov", reg, 0, METHODCALL);
        arg2->left = arg;
        arg2->right = temp;
        return arg2;
    }

    arg1->left = arg;
    return arg1;
}

cmd_node *checkExpOr(struct ASTNode *expOr, method_scope *method) {
    enum NodeType nodeType = expOr->node_type;
    if (nodeType == NODETYPE_EXPOR) {
        cmd_node *temp = checkExpOr(expOr->children[0], method);
        cmd_node *temp2 = checkExpAnd(expOr->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_three_param("amxhdaorr", method->num_register, reg1, reg2, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->right->left = temp2;
            } else {
                result->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->right->left = temp2;
            } else {
                result->left = temp;
                result->right = temp2;
            }
        }
        return result;
    } else {
        return checkExpAnd(expOr->children[0], method);
    }
}
cmd_node *checkExpAnd(struct ASTNode *expAnd, method_scope *method) {
    enum NodeType nodeType = expAnd->node_type;
    if (nodeType == NODETYPE_EXPAND) {
        cmd_node *temp = checkExpAnd(expAnd->children[0], method);
        cmd_node *temp2 = checkExpEql(expAnd->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_three_param("amxhdaand", method->num_register, reg1, reg2, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->right->left = temp2;
            } else {
                result->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left = temp;
                result->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->right->left = temp2;
            } else {
                result->left = temp;
                result->right = temp2;
            }
        }
        return result;
    } else {
        return checkExpEql(expAnd->children[0], method);
    }
}
cmd_node *checkExpEql(struct ASTNode *expEql, method_scope *method) {
    enum NodeType nodeType = expEql->node_type;
    if (nodeType == NODETYPE_EXPEQL) {
        cmd_node *temp = checkExpEql(expEql->children[0], method);
        cmd_node *temp2 = checkExpIneql(expEql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamoveq", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else if (nodeType == NODETYPE_EXPNEQ) {
        cmd_node *temp = checkExpEql(expEql->children[0], method);
        cmd_node *temp2 = checkExpIneql(expEql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamovne", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else {
        return checkExpIneql(expEql->children[0], method);
    }
}
cmd_node *checkExpIneql(struct ASTNode *expIneql, method_scope *method) {
    enum NodeType nodeType = expIneql->node_type;
    if (nodeType == NODETYPE_EXPLES) {
        cmd_node *temp = checkExpIneql(expIneql->children[0], method);
        cmd_node *temp2 = checkExpPlusMinus(expIneql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamovlt", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else if (nodeType == NODETYPE_EXPGRT) {
        cmd_node *temp = checkExpIneql(expIneql->children[0], method);
        cmd_node *temp2 = checkExpPlusMinus(expIneql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamovgt", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else if (nodeType == NODETYPE_EXPLEQ) {
        cmd_node *temp = checkExpIneql(expIneql->children[0], method);
        cmd_node *temp2 = checkExpPlusMinus(expIneql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamovle", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else if (nodeType == NODETYPE_EXPGEQ) {
        cmd_node *temp = checkExpIneql(expIneql->children[0], method);
        cmd_node *temp2 = checkExpPlusMinus(expIneql->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *result = create_command_node_two_param("amxhdamovge", method->num_register, 1, BOOL_LITERAL);
        add_compiler_temp(method, method->num_register++);
        result->left = create_command_node_two_param("amxhdacmp", reg1, reg2, DATATYPE_UNDEFINED);
        result->right = create_command_node_two_param("amxhdamov", 0, 0, DATATYPE_UNDEFINED);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                result->left->right->left = temp2;
                result->left->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                //result->right->right = create_command_node_two_param("amxhdamovmov", 1, 4, DATATYPE_UNDEFINED);
            } else {
                result->left->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                result->left->left->left = temp;
                result->left->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                result->left->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                result->left->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                result->left->left = temp;
                result->left->right->right = temp2;
            } else {
                result->left->left = temp;
                result->left->right = temp2;
            }
        }
        return result;
    } else {
        return checkExpPlusMinus(expIneql->children[0], method);
    }
}
cmd_node *checkExpPlusMinus(struct ASTNode *expPM, method_scope *method) {
    enum NodeType nodeType = expPM->node_type;
    if (nodeType == NODETYPE_EXPPLUS) {
        cmd_node *temp = checkExpPlusMinus(expPM->children[0], method);
        cmd_node *temp2 = checkExpMulDiv(expPM->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        if ((temp->type == STR_LITERAL) || (temp->type == DATATYPE_STR)) {
            str_format *string1 = find_string(temp->cmd_name);
            str_format *string2 = find_string(temp2->cmd_name);
            char *result = malloc(strlen(string1->content) + strlen(string2->content) + 2);
            strncpy(result + 1, string1->content, strlen(string1->content));
            strncpy(result + strlen(string1->content) + 1, string2->content, strlen(string2->content));
            result[strlen(string1->content) + strlen(string2->content) + 1] = '\0';
            result[0] = '_';
            add_string(result, result + 1);
            return create_command_node(result, STR_LITERAL);
        }
        cmd_node *sum = create_command_node_three_param("amxhdaadd", method->num_register, reg1, reg2, INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                sum->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                sum->left->left = temp;
                sum->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                sum->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                sum->right->left = temp2;
            } else {
                sum->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                sum->left->left = temp;
                sum->right = create_command_node_two_param("amxhdamovmov", 0, 4, temp2->type);
                sum->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                sum->left = temp;
                sum->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                sum->right->left = temp2;
            } else {
                sum->left = temp;
                sum->right = temp2;
            }
        }
        return sum;
    } else if (nodeType == NODETYPE_EXPMINUS) {
        cmd_node *temp = checkExpPlusMinus(expPM->children[0], method);
        cmd_node *temp2 = checkExpMulDiv(expPM->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *diff = create_command_node_three_param("amxhdasub", method->num_register, reg1, reg2, INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                diff->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                diff->left->left = temp;
                diff->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                diff->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                diff->right->left = temp2;
            } else {
                diff->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                diff->left->left = temp;
                diff->right = create_command_node_two_param("amxhdamovmov", 0, 4, temp2->type);
                diff->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                diff->left = temp;
                diff->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                diff->right->left = temp2;
            } else {
                diff->left = temp;
                diff->right = temp2;
            }
        }
        return diff;
    } else {
        return checkExpMulDiv(expPM->children[0], method);
    }
}
cmd_node *checkExpMulDiv(struct ASTNode *expMD, method_scope *method) {
    enum NodeType nodeType = expMD->node_type;
    if (nodeType == NODETYPE_EXPMUL) {
        cmd_node *temp = checkExpMulDiv(expMD->children[0], method);
        cmd_node *temp2 = checkExpFactor(expMD->children[1], method);
        int reg1 = temp->parameters[0];
        int reg2 = temp2->parameters[0];
        cmd_node *product = create_command_node_three_param("amxhdamul", method->num_register, reg1, reg2, INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        if (temp->type == METHODCALL) {
            if (temp2->type == METHODCALL) {
                product->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                product->left->left = temp;
                product->right = create_command_node_two_param("amxhdamovmov", 0, 4, METHODCALL);
                product->right->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                product->right->left = temp2;
            } else {
                product->left = create_command_node_two_param("amxhdamovmov", 4, 0, METHODCALL);
                product->left->left = temp;
                product->right = create_command_node_two_param("amxhdamovmov", 0, 4, DATATYPE_UNDEFINED);
                product->right->right = temp2;
            }
        } else {
            if (temp2->type == METHODCALL) {
                product->left = temp;
                product->right = create_command_node_two_param("amxhdamovmov", 1, 0, METHODCALL);
                product->right->left = temp2;
            } else {
                product->left = temp;
                product->right = temp2;
            }
        }
        return product;
    } else if (nodeType == NODETYPE_EXPDIV) {
        cmd_node *temp = checkExpMulDiv(expMD->children[0], method);
        cmd_node *temp2 = checkExpFactor(expMD->children[1], method);
    } else {
        return checkExpFactor(expMD->children[0], method);
    }
}
cmd_node *checkExpFactor(struct ASTNode *expFactor, method_scope *method) {
    return checkFactor(expFactor->children[0], method);
}
cmd_node *checkFactor(struct ASTNode *factor, method_scope *method) {
    enum NodeType nodeType = factor->node_type;
    cmd_node *temp, *ret, *load_length;
    switch (nodeType) {
        case NODETYPE_NEG:
            ret = checkFactor(factor->children[0], method);
            temp = create_command_node_two_param("amxhdamvn", method->num_register, ret->parameters[0], BOOL_LITERAL);
            add_compiler_temp(method, method->num_register++);
            temp->left = ret;
            return temp;
            break;
        case NODETYPE_PLUS:
            return checkFactor(factor->children[0], method);
        case NODETYPE_MINUS:
            temp = checkFactor(factor->children[0], method);
            cmd_node* neg = create_command_node_two_param("amxhdaldr", method->num_register, -1, INT_LITERAL);
            add_compiler_temp(method, method->num_register++);
            cmd_node* result = create_command_node_three_param("amxhdamul", method->num_register, temp->parameters[0], neg->parameters[0], INT_LITERAL);
            add_compiler_temp(method, method->num_register++);
            result->left = temp;
            result->right = neg;
            return result;
        case NODETYPE_FACTORRECUR:
            return checkExpOr(factor->children[0], method);
        case NODETYPE_LEFTVALUE:
            return checkLeftValue(factor->children[0], method);
        case NODETYPE_LEFTVALUELENGTH:
            ret = checkLeftValue(factor->children[0], method);
            load_length = create_command_node_three_param("amxhdaldr", method->num_register, 1, 0, INT_LITERAL);
            add_compiler_temp(method, method->num_register++);
            load_length->return_type = ARRAY;
            load_length->right = ret;
            return load_length;
        case NODETYPE_INT:
            temp = create_command_node_two_param("amxhdaldr", method->num_register, factor->data.value.int_value, INT_LITERAL);
            add_compiler_temp(method, method->num_register++);
            return temp;
        case NODETYPE_STR:
            factor->data.value.string_value[strlen(factor->data.value.string_value) - 1] = '\0';
            factor->data.value.string_value[0] = '_';
            add_string(factor->data.value.string_value, factor->data.value.string_value + 1);
            return create_command_node(factor->data.value.string_value, STR_LITERAL);
        case NODETYPE_TRUE:
            temp = create_command_node_two_param("amxhdaldr", method->num_register, 1, BOOL_LITERAL);
            add_compiler_temp(method, method->num_register++);
            return temp;
        case NODETYPE_FALSE:
            temp = create_command_node_two_param("amxhdaldr", method->num_register, 0, BOOL_LITERAL);
            add_compiler_temp(method, method->num_register++);
            return temp;
        case NODETYPE_METHODCALL:
            return checkMethodCall(factor->children[0], method);
        case NODETYPE_NEW:
            return checkIndex(factor->children[1], method);
        default:
            return NULL;
    }
    return NULL;
}

cmd_node *checkIndex(struct ASTNode *index, method_scope *method) {
    enum NodeType nodeType = index->node_type;
    if (nodeType == NODETYPE_INDEXRECUR) {
        /*expression type_dim1 = checkIndex(index->children[0], tree_node, dim + 1);
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
        return type_dim1;*/
    } else if (nodeType == NODETYPE_INDEX) {
        cmd_node *exp = checkExpOr(index->children[0], method);
        cmd_node *load_exp = create_command_node_three_param("amxhdaldr", exp->parameters[0], -1, find_int_lit_offset(method, exp->parameters[0]), DATATYPE_UNDEFINED);
        cmd_node *load_one = create_command_node_two_param("amxhdaldr", method->num_register, 1, DATATYPE_UNDEFINED);
        add_compiler_temp(method, method->num_register++);
        cmd_node *add_one = create_command_node_three_param("amxhdaadd", method->num_register, load_exp->parameters[0], load_one->parameters[0], INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        cmd_node *load_add = create_command_node_three_param("amxhdaldr", add_one->parameters[0], -1, find_int_lit_offset(method, add_one->parameters[0]), DATATYPE_UNDEFINED);
        cmd_node *load_four = create_command_node_two_param("amxhdaldr", method->num_register, 4, DATATYPE_UNDEFINED);
        add_compiler_temp(method, method->num_register++);
        cmd_node *mul_four = create_command_node_three_param("amxhdamul", method->num_register, load_add->parameters[0], load_four->parameters[0], INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        cmd_node *load_mul = create_command_node_three_param("amxhdaldr", mul_four->parameters[0], -1, find_int_lit_offset(method, mul_four->parameters[0]), DATATYPE_UNDEFINED);
        cmd_node *malloc = create_command_node("malloc", METHODCALL);
        cmd_node *store_malloc = create_command_node_three_param("amxhdastr", 0, -1, method->total_bytes, METHODCALL);
        cmd_node *load_array = create_command_node_three_param("amxhdaldr", 0, -1, method->total_bytes, METHODCALL);
        cmd_node *load_length = create_command_node_three_param("amxhdaldr", 1, -1, find_int_lit_offset(method, exp->parameters[0]), METHODCALL);
        cmd_node *store_length = create_command_node_three_param("amxhdastr", 1, 0, 0, METHODCALL);
        //store_length->return_type = ARRAY;
        load_add->left = exp;
        load_add->right = add_one;
        add_one->left = load_exp;
        add_one->right = load_one;
        load_mul->left = mul_four;
        mul_four->left = load_add;
        mul_four->right = load_four;
        store_length->left = load_mul;
        store_length->right = load_length;
        load_length->left = store_malloc;
        load_length->right = load_array;
        store_malloc->left = malloc;
        return store_length;
    }
}
cmd_node *checkLeftValue(struct ASTNode *leftValue, method_scope *method) {
    enum NodeType type = leftValue->node_type;
    if (type == NODETYPE_LEFTVALUE) {
        char *name = leftValue->data.value.string_value;
        local_var *found = find_local_var(method, name);
        if (found) {
            if (found->type == DATATYPE_INT) {
                add_compiler_temp_with_offset(method, method->num_register, found->offset);
                return create_command_node_three_param("amxhdaldr", method->num_register++, -1, found->offset, DATATYPE_INT);
            } else if (found->type == DATATYPE_BOOLEAN) {
                add_compiler_temp_with_offset(method, method->num_register, found->offset);
                return create_command_node_three_param("amxhdaldr", method->num_register++, -1, found->offset, DATATYPE_BOOLEAN);
            } else if (found->type == DATATYPE_STR) {
                return create_command_node_three_param("amxhdaldr", method->num_register++, -1, found->offset, DATATYPE_STR);
            } else {
                cmd_node *temp = create_command_node_three_param("serdhtfjgyvhuegsrj", method->num_register++, -1, found->offset, ARRAY);
                temp->array_type = found->array_type;
                return temp;
            }
        }
        static_int *static_int_found = find_static_int(name);
        if (static_int_found) {
            cmd_node *temp = create_command_node_one_param("amxhdaldr", method->num_register++, STATIC_INT);
            temp->print_format = name;
            return temp;
        }
        str_format *find_str = find_string(name);
        if (find_str) {
            return create_command_node(find_str->name, DATATYPE_STR);
        }
        static_int *static_bool_found = find_static_bool(name);
        if (static_bool_found) {
            cmd_node *temp = create_command_node_one_param("amxhdaldr", method->num_register++, STATIC_BOOL);
            temp->print_format = name;
            return temp;
        }
    } else if (type == NODETYPE_LEFTVALUERECUR) {
        cmd_node *recur = checkLeftValue(leftValue->children[0], method);
        cmd_node *temp = checkExpOr(leftValue->children[1], method);
        cmd_node *load_exp;
        if (temp->type == ARRAY) {
            load_exp = create_command_node_three_param("amxhdaldr", temp->parameters[0], -1, temp->right->parameters[2], ARRAY);
        } else {
            load_exp = create_command_node_three_param("amxhdaldr", temp->parameters[0], -1, find_int_lit_offset(method, temp->parameters[0]), DATATYPE_UNDEFINED);
        }
        cmd_node *load_one = create_command_node_two_param("amxhdaldr", method->num_register, 1, DATATYPE_UNDEFINED);
        add_compiler_temp(method, method->num_register++);
        cmd_node *add_one = create_command_node_three_param("amxhdaadd", method->num_register, load_exp->parameters[0], load_one->parameters[0], INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        cmd_node *load_add = create_command_node_three_param("amxhdaldr", add_one->parameters[0], -1, find_int_lit_offset(method, add_one->parameters[0]), DATATYPE_UNDEFINED);
        cmd_node *load_four = create_command_node_two_param("amxhdaldr", method->num_register, 4, DATATYPE_UNDEFINED);
        add_compiler_temp(method, method->num_register++);
        cmd_node *mul_four = create_command_node_three_param("amxhdamul", method->num_register, load_add->parameters[0], load_four->parameters[0], INT_LITERAL);
        add_compiler_temp(method, method->num_register++);
        cmd_node *load_mul = create_command_node_three_param("amxhdaldr", mul_four->parameters[0], -1, find_int_lit_offset(method, mul_four->parameters[0]), DATATYPE_UNDEFINED);
        cmd_node *root = create_command_node_three_param("fasjieflesj", 1, 1, 0, ARRAY);
        root->array_type = recur->array_type;
        cmd_node *load_array = create_command_node_three_param("amxhdaldr", 1, recur->parameters[1], recur->parameters[2], DATATYPE_UNDEFINED);
        load_add->left = temp;
        load_add->right = add_one;
        add_one->left = load_exp;
        add_one->right = load_one;
        load_mul->left = mul_four;
        mul_four->left = load_add;
        mul_four->right = load_four;
        root->left = load_mul;
        root->right = load_array;
        return root;
    }
}

/* ---------------------------Helper functions--------------------------- */

bool if_epsilon(struct ASTNode *node) {
    if (node->num_children == 0) return true;
    return false;
}
char *name_generator(char *name, int count) {
    char *result = NULL;
    if (strcmp(name, "if") == 0) {
        if (count == 58) { count = 65; if_count = 65; }
        if (count == 91) { count = 97; if_count = 97; }
        result = malloc(strlen(name) + 2);
        strncpy(result, name, strlen(name));
        result[strlen(name)] = count;
        result[strlen(name) + 1] = '\0';
    } else if (strcmp(name, "loop") == 0) {
        if (count == 58) { count = 65; loop_count = 65; }
        if (count == 91) { count = 97; loop_count = 97; }
        result = malloc(strlen(name) + 2);
        strncpy(result, name, strlen(name));
        result[strlen(name)] = count;
        result[strlen(name) + 1] = '\0';
    } else if (strcmp(name, "endif") == 0) {
        result = malloc(strlen(name) + 2);
        strncpy(result, name, strlen(name));
        result[strlen(name)] = count;
        result[strlen(name) + 1] = '\0';
    } else if (strcmp(name, "endloop") == 0) {
        result = malloc(strlen(name) + 2);
        strncpy(result, name, strlen(name));
        result[strlen(name)] = count;
        result[strlen(name) + 1] = '\0';
    }
    return result;
}

method_scope *create_method_scope(char *name) {
    method_scope *new_method = malloc(sizeof(method_scope));
    new_method->method_name = malloc(strlen(name) + 1);
    strncpy(new_method->method_name, name, strlen(name));
    new_method->method_name[strlen(name)] = '\0';
    return new_method;
}
cmd_node *create_command_node(char *cmd_name, enum DataType type) {
    cmd_node *new_node = malloc(sizeof(cmd_node));
    new_node->cmd_name = malloc(strlen(cmd_name) + 1);
    strncpy(new_node->cmd_name, cmd_name, strlen(cmd_name));
    new_node->cmd_name[strlen(cmd_name)] = '\0';
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
cmd_node *create_command_node_one_param(char *cmd_name, int param1, enum DataType type) {
    cmd_node *new_node = malloc(sizeof(cmd_node));
    new_node->cmd_name = malloc(strlen(cmd_name) + 1);
    strncpy(new_node->cmd_name, cmd_name, strlen(cmd_name));
    new_node->cmd_name[strlen(cmd_name)] = '\0';
    new_node->parameters[0] = param1;
    new_node->num_param = 1;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
cmd_node *create_command_node_two_param(char *cmd_name, int param1, int param2, enum DataType type) {
    cmd_node *new_node = malloc(sizeof(cmd_node));
    new_node->cmd_name = malloc(strlen(cmd_name) + 1);
    strncpy(new_node->cmd_name, cmd_name, strlen(cmd_name));
    new_node->cmd_name[strlen(cmd_name)] = '\0';
    new_node->num_param = 2;
    new_node->parameters[0] = param1;
    new_node->parameters[1] = param2;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
cmd_node *create_command_node_three_param(char *cmd_name, int param1, int param2, int param3, enum DataType type) {
    cmd_node *new_node = malloc(sizeof(cmd_node));
    new_node->cmd_name = malloc(strlen(cmd_name) + 1);
    strncpy(new_node->cmd_name, cmd_name, strlen(cmd_name));
    new_node->cmd_name[strlen(cmd_name)] = '\0';
    new_node->num_param = 3;
    new_node->parameters[0] = param1;
    new_node->parameters[1] = param2;
    new_node->parameters[2] = param3;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void add_method(method_scope *method) {
    methods[num_methods] = method;
    num_methods += 1;
}
void add_cmd_to_table(method_scope *method, cmd_node *node) {
    method->cmd_table[method->num_commands] = node;
    method->num_commands += 1;
}
void add_local_var(method_scope *method, char* id, enum DataType type) {
    local_var *entry = malloc(sizeof(local_var));
    entry->id = id;
    entry->offset = method->total_bytes;
    entry->type = type;
    method->total_bytes += 4;
    method->local_vars[method->num_local_vars] = entry;
    method->num_local_vars += 1;
}
void add_local_var_with_offset(method_scope *method, char* id, enum DataType type, int offset) {
    local_var *entry = malloc(sizeof(local_var));
    entry->id = id;
    entry->offset = offset;
    entry->type = type;
    method->local_vars[method->num_local_vars] = entry;
    method->num_local_vars += 1;
}
void add_compiler_temp(method_scope *method, int reg) {
    compiler_temp *entry = malloc(sizeof(compiler_temp));
    entry->reg = reg;
    entry->offset = method->total_bytes;
    method->intermediate_vars[method->num_intermediate_vars] = entry;
    method->num_intermediate_vars += 1;
    method->total_bytes += 4;
}
void add_compiler_temp_with_offset(method_scope *method, int reg, int offset) {
    compiler_temp *entry = malloc(sizeof(compiler_temp));
    entry->reg = reg;
    entry->offset = offset;
    method->intermediate_vars[method->num_intermediate_vars] = entry;
    method->num_intermediate_vars += 1;
}
void add_static_int(char *name, int value) {
    static_int *node = malloc(sizeof(static_int));
    node->name = malloc(strlen(name) + 1);
    strncpy(node->name, name, strlen(name));
    node->name[strlen(name)] = '\0';
    node->value = value;
    static_ints[num_static_int] = node;
    num_static_int += 1;
}
void add_string(char *name, char *content) {
    str_format *node = malloc(sizeof(str_format));
    node->content = malloc(strlen(content) + 1);
    strncpy(node->content, content, strlen(content));
    node->content[strlen(content)] = '\0';
    node->name = name;
    for (size_t i = 1; i < strlen(name); i++) {
        if (name[i] < 47) {
            name[i] = '_';
        } else if (name[i] > 122) {
            name[i] = '_';
        } else if ((name[i] > 57) && (name[i] < 65)) {
            name[i] = '_';
        } else if ((name[i] > 90) && (name[i] < 97)) {
            name[i] = '_';
        }
    }
    strings[num_strings] = node;
    num_strings += 1;
}
void add_static_bool(char *name, int value) {
    static_int *node = malloc(sizeof(static_int));
    node->name = malloc(strlen(name) + 1);
    strncpy(node->name, name, strlen(name));
    node->name[strlen(name)] = '\0';
    node->value = value;
    static_bools[num_static_bool] = node;
    num_static_bool += 1;
}

method_scope *find_method(char *name) {
    for (size_t i = 0; i < num_methods; i++) {
        if (strcmp(methods[i]->method_name, name) == 0) {
            return methods[i];
        }
    }
    return NULL;
}
local_var *find_local_var(method_scope *method, char* id) {
    for (int i = 0; i < method->num_local_vars; i++) {
        if(strcmp(id, method->local_vars[i]->id) == 0){
            return method->local_vars[i];
        }
    }
    return NULL;
}
int find_int_lit_offset(method_scope *method, int reg) {
    for (int i = 0; i < method->num_intermediate_vars; i++) {
        if(method->intermediate_vars[i]->reg == reg){
            return method->intermediate_vars[i]->offset;
        }
    }
    return -100;
}
static_int *find_static_int(char *id) {
    for (size_t i = 0; i < num_static_int; i++) {
        if (strcmp(id, static_ints[i]->name) == 0) {
            return static_ints[i];
        }
    }
    return NULL;
}
str_format *find_string(char *id) {
    for (size_t i = 0; i < num_strings; i++) {
        if (strcmp(id, strings[i]->name) == 0) {
            return strings[i];
        }
    }
    return NULL;
}
static_int *find_static_bool(char *id) {
    for (size_t i = 0; i < num_static_bool; i++) {
        if (strcmp(id, static_bools[i]->name) == 0) {
            return static_bools[i];
        }
    }
    return NULL;
}
