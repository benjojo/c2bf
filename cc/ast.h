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

#ifndef AST_H
#define AST_H

/* valid typesof nodes: */
#define _ABSTRACT_DECLARATOR         1
#define _ADD                         2
#define _ADD_ASSIGN                  3
#define _ADDITIVE_EXPR               4
#define _ADDRESS_OF                  5
#define _AND_ASSIGN                  6
#define _ARRAY                       7
#define _ARRAY_REF                   8
#define _ASSIGN                      9
#define _ASSIGNMENT                 10
#define _ASSIGNMENT_EXPR            11
#define _AUTO                       12
#define _BIT_NOT                    13
#define _BREAK                      14
#define _CASE                       15
#define _CAST_EXPR                  16
#define _CHAR                       17
#define _COMPOUND_STATEMENT         18
#define _CONDITIONAL_EXPR           19
#define _CONST                      20
#define _CONSTANT                   21
#define _CONTINUE                   22
#define _DEC                        23
#define _DECLARATION                24
#define _DECLARATOR                 25
#define _DEFAULT                    26
#define _DEREFERENCE                27
#define _DIV_ASSIGN                 28
#define _DIVIDE                     29
#define _DO_WHILE                   30
#define _DOT                        31
#define _DOUBLE                     32
#define _ENUM_SPECIFIER             33
#define _EQUAL                      34
#define _EXPR                       35
#define _EXPRESSION_STATEMENT       36
#define _EXTERN                     37
#define _FCALL                      38
#define _FLOAT                      39
#define _FOR                        40
#define _FUNC_OLD_STYLE             41
#define _FUNC_BY_TYPE               42
#define _FUNCTION_DEFINITION        43
#define _GE                         44
#define _GOTO                       45
#define _GREATER                    46
#define _IDENTIFIER                 47
#define _IF                         48
#define _IF_ELSE                    49
#define _INC                        50
#define _INITIALIZER_LIST           51
#define _INT                        52
#define _ITERATION_STATEMENT        53
#define _JUMP_STATEMENT             54
#define _LABEL                      55
#define _LABELED_STATEMENT          56
#define _LE                         57
#define _LEFT_ASSIGN                58
#define _LEFT_SHIFT                 59
#define _LESS                       60
#define _LOGIC_NOT                  61
#define _LONG                       62
#define _MOD_ASSIGN                 63
#define _MODULO                     64
#define _MUL_ASSIGN                 65
#define _MULTIPLICATIVE_EXPR        66
#define _MULTIPLY                   67
#define _NEGATIVE                   68
#define _NEQUAL                     69
#define _OR_ASSIGN                  70
#define _POSITIVE                   71
#define _POSTFIX_EXPR               72
#define _PRIMARY_EXPR               73
#define _PTR_OP                     74
#define _REGISTER                   75
#define _RELATIONAL_EXPR            76
#define _RETURN                     77
#define _RIGHT_ASSIGN               78
#define _RIGHT_SHIFT                79
#define _SELECTION_STATEMENT        80
#define _SHIFT_EXPR                 81
#define _SHORT                      82
#define _SIGNED                     83
#define _SIMPLE_ARRAY               84
#define _SIMPLE_FCALL               85
#define _SIMPLE_FUNC                86
#define _SIZEOF_EXPR                87
#define _SIZEOF_TYPE                88
#define _STATIC                     89
#define _STORAGE_CLASS_SPECIFIER    90
#define _STRING                     91
#define _STRUCT                     92
#define _STRUCT_OR_UNION_SPECIFIER  93
#define _SUB_ASSIGN                 94
#define _SUBTRACT                   95
#define _SWITCH                     96
#define _TYPE_CAST                  97
#define _TYPE_NAME                  98
#define _TYPE_SPECIFIER             99
#define _TYPEDEF                   100
#define _UNARY_EXPR                101
#define _UNARY_OP                  102
#define _UNION                     103
#define _UNSIGNED                  104
#define _VOID                      105
#define _VOLATILE                  106
#define _WHILE                     107
#define _XOR_ASSIGN                108

extern struct file *ast_root;

struct abstract_declarator {
    char has_pointer; /* if 0, no v1 */
    char has_abstract_declarator2; /* if 0, no v2 */
    struct pointer *v1;
    struct abstract_declarator2 *v2;
};
void disp_abstract_declarator(int spc, struct abstract_declarator *a);

