CC=gcc
CFLAGS=-O2 -g

AR=ar
ARFLAGS=rcu

LIBGENBF_A_OBJS=abstract_declarator2.o \
abstract_declarator.o \
additive_expr.o \
and_expr.o \
argument_expr_list.o \
assignment_expr.o \
assignment_operator.o \
cast_expr.o \
compound_statement.o \
conditional_expr.o \
declaration.o \
declaration_list.o \
declaration_specifiers.o \
declarator2.o \
declarator.o \
enumerator.o \
enumerator_list.o \
enum_specifier.o \
equality_expr.o \
exclusive_or_expr.o \
expr.o \
expression_statement.o \
external_definition.o \
external_definition_list.o \
file.o \
function_body.o \
function_definition.o \
identifier.o \
identifier_list.o \
inclusive_or_expr.o \
init_declarator.o \
init_declarator_list.o \
initializer.o \
initializer_list.o \
iteration_statement.o \
jump_statement.o \
labeled_statement.o \
logical_and_expr.o \
logical_or_expr.o \
multiplicative_expr.o \
parameter_declaration.o \
parameter_identifier_list.o \
parameter_list.o \
parameter_type_list.o \
pointer.o \
postfix_expr.o \
primary_expr.o \
relational_expr.o \
selection_statement.o \
shift_expr.o \
statement.o \
statement_list.o \
storage_class_specifier.o \
struct_declaration.o \
struct_declaration_list.o \
struct_declarator.o \
struct_declarator_list.o \
struct_or_union.o \
struct_or_union_specifier.o \
type_name.o \
type_specifier.o \
type_specifier_list.o \
unary_expr.o \
unary_operator.o \
generator.o

all: libgenbf.a

libgenbf.a: $(LIBGENBF_A_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIBGENBF_A_OBJS)

.PREFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBGENBF_A_OBJS) libgenbf.a
