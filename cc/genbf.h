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

#include "ast.h"
#include "genbf/generator.h"

/* _expr functions have a special syntax:
 * Input: The expression, a boolean for whether this is an lval, and (if it is
 *        an lval), a location to put the appropriate struct type.
 * Output: If lval:
 *           -1 if a pointer has been pushed onto the stack
 *           >=0 is the depth of the variable in the stack
 *           t is set
 *         else:
 *           irrelevent (usu. 0)
 */

void genbf_abstract_declarator(struct abstract_declarator *a);
void genbf_abstract_declarator2(struct abstract_declarator2 *a);

int genbf_additive_expr(struct additive_expr *a, int lval, struct type **t);
char *genbf_additive_expr_get_primary(int type, struct additive_expr *a);

int genbf_and_expr(struct and_expr *a, int lval, struct type **t);
char *genbf_and_expr_get_primary(int type, struct and_expr *a);

int genbf_argument_expr_list(struct argument_expr_list *a);

int genbf_assignment_expr(struct assignment_expr *a, int lval, struct type **t);
char *genbf_assignment_expr_get_primary(int type, struct assignment_expr *a);

void genbf_assignment_operator(struct assignment_operator *a);

int genbf_cast_expr(struct cast_expr *a, int lval, struct type **t);
char *genbf_cast_expr_get_primary(int type, struct cast_expr *a);

void genbf_compound_statement(struct compound_statement *a);

int genbf_conditional_expr(struct conditional_expr *a, int lval, struct type **t);
char *genbf_conditional_expr_get_primary(int type, struct conditional_expr *a);

struct type *genbf_declarator(struct declarator *a, struct type *into);

struct type *genbf_declarator2(struct declarator2 *a, struct type *into);
char *genbf_declarator2_get_identifier(struct declarator2 *a);

void genbf_declaration(struct declaration *a);
void genbf_declaration_list(struct declaration_list *a);
void genbf_declaration_specifiers(struct declaration_specifiers *a);
void genbf_enum_specifier(struct enum_specifier *a);
void genbf_enumerator(struct enumerator *a);
void genbf_enumerator_list(struct enumerator_list *a);

int genbf_equality_expr(struct equality_expr *a, int lval, struct type **t);
char *genbf_equality_expr_get_primary(int type, struct equality_expr *a);

int genbf_exclusive_or_expr(struct exclusive_or_expr *a, int lval, struct type **t);
char *genbf_exclusive_or_expr_get_primary(int type, struct exclusive_or_expr *a);

int genbf_expr(struct expr *a, int lval, struct type **t);
void genbf_expression_statement(struct expression_statement *a);
void genbf_external_definition(struct external_definition *a);
void genbf_external_definition_list(struct external_definition_list *a);
void genbf_file(struct file *a);
void genbf_function_body(struct function_body *a);
void genbf_function_definition(struct function_definition *a);
void genbf_identifier(struct identifier *a);
void genbf_identifier_list(struct identifier_list *a);

int genbf_inclusive_or_expr(struct inclusive_or_expr *a, int lval, struct type **t);
char *genbf_inclusive_or_expr_get_primary(int type, struct inclusive_or_expr *a);

void genbf_init_declarator(struct init_declarator *a);
void genbf_init_declarator_list(struct init_declarator_list *a);
void genbf_initializer(struct initializer *a);
void genbf_initializer_list(struct initializer_list *a);
void genbf_iteration_statement(struct iteration_statement *a);
void genbf_jump_statement(struct jump_statement *a);
void genbf_labeled_statement(struct labeled_statement *a);

int genbf_logical_and_expr(struct logical_and_expr *a, int lval, struct type **t);
char *genbf_logical_and_expr_get_primary(int type, struct logical_and_expr *a);

int genbf_logical_or_expr(struct logical_or_expr *a, int lval, struct type **t);
char *genbf_logical_or_expr_get_primary(int type, struct logical_or_expr *a);

int genbf_multiplicative_expr(struct multiplicative_expr *a, int lval, struct type **t);
char *genbf_multiplicative_expr_get_primary(int type, struct multiplicative_expr *a);

void genbf_parameter_declaration(struct parameter_declaration *a);
void genbf_parameter_identifier_list(struct parameter_identifier_list *a);
void genbf_parameter_list(struct parameter_list *a);
void genbf_parameter_type_list(struct parameter_type_list *a);
void genbf_pointer(struct pointer *a);

int genbf_postfix_expr(struct postfix_expr *a, int lval, struct type **t);
char *genbf_postfix_expr_get_primary(int type, struct postfix_expr *a);

int genbf_primary_expr(struct primary_expr *a, int lval, struct type **t);
char *genbf_primary_expr_get_primary(int type, struct primary_expr *a);
char *genbf_parse_string(char *inp);

int genbf_relational_expr(struct relational_expr *a, int lval, struct type **t);
char *genbf_relational_expr_get_primary(int type, struct relational_expr *a);

void genbf_selection_statement(struct selection_statement *a);

int genbf_shift_expr(struct shift_expr *a, int lval, struct type **t);
char *genbf_shift_expr_get_primary(int type, struct shift_expr *a);

void genbf_statement(struct statement *a);
void genbf_statement_list(struct statement_list *a);
void genbf_storage_class_specifier(struct storage_class_specifier *a);
void genbf_struct_declaration(struct struct_declaration *a);
void genbf_struct_declaration_list(struct struct_declaration_list *a);
void genbf_struct_declarator(struct struct_declarator *a);
void genbf_struct_declarator_list(struct struct_declarator_list *a);
void genbf_struct_or_union(struct struct_or_union *a);
void genbf_struct_or_union_specifier(struct struct_or_union_specifier *a);
void genbf_type_name(struct type_name *a);
void genbf_type_specifier(struct type_specifier *a);
void genbf_type_specifier_list(struct type_specifier_list *a);

int genbf_unary_expr(struct unary_expr *a, int lval, struct type **t);
char *genbf_unary_expr_get_primary(int type, struct unary_expr *a);

void genbf_unary_operator(struct unary_operator *a);