struct abstract_declarator2 {
    /* _ABSTRACT_DECLARATOR, _SIMPLE_ARRAY, _ARRAY, _SIMPLE_FUNC,
     * _FUNC_BY_TYPE */
    int type;
    char end; /* if 1, no v1._abstract_declarator2 */
    union {
        struct abstract_declarator *_abstract_declarator;
        struct abstract_declarator2 *_abstract_declarator2;
    } v1;
    union {
        struct conditional_expr *_conditional_expr;
        struct parameter_type_list *_parameter_type_list;
    } v2;
};
void disp_abstract_declarator2(int spc, struct abstract_declarator2 *a);

struct additive_expr {
    /* _MULTIPLICATIVE_EXPR, _ADD, _SUBTRACT */
    int type;
    union {
        struct multiplicative_expr *_multiplicative_expr;
        struct additive_expr *_additive_expr;
    } v1;
    struct multiplicative_expr *v2;
};
void disp_additive_expr(int spc, struct additive_expr *a);

struct and_expr {
    char end; /* if 1, only v2 */
    struct and_expr *v1;
    struct equality_expr *v2;
};
void disp_and_expr(int spc, struct and_expr *a);

struct argument_expr_list {
    char end; /* if 1, only v2 */
    struct argument_expr_list *v1;
    struct assignment_expr *v2;
};
void disp_argument_expr_list(int spc, struct argument_expr_list *a);

struct assignment_expr {
    /* _CONDITIONAL_EXPR, _ASSIGNMENT */
    int type;
    union {
        struct conditional_expr *_conditional_expr;
        struct unary_expr *_unary_expr;
    } v1;
    struct assignment_operator *v2;
    struct assignment_expr *v3;
};
void disp_assignment_expr(int spc, struct assignment_expr *a);

struct assignment_operator {
    /* _ASSIGN, _MUL_ASSIGN, _DIV_ASSIGN, _MOD_ASSIGN, _ADD_ASSIGN,
     * _SUB_ASSIGN, _LEFT_ASSIGN, _RIGHT_ASSIGN, _AND_ASSIGN, _XOR_ASSIGN,
     * _OR_ASSIGN */
    int type;
};
void disp_assignment_operator(int spc, struct assignment_operator *a);

struct cast_expr {
    /* _UNARY_EXPR, _TYPE_CAST */
    int type;
    union {
        struct unary_expr *_unary_expr;
        struct type_name *_type_name;
    } v1;
    struct cast_expr *v2;
};
void disp_cast_expr(int spc, struct cast_expr *a);

struct compound_statement {
    char has_declaration_list; /* if 0, no v1 */
    char has_statement_list; /* if 0, no v2 */
    struct declaration_list *v1;
    struct statement_list *v2;
};
void disp_compound_statement(int spc, struct compound_statement *a);

struct conditional_expr {
    char end; /* if 1, only v1 */
    struct logical_or_expr *v1;
    struct logical_or_expr *v2;
    struct conditional_expr *v3;
};
void disp_conditional_expr(int spc, struct conditional_expr *a);

struct declarator {
    char pointer; /* if 0, only v2 */
    struct pointer *v1;
    struct declarator2 *v2;
};
void disp_declarator(int spc, struct declarator *a);

struct declarator2 {
    /* _IDENTIFIER, _DECLARATOR, _SIMPLE_ARRAY, _ARRAY, _SIMPLE_FUNC,
     * _FUNC_BY_TYPE, _FUNC_OLD_STYLE */
    int type;
    union {
        struct identifier *_identifier;
        struct declarator *_declarator;
        struct declarator2 *_declarator2;
    } v1;
    union {
        struct conditional_expr *_conditional_expr;
        struct parameter_type_list *_parameter_type_list;
        struct parameter_identifier_list *_parameter_identifier_list;
    } v2;
};
void disp_declarator2(int spc, struct declarator2 *a);

struct declaration {
    char has_init_declarator_list; /* if 0, only v1 */
    struct declaration_specifiers *v1;
    struct init_declarator_list *v2;
};
void disp_declaration(int spc, struct declaration *a);

struct declaration_list {
    char end; /* if 1, only v2 */
    struct declaration_list *v1;
    struct declaration *v2;
};
void disp_declaration_list(int spc, struct declaration_list *a);

