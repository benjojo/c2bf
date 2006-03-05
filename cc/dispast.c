/*
 * Copyright (c) 2006  Gregor Richards
 * 
 * This file is part of C2BF.
 * 
 * C2BF is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * C2BF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with C2BF; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>

#include "ast.h"

int dispay_space_iterator;
#define SPC \
for (dispay_space_iterator = 0; \
     dispay_space_iterator < spc; \
     dispay_space_iterator++) putchar('|')
#define SSPC \
for (dispay_space_iterator = 1; \
     dispay_space_iterator < spc; \
     dispay_space_iterator++) putchar('|')

void disp_abstract_declarator(int spc, struct abstract_declarator *a)
{
    SSPC; printf("-abstract_declarator\n");
    if (a->has_pointer) {
        disp_pointer(spc+1, a->v1);
    }
    if (a->has_abstract_declarator2) {
        disp_abstract_declarator2(spc+1, a->v2);
    }
}

void disp_abstract_declarator2(int spc, struct abstract_declarator2 *a)
{
    SSPC; printf("-abstract_declarator2\n");
    if (a->type == _ABSTRACT_DECLARATOR) {
        SPC; printf("(\n");
        disp_abstract_declarator(spc+1, a->v1._abstract_declarator);
        SPC; printf(")\n");
        return;
    }
    
    if (!a->end) {
        disp_abstract_declarator2(spc+1, a->v1._abstract_declarator2);
    }
    
    switch (a->type) {
        case _SIMPLE_ARRAY:
            SPC; printf("[]\n");
            break;
            
        case _ARRAY:
            SPC; printf("[\n");
            disp_conditional_expr(spc+1, a->v2._conditional_expr);
            SPC; printf("]\n");
            break;
            
        case _SIMPLE_FUNC:
            SPC; printf("()\n");
            break;
            
        case _FUNC_BY_TYPE:
            SPC; printf("(\n");
            disp_parameter_type_list(spc+1, a->v2._parameter_type_list);
            SPC; printf(")\n");
            break;
    }
}

void disp_additive_expr(int spc, struct additive_expr *a)
{
    SSPC; printf("-additive_expr\n");
    switch (a->type) {
        case _MULTIPLICATIVE_EXPR:
            disp_multiplicative_expr(spc+1, a->v1._multiplicative_expr);
            break;
            
        case _ADD:
            disp_additive_expr(spc+1, a->v1._additive_expr);
            SPC; printf("+\n");
            disp_multiplicative_expr(spc+1, a->v2);
            break;
            
        case _SUBTRACT:
            disp_additive_expr(spc+1, a->v1._additive_expr);
            SPC; printf("-\n");
            disp_multiplicative_expr(spc+1, a->v2);
            break;
    }
}

void disp_and_expr(int spc, struct and_expr *a)
{
    SSPC; printf("-and_expr\n");
    if (!a->end) {
        disp_and_expr(spc+1, a->v1);
        SPC; printf("&\n");
    }
    disp_equality_expr(spc+1, a->v2);
}

void disp_argument_expr_list(int spc, struct argument_expr_list *a)
{
    SSPC; printf("-argument_expr_list\n");
    if (!a->end) {
        disp_argument_expr_list(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_assignment_expr(spc+1, a->v2);
}

void disp_assignment_expr(int spc, struct assignment_expr *a)
{
    SSPC; printf("-assignment_expr\n");
    switch (a->type) {
        case _CONDITIONAL_EXPR:
            disp_conditional_expr(spc+1, a->v1._conditional_expr);
            break;
            
        case _ASSIGNMENT:
            disp_unary_expr(spc+1, a->v1._unary_expr);
            disp_assignment_operator(spc+1, a->v2);
            disp_assignment_expr(spc+1, a->v3);
            break;
    }
}

void disp_assignment_operator(int spc, struct assignment_operator *a)
{
    SSPC; printf("-assignment_operator\n");
    switch (a->type) {
        case _ASSIGN:
            SPC; printf("=\n");
            break;
            
        case _MUL_ASSIGN:
            SPC; printf("*=\n");
            break;
            
        case _DIV_ASSIGN:
            SPC; printf("/=\n");
            break;
            
        case _MOD_ASSIGN:
            SPC; printf("%=\n");
            break;
            
        case _ADD_ASSIGN:
            SPC; printf("+=\n");
            break;
            
        case _SUB_ASSIGN:
            SPC; printf("-=\n");
            break;
            
        case _LEFT_ASSIGN:
            SPC; printf("<<=\n");
            break;
            
        case _RIGHT_ASSIGN:
            SPC; printf(">>=\n");
            break;
            
        case _AND_ASSIGN:
            SPC; printf("&=\n");
            break;
            
        case _XOR_ASSIGN:
            SPC; printf("^=\n");
            break;
            
        case _OR_ASSIGN:
            SPC; printf("|=\n");
            break;
    }
}

void disp_cast_expr(int spc, struct cast_expr *a)
{
    SSPC; printf("-cast_expr\n");
    switch (a->type) {
        case _UNARY_EXPR:
            disp_unary_expr(spc+1, a->v1._unary_expr);
            break;
            
        case _TYPE_CAST:
            SPC; printf("(\n");
            disp_type_name(spc+1, a->v1._type_name);
            SPC; printf(")\n");
            disp_cast_expr(spc+1, a->v2);
            break;
    }
}

void disp_compound_statement(int spc, struct compound_statement *a)
{
    SSPC; printf("-compound_statement\n");
    SPC; printf("{\n");
    if (a->has_declaration_list) {
        disp_declaration_list(spc+1, a->v1);
    }
    if (a->has_statement_list) {
        disp_statement_list(spc+1, a->v2);
    }
    SPC; printf("}\n");
}

void disp_conditional_expr(int spc, struct conditional_expr *a)
{
    SSPC; printf("-conditional_expr\n");
    disp_logical_or_expr(spc+1, a->v1);
    if (!a->end) {
        SPC; printf("?\n");
        disp_logical_or_expr(spc+1, a->v2);
        SPC; printf(":\n");
        disp_conditional_expr(spc+1, a->v3);
    }
}

void disp_declaration(int spc, struct declaration *a)
{
    SSPC; printf("-declaration\n");
    disp_declaration_specifiers(spc+1, a->v1);
    if (a->has_init_declarator_list) {
        disp_init_declarator_list(spc+1, a->v2);
    }
}

void disp_declaration_list(int spc, struct declaration_list *a)
{
    SSPC; printf("-declaration_list\n");
    if (!a->end) {
        disp_declaration_list(spc+1, a->v1);
    }
    disp_declaration(spc+1, a->v2);
}

void disp_declaration_specifiers(int spc, struct declaration_specifiers *a)
{
    SSPC; printf("-declaration_specifiers\n");
    switch (a->type) {
        case _STORAGE_CLASS_SPECIFIER:
            disp_storage_class_specifier(spc+1, a->v1._storage_class_specifier);
            break;
            
        case _TYPE_SPECIFIER:
            disp_type_specifier(spc+1, a->v1._type_specifier);
            break;
    }
    if (!a->end) {
        disp_declaration_specifiers(spc+1, a->v2);
    }
}

void disp_declarator(int spc, struct declarator *a)
{
    SSPC; printf("-declarator\n");
    if (a->pointer) {
        disp_pointer(spc+1, a->v1);
    }
    disp_declarator2(spc+1, a->v2);
}

void disp_declarator2(int spc, struct declarator2 *a)
{
    SSPC; printf("-declarator2\n");
    switch (a->type) {
        case _IDENTIFIER:
            disp_identifier(spc+1, a->v1._identifier);
            break;
            
        case _DECLARATOR:
            SPC; printf("(\n");
            disp_declarator(spc+1, a->v1._declarator);
            SPC; printf(")\n");
            break;
            
        case _SIMPLE_ARRAY:
            disp_declarator2(spc+1, a->v1._declarator2);
            SPC; printf("[]\n");
            break;
            
        case _ARRAY:
            disp_declarator2(spc+1, a->v1._declarator2);
            SPC; printf("[\n");
            disp_conditional_expr(spc+1, a->v2._conditional_expr);
            SPC; printf("]\n");
            break;
            
        case _SIMPLE_FUNC:
            disp_declarator2(spc+1, a->v1._declarator2);
            SPC; printf("()\n");
            break;
            
        case _FUNC_BY_TYPE:
            disp_declarator2(spc+1, a->v1._declarator2);
            SPC; printf("(\n");
            disp_parameter_type_list(spc+1, a->v2._parameter_type_list);
            SPC; printf(")\n");
            break;
            
        case _FUNC_OLD_STYLE:
            disp_declarator2(spc+1, a->v1._declarator2);
            SPC; printf("(\n");
            disp_parameter_identifier_list(spc+1, a->v2._parameter_identifier_list);
            SPC; printf(")\n");
            break;
    }
}

void disp_enum_specifier(int spc, struct enum_specifier *a)
{
    SSPC; printf("-enum_specifier\n");
    if (a->has_identifier) {
        disp_identifier(spc+1, a->v1);
    }
    if (a->has_enumerator_list) {
        SPC; printf("{\n");
        disp_enumerator_list(spc+1, a->v2);
        SPC; printf("}\n");
    }
}

void disp_enumerator(int spc, struct enumerator *a)
{
    SSPC; printf("-enumerator\n");
    disp_identifier(spc+1, a->v1);
    if (a->assign) {
        SPC; printf("=\n");
        disp_conditional_expr(spc+1, a->v2);
    }
}

void disp_enumerator_list(int spc, struct enumerator_list *a)
{
    SSPC; printf("-enumerator_list\n");
    if (!a->end) {
        disp_enumerator_list(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_enumerator(spc+1, a->v2);
}

void disp_equality_expr(int spc, struct equality_expr *a)
{
    SSPC; printf("-equality_expr\n");
    switch (a->type) {
        case _RELATIONAL_EXPR:
            disp_relational_expr(spc+1, a->v1._relational_expr);
            break;
            
        case _EQUAL:
            disp_equality_expr(spc+1, a->v1._equality_expr);
            SPC; printf("==\n");
            disp_relational_expr(spc+1, a->v2);
            break;
            
        case _NEQUAL:
            disp_equality_expr(spc+1, a->v1._equality_expr);
            SPC; printf("!=\n");
            disp_relational_expr(spc+1, a->v2);
            break;
    }
}

void disp_exclusive_or_expr(int spc, struct exclusive_or_expr *a)
{
    SSPC; printf("-exclusive_or_expr\n");
    if (!a->end) {
        disp_exclusive_or_expr(spc+1, a->v1);
        SPC; printf("^\n");
    }
    disp_and_expr(spc+1, a->v2);
}

void disp_expr(int spc, struct expr *a)
{
    SSPC; printf("-expr\n");
    if (!a->end) {
        disp_expr(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_assignment_expr(spc+1, a->v2);
}

void disp_expression_statement(int spc, struct expression_statement *a)
{
    SSPC; printf("-expression_statement\n");
    if (a->has_expr) {
        disp_expr(spc+1, a->v);
    }
    SPC; printf(";\n");
}

void disp_external_definition(int spc, struct external_definition *a)
{
    SSPC; printf("-external_definition\n");
    switch (a->type) {
        case _FUNCTION_DEFINITION:
            disp_function_definition(spc+1, a->v._function_definition);
            break;
            
        case _DECLARATION:
            disp_declaration(spc+1, a->v._declaration);
            break;
    }
}

void disp_external_definition_list(int spc, struct external_definition_list *a)
{
    SSPC; printf("-external_definition_list\n");
    if (!a->end) {
        disp_external_definition_list(spc+1, a->v1);
    }
    disp_external_definition(spc+1, a->v2);
}

void disp_file(int spc, struct file *a)
{
    SSPC; printf("-file\n");
    disp_external_definition_list(spc+1, a->v);
}

void disp_function_body(int spc, struct function_body *a)
{
    SSPC; printf("-function_body\n");
    if (a->has_declaration_list) {
        disp_declaration_list(spc+1, a->v1);
    }
    disp_compound_statement(spc+1, a->v2);
}

void disp_function_definition(int spc, struct function_definition *a)
{
    SSPC; printf("-function_definition\n");
    if (a->has_declaration_specifiers) {
        disp_declaration_specifiers(spc+1, a->v1);
    }
    disp_declarator(spc+1, a->v2);
    disp_function_body(spc+1, a->v3);
}

void disp_identifier(int spc, struct identifier *a)
{
    SSPC; printf("-identifier\n");
    SPC; printf("IDENTIFIER: %s\n", a->v);
}

void disp_identifier_list(int spc, struct identifier_list *a)
{
    SSPC; printf("-identifier_list\n");
    if (!a->end) {
        disp_identifier_list(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_identifier(spc+1, a->v2);
}

void disp_inclusive_or_expr(int spc, struct inclusive_or_expr *a)
{
    SSPC; printf("-inclusive_or_expr\n");
    if (!a->end) {
        disp_inclusive_or_expr(spc+1, a->v1);
        SPC; printf("|\n");
    }
    disp_exclusive_or_expr(spc+1, a->v2);
}

void disp_init_declarator(int spc, struct init_declarator *a)
{
    SSPC; printf("-init_declarator\n");
    disp_declarator(spc+1, a->v1);
    if (a->assign) {
        SPC; printf("=\n");
        disp_initializer(spc+1, a->v2);
    }
}

void disp_init_declarator_list(int spc, struct init_declarator_list *a)
{
    SSPC; printf("-init_declarator_list\n");
    if (!a->end) {
        disp_init_declarator_list(spc+1, a->v1);
    }
    disp_init_declarator(spc+1, a->v2);
}

void disp_initializer(int spc, struct initializer *a)
{
    SSPC; printf("-initializer\n");
    switch (a->type) {
        case _ASSIGNMENT_EXPR:
            disp_assignment_expr(spc+1, a->v._assignment_expr);
            break;
            
        case _INITIALIZER_LIST:
            SPC; printf("{\n");
            disp_initializer_list(spc+1, a->v._initializer_list);
            SPC; printf("}\n");
            break;
    }
}

void disp_initializer_list(int spc, struct initializer_list *a)
{
    SSPC; printf("-initializer_list\n");
    if (!a->end) {
        disp_initializer_list(spc+1, a->v1);
        printf(",\n");
    }
    disp_initializer(spc+1, a->v2);
}

void disp_iteration_statement(int spc, struct iteration_statement *a)
{
    SSPC; printf("-iteration_statement\n");
    switch (a->type) {
        case _WHILE:
            SPC; printf("while (\n");
            disp_expr(spc+1, a->v1);
            SPC; printf(")\n");
            disp_statement(spc+1, a->v4);
            break;
            
        case _DO_WHILE:
            SPC; printf("do\n");
            disp_statement(spc+1, a->v4);
            SPC; printf("while (\n");
            disp_expr(spc+1, a->v1);
            SPC; printf(");\n");
            break;
            
        case _FOR:
            SPC; printf("for (\n");
            if (a->has_initializer) {
                disp_expr(spc+1, a->v1);
            }
            SPC; printf(";\n");
            if (a->has_condition) {
                disp_expr(spc+1, a->v2);
            }
            SPC; printf(";\n");
            if (a->has_post) {
                disp_expr(spc+1, a->v3);
            }
            SPC; printf(")\n");
            disp_statement(spc+1, a->v4);
            break;
    }
}

void disp_jump_statement(int spc, struct jump_statement *a)
{
    SSPC; printf("-jump_statement\n");
    switch (a->type) {
        case _GOTO:
            SPC; printf("goto\n");
            disp_identifier(spc+1, a->v._identifier);
            SPC; printf(";\n");
            break;
            
        case _CONTINUE:
            SPC; printf("continue;\n");
            break;
            
        case _BREAK:
            SPC; printf("break;\n");
            break;
            
        case _RETURN:
            SPC; printf("return\n");
            if (a->has_expr) {
                disp_expr(spc+1, a->v._expr);
            }
            SPC; printf(";\n");
            break;
    }
}

void disp_labeled_statement(int spc, struct labeled_statement *a)
{
    SSPC; printf("-labeled_statement\n");
    switch (a->type) {
        case _LABEL:
            disp_identifier(spc+1, a->v1._identifier);
            SPC; printf(":\n");
            disp_statement(spc+1, a->v2);
            break;
            
        case _CASE:
            SPC; printf("case\n");
            disp_conditional_expr(spc+1, a->v1._conditional_expr);
            SPC; printf(":\n");
            disp_statement(spc+1, a->v2);
            break;
            
        case _DEFAULT:
            SPC; printf("default:\n");
            disp_statement(spc+1, a->v2);
            break;
    }
}

void disp_logical_and_expr(int spc, struct logical_and_expr *a)
{
    SSPC; printf("-logical_and_expr\n");
    if (!a->end) {
        disp_logical_and_expr(spc+1, a->v1);
        SPC; printf("&&\n");
    }
    disp_inclusive_or_expr(spc+1, a->v2);
}

void disp_logical_or_expr(int spc, struct logical_or_expr *a)
{
    SSPC; printf("-logical_or_expr\n");
    if (!a->end) {
        disp_logical_or_expr(spc+1, a->v1);
        SPC; printf("||\n");
    }
    disp_logical_and_expr(spc+1, a->v2);
}

void disp_multiplicative_expr(int spc, struct multiplicative_expr *a)
{
    SSPC; printf("-multiplicative_expr\n");
    switch (a->type) {
        case _CAST_EXPR:
            disp_cast_expr(spc+1, a->v1._cast_expr);
            break;
            
        case _MULTIPLY:
            disp_multiplicative_expr(spc+1, a->v1._multiplicative_expr);
            SPC; printf("*\n");
            disp_cast_expr(spc+1, a->v2);
            break;
            
        case _DIVIDE:
            disp_multiplicative_expr(spc+1, a->v1._multiplicative_expr);
            SPC; printf("/\n");
            disp_cast_expr(spc+1, a->v2);
            break;
            
        case _MODULO:
            disp_multiplicative_expr(spc+1, a->v1._multiplicative_expr);
            SPC; printf("%\n");
            disp_cast_expr(spc+1, a->v2);
            break;
    }
}

void disp_parameter_declaration(int spc, struct parameter_declaration *a)
{
    SSPC; printf("-parameter_declaration\n");
    switch (a->type) {
        case _DECLARATION:
            disp_type_specifier_list(spc+1, a->v1._type_specifier_list);
            disp_declarator(spc+1, a->v2);
            break;
            
        case _TYPE_NAME:
            disp_type_name(spc+1, a->v1._type_name);
            break;
    }
}

void disp_parameter_identifier_list(int spc, struct parameter_identifier_list *a)
{
    SSPC; printf("-parameter_identifier_list\n");
    disp_identifier_list(spc+1, a->v);
    if (a->varargs) {
        SPC; printf(", ...\n");
    }
}

void disp_parameter_list(int spc, struct parameter_list *a)
{
    SSPC; printf("-parameter_list\n");
    if (!a->end) {
        disp_parameter_list(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_parameter_declaration(spc+1, a->v2);
}

void disp_parameter_type_list(int spc, struct parameter_type_list *a)
{
    SSPC; printf("-parameter_type_list\n");
    disp_parameter_list(spc+1, a->v);
    if (a->varargs) {
        SPC; printf(", ...\n");
    }
}

void disp_pointer(int spc, struct pointer *a)
{
    SSPC; printf("-pointer\n");
    SPC; printf("*\n");
    if (a->has_type_specifier_list) {
        disp_type_specifier_list(spc+1, a->v1);
    }
    if (!a->end) {
        disp_pointer(spc+1, a->v2);
    }
}

void disp_postfix_expr(int spc, struct postfix_expr *a)
{
    SSPC; printf("-postfix_expr\n");
    switch (a->type) {
        case _PRIMARY_EXPR:
            disp_primary_expr(spc+1, a->v1._primary_expr);
            break;
            
        case _ARRAY_REF:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("[\n");
            disp_expr(spc+1, a->v2._expr);
            SPC; printf("]\n");
            break;
            
        case _SIMPLE_FCALL:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("()\n");
            break;
            
        case _FCALL:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("(\n");
            disp_argument_expr_list(spc+1, a->v2._argument_expr_list);
            SPC; printf(")\n");
            break;
            
        case _DOT:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf(".\n");
            disp_identifier(spc+1, a->v2._identifier);
            break;
            
        case _PTR_OP:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("->\n");
            disp_identifier(spc+1, a->v2._identifier);
            break;
            
        case _INC:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("++\n");
            break;
            
        case _DEC:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            SPC; printf("--\n");
            break;
    }
}

void disp_primary_expr(int spc, struct primary_expr *a)
{
    SSPC; printf("-primary_expr\n");
    switch (a->type) {
        case _IDENTIFIER:
            disp_identifier(spc+1, a->v._identifier);
            break;
            
        case _CONSTANT:
            SPC; printf("CONSTANT: %s\n", a->v._token);
            break;
            
        case _STRING:
            SPC; printf("STRING: %s\n", a->v._token);
            break;
            
        case _EXPR:
            disp_expr(spc+1, a->v._expr);
            break;
    }
}

void disp_relational_expr(int spc, struct relational_expr *a)
{
    SSPC; printf("-relational_expr\n");
    switch (a->type) {
        case _SHIFT_EXPR:
            disp_shift_expr(spc+1, a->v1._shift_expr);
            break;
            
        case _LESS:
            disp_relational_expr(spc+1, a->v1._relational_expr);
            SPC; printf("<\n");
            disp_shift_expr(spc+1, a->v2);
            break;
            
        case _GREATER:
            disp_relational_expr(spc+1, a->v1._relational_expr);
            SPC; printf(">\n");
            disp_shift_expr(spc+1, a->v2);
            break;
            
        case _LE:
            disp_relational_expr(spc+1, a->v1._relational_expr);
            SPC; printf("<=\n");
            disp_shift_expr(spc+1, a->v2);
            break;
            
        case _GE:
            disp_relational_expr(spc+1, a->v1._relational_expr);
            SPC; printf(">=\n");
            disp_shift_expr(spc+1, a->v2);
            break;
    }
}

void disp_selection_statement(int spc, struct selection_statement *a)
{
    SSPC; printf("-selection_statement\n");
    switch (a->type) {
        case _IF:
        case _IF_ELSE:
            SPC; printf("if (\n");
            disp_expr(spc+1, a->v1);
            SPC; printf(")\n");
            disp_statement(spc+1, a->v2);
            if (a->type == _IF_ELSE) {
                SPC; printf("else\n");
                disp_statement(spc+1, a->v3);
            }
            break;
            
        case _SWITCH:
            SPC; printf("switch (\n");
            disp_expr(spc+1, a->v1);
            SPC; printf(")\n");
            disp_statement(spc+1, a->v2);
            break;
    }
}

void disp_shift_expr(int spc, struct shift_expr *a)
{
    SSPC; printf("-shift_expr\n");
    switch (a->type) {
        case _ADDITIVE_EXPR:
            disp_additive_expr(spc+1, a->v1._additive_expr);
            break;
            
        case _LEFT_SHIFT:
            disp_shift_expr(spc+1, a->v1._shift_expr);
            SPC; printf("<<\n");
            disp_additive_expr(spc+1, a->v2);
            break;
            
        case _RIGHT_SHIFT:
            disp_shift_expr(spc+1, a->v1._shift_expr);
            SPC; printf(">>\n");
            disp_additive_expr(spc+1, a->v2);
            break;
    }
}

void disp_statement(int spc, struct statement *a)
{
    SSPC; printf("-statement\n");
    switch (a->type) {
        case _LABELED_STATEMENT:
            disp_labeled_statement(spc+1, a->v._labeled_statement);
            break;
            
        case _COMPOUND_STATEMENT:
            disp_compound_statement(spc+1, a->v._compound_statement);
            break;
            
        case _EXPRESSION_STATEMENT:
            disp_expression_statement(spc+1, a->v._expression_statement);
            break;
            
        case _SELECTION_STATEMENT:
            disp_selection_statement(spc+1, a->v._selection_statement);
            break;
            
        case _ITERATION_STATEMENT:
            disp_iteration_statement(spc+1, a->v._iteration_statement);
            break;
            
        case _JUMP_STATEMENT:
            disp_jump_statement(spc+1, a->v._jump_statement);
            break;
    }
}

void disp_statement_list(int spc, struct statement_list *a)
{
    SSPC; printf("-statement_list\n");
    if (!a->end) {
        disp_statement_list(spc+1, a->v1);
    }
    disp_statement(spc+1, a->v2);
}

void disp_storage_class_specifier(int spc, struct storage_class_specifier *a)
{
    SSPC; printf("-storage_class_specifier\n");
    switch (a->type) {
        case _TYPEDEF:
            SPC; printf("typedef\n");
            break;
            
        case _EXTERN:
            SPC; printf("extern\n");
            break;
            
        case _STATIC:
            SPC; printf("static\n");
            break;
            
        case _AUTO:
            SPC; printf("auto\n");
            break;
            
        case _REGISTER:
            SPC; printf("register\n");
            break;
    }
}

void disp_struct_declaration(int spc, struct struct_declaration *a)
{
    SSPC; printf("-struct_declaration\n");
    disp_type_specifier_list(spc+1, a->v1);
    disp_struct_declarator_list(spc+1, a->v2);
}

void disp_struct_declaration_list(int spc, struct struct_declaration_list *a)
{
    SSPC; printf("-struct_declaration_list\n");
    if (!a->end) {
        disp_struct_declaration_list(spc+1, a->v1);
    }
    disp_struct_declaration(spc+1, a->v2);
}

void disp_struct_declarator(int spc, struct struct_declarator *a)
{
    SSPC; printf("-struct_declarator\n");
    if (a->has_declarator) {
        disp_declarator(spc+1, a->v1);
    }
    if (a->has_bitwidth) {
        SPC; printf(":\n");
        disp_conditional_expr(spc+1, a->v2);
    }
}

void disp_struct_declarator_list(int spc, struct struct_declarator_list *a)
{
    SSPC; printf("-struct_declarator_list\n");
    if (!a->end) {
        disp_struct_declarator_list(spc+1, a->v1);
        SPC; printf(",\n");
    }
    disp_struct_declarator(spc+1, a->v2);
}

void disp_struct_or_union(int spc, struct struct_or_union *a)
{
    SSPC; printf("-struct_or_union\n");
    switch (a->type) {
        case _STRUCT:
            SPC; printf("struct\n");
            break;
            
        case _UNION:
            SPC; printf("union\n");
            break;
    }
}

void disp_struct_or_union_specifier(int spc, struct struct_or_union_specifier *a)
{
    SSPC; printf("-struct_or_union_specifier\n");
    disp_struct_or_union(spc+1, a->v1);
    if (a->has_identifier) {
        disp_identifier(spc+1, a->v2);
    }
    if (a->has_struct_declaration_list) {
        SPC; printf("{\n");
        disp_struct_declaration_list(spc+1, a->v3);
        SPC; printf("}\n");
    }
}

void disp_type_name(int spc, struct type_name *a)
{
    SSPC; printf("-type_name\n");
    disp_type_specifier_list(spc+1, a->v1);
    if (a->has_declarator) {
        disp_abstract_declarator(spc+1, a->v2);
    }
}

void disp_type_specifier(int spc, struct type_specifier *a)
{
    SSPC; printf("-type_specifier\n");
    switch (a->type) {
        case _CHAR:
            SPC; printf("char\n");
            break;
            
        case _SHORT:
            SPC; printf("short\n");
            break;
            
        case _INT:
            SPC; printf("int\n");
            break;
            
        case _LONG:
            SPC; printf("long\n");
            break;
            
        case _SIGNED:
            SPC; printf("signed\n");
            break;
            
        case _UNSIGNED:
            SPC; printf("unsigned\n");
            break;
            
        case _FLOAT:
            SPC; printf("float\n");
            break;
            
        case _DOUBLE:
            SPC; printf("double\n");
            break;
            
        case _CONST:
            SPC; printf("const\n");
            break;
            
        case _VOLATILE:
            SPC; printf("volatile\n");
            break;
            
        case _VOID:
            SPC; printf("void\n");
            break;
            
        case _STRUCT_OR_UNION_SPECIFIER:
            disp_struct_or_union_specifier(spc+1, a->v._struct_or_union_specifier);
            break;
            
        case _ENUM_SPECIFIER:
            disp_enum_specifier(spc+1, a->v._enum_specifier);
            break;
            
        case _TYPE_NAME:
            SPC; printf("type_name\n");
            break;
    }
}

void disp_type_specifier_list(int spc, struct type_specifier_list *a)
{
    SSPC; printf("-type_specifier_list\n");
    if (!a->end) {
        disp_type_specifier_list(spc+1, a->v1);
    }
    disp_type_specifier(spc+1, a->v2);
}

void disp_unary_expr(int spc, struct unary_expr *a)
{
    SSPC; printf("-unary_expr\n");
    switch (a->type) {
        case _POSTFIX_EXPR:
            disp_postfix_expr(spc+1, a->v1._postfix_expr);
            break;
            
        case _INC:
            SPC; printf("++\n");
            disp_unary_expr(spc+1, a->v1._unary_expr);
            break;
            
        case _DEC:
            SPC; printf("--\n");
            disp_unary_expr(spc+1, a->v1._unary_expr);
            break;
            
        case _UNARY_OP:
            disp_unary_operator(spc+1, a->v1._unary_operator);
            disp_cast_expr(spc+1, a->v2);
            break;
            
        case _SIZEOF_EXPR:
            SPC; printf("sizeof\n");
            disp_unary_expr(spc+1, a->v1._unary_expr);
            break;
            
        case _SIZEOF_TYPE:
            SPC; printf("sizeof\n");
            disp_type_name(spc+1, a->v1._type_name);
            break;
    }
}

void disp_unary_operator(int spc, struct unary_operator *a)
{
    SSPC; printf("-unary_operator\n");
    switch (a->type) {
        case _ADDRESS_OF:
            SPC; printf("&\n");
            break;
            
        case _DEREFERENCE:
            SPC; printf("*\n");
            break;
            
        case _POSITIVE:
            SPC; printf("+\n");
            break;
            
        case _NEGATIVE:
            SPC; printf("-\n");
            break;
            
        case _BIT_NOT:
            SPC; printf("~\n");
            break;
            
        case _LOGIC_NOT:
            SPC; printf("!\n");
            break;
    }
}