struct declaration_specifiers {
    /* _STORAGE_CLASS_SPECIFIER, _TYPE_SPECIFIER */
    int type;
    char end; /* if 1, only v1 */
    union {
        struct storage_class_specifier *_storage_class_specifier;
        struct type_specifier *_type_specifier;
    } v1;
    struct declaration_specifiers *v2;
};
void disp_declaration_specifiers(int spc, struct declaration_specifiers *a);

struct enum_specifier {
    char has_identifier; /* if 0, no v1 */
    char has_enumerator_list; /* if 0, no v2 */
    struct identifier *v1;
    struct enumerator_list *v2;
};
void disp_enum_specifier(int spc, struct enum_specifier *a);

struct enumerator {
    char assign; /* if 0, only v1 */
    struct identifier *v1;
    struct conditional_expr *v2;
};
void disp_enumerator(int spc, struct enumerator *a);

struct enumerator_list {
    char end; /* if 1, only v2 */
    struct enumerator_list *v1;
    struct enumerator *v2;
};
void disp_enumerator_list(int spc, struct enumerator_list *a);

struct equality_expr {
    /* _RELATIONAL_EXPR, _EQUAL, _NEQUAL */
    int type;
    union {
        struct relational_expr *_relational_expr;
        struct equality_expr *_equality_expr;
    } v1;
    struct relational_expr *v2;
};
void disp_equality_expr(int spc, struct equality_expr *a);

struct exclusive_or_expr {
    char end; /* if 1, only v2 */
    struct exclusive_or_expr *v1;
    struct and_expr *v2;
};
void disp_exclusive_or_expr(int spc, struct exclusive_or_expr *a);

struct expr {
    char end; /* if 1, only v2 */
    struct expr *v1;
    struct assignment_expr *v2;
};
void disp_expr(int spc, struct expr *a);

struct expression_statement {
    char has_expr; /* if 0, no v */
    struct expr *v;
};
void disp_expression_statement(int spc, struct expression_statement *a);

struct external_definition {
    /* _FUNCTION_DEFINITION, _DECLARATION */
    int type;
    union {
        struct function_definition *_function_definition;
        struct declaration *_declaration;
    } v;
};
void disp_external_definition(int spc, struct external_definition *a);

struct external_definition_list {
    char end; /* if 1, only v2 */
    struct external_definition_list *v1;
    struct external_definition *v2;
};
void disp_external_definition_list(int spc, struct external_definition_list *a);

struct file {
    struct external_definition_list *v;
};
void disp_file(int spc, struct file *a);

struct function_body {
    char has_declaration_list; /* if 1, only v2 */
    struct declaration_list *v1;
    struct compound_statement *v2;
};
void disp_function_body(int spc, struct function_body *a);

struct function_definition {
    char has_declaration_specifiers; /* if 0, no v1 */
    struct declaration_specifiers *v1;
    struct declarator *v2;
    struct function_body *v3;
};
void disp_function_definition(int spc, struct function_definition *a);

struct identifier {
    char *v;
};
void disp_identifier(int spc, struct identifier *a);

struct identifier_list {
    char end; /* if 1, only v2 */
    struct identifier_list *v1;
    struct identifier *v2;
};
void disp_identifier_list(int spc, struct identifier_list *a);

struct inclusive_or_expr {
    char end; /* if 1, only v2 */
    struct inclusive_or_expr *v1;
    struct exclusive_or_expr *v2;
};
void disp_inclusive_or_expr(int spc, struct inclusive_or_expr *a);

struct init_declarator {
    char assign; /* if 0, only v1 */
    struct declarator *v1;
    struct initializer *v2;
};
void disp_init_declarator(int spc, struct init_declarator *a);

struct init_declarator_list {
    char end; /* if 1, only v2 */
    struct init_declarator_list *v1;
    struct init_declarator *v2;
};
void disp_init_declarator_list(int spc, struct init_declarator_list *a);

struct initializer {
    /* _ASSIGNMENT_EXPR, _INITIALIZER_LIST */
    int type;
    union {
        struct assignment_expr *_assignment_expr;
        struct initializer_list *_initializer_list;
    } v;
};
void disp_initializer(int spc, struct initializer *a);

struct initializer_list {
    char end; /* if 1, only v2 */
    struct initializer_list *v1;
    struct initializer *v2;
};
void disp_initializer_list(int spc, struct initializer_list *a);

struct iteration_statement {
    /* _WHILE, _DO_WHILE, _FOR */
    int type;
    char has_initializer; /* _FOR: if 0, no v1 */
    char has_condition; /* _FOR: if 0, no v2 */
    char has_post; /* _FOR: if 0, no v3 */
    struct expr *v1;
    struct expr *v2;
    struct expr *v3;
    struct statement *v4;
};
void disp_iteration_statement(int spc, struct iteration_statement *a);

struct jump_statement {
    /* _GOTO, _CONTINUE, _BREAK, _RETURN */
    int type;
    char has_expr; /* _RETURN: if 0, no v */
    union {
        struct identifier *_identifier;
        struct expr *_expr;
    } v;
};
void disp_jump_statement(int spc, struct jump_statement *a);

struct labeled_statement {
    /* _LABEL, _CASE, _DEFAULT */
    int type;
    union {
        struct identifier *_identifier;
        struct conditional_expr *_conditional_expr;
    } v1;
    struct statement *v2;
};
void disp_labeled_statement(int spc, struct labeled_statement *a);

struct logical_and_expr {
    char end; /* if 1, only v2 */
    struct logical_and_expr *v1;
    struct inclusive_or_expr *v2;
};
void disp_logical_and_expr(int spc, struct logical_and_expr *a);

struct logical_or_expr {
    char end; /* if 1, only v2 */
    struct logical_or_expr *v1;
    struct logical_and_expr *v2;
};
void disp_logical_or_expr(int spc, struct logical_or_expr *a);

struct multiplicative_expr {
    /* _CAST_EXPR, _MULTIPLY, _DIVIDE, _MODULO */
    int type;
    union {
        struct multiplicative_expr *_multiplicative_expr;
        struct cast_expr *_cast_expr;
    } v1;
    struct cast_expr *v2;
};
void disp_multiplicative_expr(int spc, struct multiplicative_expr *a);

struct parameter_declaration {
    /* _DECLARATION, _TYPE_NAME */
    int type;
    union {
        struct type_specifier_list *_type_specifier_list;
        struct type_name *_type_name;
    } v1;
    struct declarator *v2;
};
void disp_parameter_declaration(int spc, struct parameter_declaration *a);

struct parameter_identifier_list {
    char varargs; /* if 1, has ellipsis */
    struct identifier_list *v;
};
void disp_parameter_identifier_list(int spc, struct parameter_identifier_list *a);

struct parameter_list {
    char end; /* if 1, only v2 */
    struct parameter_list *v1;
    struct parameter_declaration *v2;
};
void disp_parameter_list(int spc, struct parameter_list *a);

struct parameter_type_list {
    char varargs; /* if 1, has ellipsis */
    struct parameter_list *v;
};
void disp_parameter_type_list(int spc, struct parameter_type_list *a);

struct pointer {
    char has_type_specifier_list; /* if 0, no v1 */
    char end; /* if 1, no v2 */
    struct type_specifier_list *v1;
    struct pointer *v2;
};
void disp_pointer(int spc, struct pointer *a);

struct postfix_expr {
    /* _PRIMARY_EXPR, _ARRAY_REF, _SIMPLE_FCALL, _FCALL, _DOT, _PTR_OP, _INC,
     * _DEC */
    int type;
    union {
        struct primary_expr *_primary_expr;
        struct postfix_expr *_postfix_expr;
    } v1;
    union {
        struct expr *_expr;
        struct argument_expr_list *_argument_expr_list;
        struct identifier *_identifier;
    } v2;
};
void disp_postfix_expr(int spc, struct postfix_expr *a);

struct primary_expr {
    /* _IDENTIFIER, _CONSTANT, _STRING, _EXPR */
    int type;
    union {
        struct identifier *_identifier;
        char *_token;
        struct expr *_expr;
    } v;
};
void disp_primary_expr(int spc, struct primary_expr *a);

struct relational_expr {
    /* _SHIFT_EXPR, _LESS, _GREATER, _LE, _GE */
    int type;
    union {
        struct shift_expr *_shift_expr;
        struct relational_expr *_relational_expr;
    } v1;
    struct shift_expr *v2;
};
void disp_relational_expr(int spc, struct relational_expr *a);

struct selection_statement {
    /* _IF, _IF_ELSE, _SWITCH */
    int type;
    struct expr *v1;
    struct statement *v2;
    struct statement *v3;
};
void disp_selection_statement(int spc, struct selection_statement *a);

struct shift_expr {
    /* _ADDITIVE_EXPR, _LEFT_SHIFT, _RIGHT_SHIFT */
    int type;
    union {
        struct additive_expr *_additive_expr;
        struct shift_expr *_shift_expr;
    } v1;
    struct additive_expr *v2;
};
void disp_shift_expr(int spc, struct shift_expr *a);

struct statement {
    /* _LABELED_STATEMENT, _COMPOUND_STATEMENT, _EXPRESSION_STATEMENT,
     * _SELECTION_STATEMENT, _ITERATION_STATEMENT, _JUMP_STATEMENT */
    int type;
    union {
        struct labeled_statement *_labeled_statement;
        struct compound_statement *_compound_statement;
        struct expression_statement *_expression_statement;
        struct selection_statement *_selection_statement;
        struct iteration_statement *_iteration_statement;
        struct jump_statement *_jump_statement;
    } v;
};
void disp_statement(int spc, struct statement *a);

struct statement_list {
    char end; /* if 1, only v2 */
    struct statement_list *v1;
    struct statement *v2;
};
void disp_statement_list(int spc, struct statement_list *a);

struct storage_class_specifier {
    /* _TYPEDEF, _EXTERN, _STATIC, _AUTO, _REGISTER */
    int type;
};
void disp_storage_class_specifier(int spc, struct storage_class_specifier *a);

struct struct_declaration {
    struct type_specifier_list *v1;
    struct struct_declarator_list *v2;
};
void disp_struct_declaration(int spc, struct struct_declaration *a);

struct struct_declaration_list {
    char end; /* if 1, only v2 */
    struct struct_declaration_list *v1;
    struct struct_declaration *v2;
};
void disp_struct_declaration_list(int spc, struct struct_declaration_list *a);

struct struct_declarator {
    char has_declarator; /* if 0, no v1 */
    char has_bitwidth; /* if 0, no v2 */
    struct declarator *v1;
    struct conditional_expr *v2;
};
void disp_struct_declarator(int spc, struct struct_declarator *a);

struct struct_declarator_list {
    char end; /* if 1, only v2 */
    struct struct_declarator_list *v1;
    struct struct_declarator *v2;
};
void disp_struct_declarator_list(int spc, struct struct_declarator_list *a);

struct struct_or_union {
    /* _STRUCT, _UNION */
    int type;
};
void disp_struct_or_union(int spc, struct struct_or_union *a);

struct struct_or_union_specifier {
    char has_identifier; /* if 0, no v2 */
    char has_struct_declaration_list; /* if 0, no v3 */
    struct struct_or_union *v1;
    struct identifier *v2;
    struct struct_declaration_list *v3;
};
void disp_struct_or_union_specifier(int spc, struct struct_or_union_specifier *a);

struct type_name {
    char has_declarator; /* if 0, only v1 */
    struct type_specifier_list *v1;
    struct abstract_declarator *v2;
};
void disp_type_name(int spc, struct type_name *a);

struct type_specifier {
    /* _CHAR, _SHORT, _INT, _LONG, _SIGNED, _UNSIGNED, _FLOAT, _DOUBLE, _CONST
     * _VOLATILE, _VOID, _STRUCT_OR_UNION_SPECIFIER, _ENUM_SPECIFIER,
     * _TYPE_NAME */
    int type;
    union {
        struct struct_or_union_specifier *_struct_or_union_specifier;
        struct enum_specifier *_enum_specifier;
    } v;
};
void disp_type_specifier(int spc, struct type_specifier *a);

struct type_specifier_list {
    char end; /* if 1, only v2 */
    struct type_specifier_list *v1;
    struct type_specifier *v2;
};
void disp_type_specifier_list(int spc, struct type_specifier_list *a);

struct unary_expr {
    /* _POSTFIX_EXPR, _INC, _DEC, _UNARY_OP, _SIZEOF_EXPR, _SIZEOF_TYPE */
    int type;
    union {
        struct postfix_expr *_postfix_expr;
        struct unary_expr *_unary_expr;
        struct unary_operator *_unary_operator;
        struct type_name *_type_name;
    } v1;
    struct cast_expr *v2;
};
void disp_unary_expr(int spc, struct unary_expr *a);

struct unary_operator {
    /* _ADDRESS_OF, _DEREFERENCE, _POSITIVE, _NEGATIVE, _BIT_NOT, _LOGIC_NOT */
    int type;
};
void disp_unary_operator(int spc, struct unary_operator *a);

#endif
