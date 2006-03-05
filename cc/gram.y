%{
#include <stdlib.h>
#include "ast.h"
extern char yytext[];
%}

%token<string> IDENTIFIER CONSTANT STRING_LITERAL
%token SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELIPSIS RANGE

%token<int> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%union {
        struct abstract_declarator *abstract_declarator;
        struct abstract_declarator2 *abstract_declarator2;
        struct additive_expr *additive_expr;
        struct and_expr *and_expr;
        struct argument_expr_list *argument_expr_list;
        struct assignment_expr *assignment_expr;
        struct assignment_operator *assignment_operator;
        struct cast_expr *cast_expr;
        struct compound_statement *compound_statement;
        struct conditional_expr *conditional_expr;
        struct declaration *declaration;
        struct declaration_list *declaration_list;
        struct declaration_specifiers *declaration_specifiers;
        struct declarator *declarator;
        struct declarator2 *declarator2;
        struct enum_specifier *enum_specifier;
        struct enumerator *enumerator;
        struct enumerator_list *enumerator_list;
        struct equality_expr *equality_expr;
        struct exclusive_or_expr *exclusive_or_expr;
        struct expr *expr;
        struct expression_statement *expression_statement;
        struct external_definition *external_definition;
        struct external_definition_list *external_definition_list;
        struct file *file;
        struct function_body *function_body;
        struct function_definition *function_definition;
        struct identifier *identifier;
        struct identifier_list *identifier_list;
        struct inclusive_or_expr *inclusive_or_expr;
        struct init_declarator *init_declarator;
        struct init_declarator_list *init_declarator_list;
        struct initializer *initializer;
        struct initializer_list *initializer_list;
        struct iteration_statement *iteration_statement;
        struct jump_statement *jump_statement;
        struct labeled_statement *labeled_statement;
        struct logical_and_expr *logical_and_expr;
        struct logical_or_expr *logical_or_expr;
        struct multiplicative_expr *multiplicative_expr;
        struct parameter_declaration *parameter_declaration;
        struct parameter_identifier_list *parameter_identifier_list;
        struct parameter_list *parameter_list;
        struct parameter_type_list *parameter_type_list;
        struct pointer *pointer;
        struct postfix_expr *postfix_expr;
        struct primary_expr *primary_expr;
        struct relational_expr *relational_expr;
        struct selection_statement *selection_statement;
        struct shift_expr *shift_expr;
        struct statement *statement;
        struct statement_list *statement_list;
        struct storage_class_specifier *storage_class_specifier;
        struct struct_declaration *struct_declaration;
        struct struct_declaration_list *struct_declaration_list;
        struct struct_declarator *struct_declarator;
        struct struct_declarator_list *struct_declarator_list;
        struct struct_or_union *struct_or_union;
        struct struct_or_union_specifier *struct_or_union_specifier;
        struct type_name *type_name;
        struct type_specifier *type_specifier;
        struct type_specifier_list *type_specifier_list;
        struct unary_expr *unary_expr;
        struct unary_operator *unary_operator;
        struct token *token;
        char *string;
}
%type<abstract_declarator> abstract_declarator;
%type<abstract_declarator2> abstract_declarator2;
%type<additive_expr> additive_expr;
%type<and_expr> and_expr;
%type<argument_expr_list> argument_expr_list;
%type<assignment_expr> assignment_expr;
%type<assignment_operator> assignment_operator;
%type<cast_expr> cast_expr;
%type<compound_statement> compound_statement;
%type<conditional_expr> conditional_expr;
%type<conditional_expr> constant_expr;
%type<declaration> declaration;
%type<declaration_list> declaration_list;
%type<declaration_specifiers> declaration_specifiers;
%type<declarator> declarator;
%type<declarator2> declarator2;
%type<enum_specifier> enum_specifier;
%type<enumerator> enumerator;
%type<enumerator_list> enumerator_list;
%type<equality_expr> equality_expr;
%type<exclusive_or_expr> exclusive_or_expr;
%type<expr> expr;
%type<expression_statement> expression_statement;
%type<external_definition> external_definition;
%type<external_definition_list> external_definition_list;
%type<file> file;
%type<function_body> function_body;
%type<function_definition> function_definition;
%type<identifier> identifier;
%type<identifier_list> identifier_list;
%type<inclusive_or_expr> inclusive_or_expr;
%type<init_declarator> init_declarator;
%type<init_declarator_list> init_declarator_list;
%type<initializer> initializer;
%type<initializer_list> initializer_list;
%type<iteration_statement> iteration_statement;
%type<jump_statement> jump_statement;
%type<labeled_statement> labeled_statement;
%type<logical_and_expr> logical_and_expr;
%type<logical_or_expr> logical_or_expr;
%type<multiplicative_expr> multiplicative_expr;
%type<parameter_declaration> parameter_declaration;
%type<parameter_identifier_list> parameter_identifier_list;
%type<parameter_list> parameter_list;
%type<parameter_type_list> parameter_type_list;
%type<pointer> pointer;
%type<postfix_expr> postfix_expr;
%type<primary_expr> primary_expr;
%type<relational_expr> relational_expr;
%type<selection_statement> selection_statement;
%type<shift_expr> shift_expr;
%type<statement> statement;
%type<statement_list> statement_list;
%type<storage_class_specifier> storage_class_specifier;
%type<struct_declaration> struct_declaration;
%type<struct_declaration_list> struct_declaration_list;
%type<struct_declarator> struct_declarator;
%type<struct_declarator_list> struct_declarator_list;
%type<struct_or_union> struct_or_union;
%type<struct_or_union_specifier> struct_or_union_specifier;
%type<type_name> type_name;
%type<type_specifier> type_specifier;
%type<type_specifier_list> type_specifier_list;
%type<unary_expr> unary_expr;
%type<unary_operator> unary_operator;

%start file
%%

primary_expr
	: identifier
          {
            $$ = (struct primary_expr *) malloc(sizeof(struct primary_expr));
            $$->type = _IDENTIFIER;
            $$->v._identifier = $1;
          }
	| CONSTANT
          {
            $$ = (struct primary_expr *) malloc(sizeof(struct primary_expr));
            $$->type = _CONSTANT;
            $$->v._token = $1;
          }
	| STRING_LITERAL
          {
            $$ = (struct primary_expr *) malloc(sizeof(struct primary_expr));
            $$->type = _STRING;
            $$->v._token = $1;
          }
	| '(' expr ')'
          {
            $$ = (struct primary_expr *) malloc(sizeof(struct primary_expr));
            $$->type = _EXPR;
            $$->v._expr = $2;
          }
	;

postfix_expr
	: primary_expr
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _PRIMARY_EXPR;
            $$->v1._primary_expr = $1;
          }
	| postfix_expr '[' expr ']'
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _ARRAY_REF;
            $$->v1._postfix_expr = $1;
            $$->v2._expr = $3;
          }
	| postfix_expr '(' ')'
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _SIMPLE_FCALL;
            $$->v1._postfix_expr = $1;
          }
	| postfix_expr '(' argument_expr_list ')'
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _FCALL;
            $$->v1._postfix_expr = $1;
            $$->v2._argument_expr_list = $3;
          }
	| postfix_expr '.' identifier
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _DOT;
            $$->v1._postfix_expr = $1;
            $$->v2._identifier = $3;
          }
	| postfix_expr PTR_OP identifier
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _PTR_OP;
            $$->v1._postfix_expr = $1;
            $$->v2._identifier = $3;
          }
	| postfix_expr INC_OP
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _INC;
            $$->v1._postfix_expr = $1;
          }
	| postfix_expr DEC_OP
          {
            $$ = (struct postfix_expr *) malloc(sizeof(struct postfix_expr));
            $$->type = _DEC;
            $$->v1._postfix_expr = $1;
          }          
	;

argument_expr_list
	: assignment_expr
          {
            $$ = (struct argument_expr_list *) malloc(sizeof(struct argument_expr_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| argument_expr_list ',' assignment_expr
          {
            $$ = (struct argument_expr_list *) malloc(sizeof(struct argument_expr_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

unary_expr
	: postfix_expr
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _POSTFIX_EXPR;
            $$->v1._postfix_expr = $1;
          }
	| INC_OP unary_expr
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _INC;
            $$->v1._unary_expr = $2;
          }
	| DEC_OP unary_expr
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _DEC;
            $$->v1._unary_expr = $2;
          }
	| unary_operator cast_expr
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _UNARY_OP;
            $$->v1._unary_operator = $1;
            $$->v2 = $2;
          }
	| SIZEOF unary_expr
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _SIZEOF_EXPR;
            $$->v1._unary_expr = $2;
          }
	| SIZEOF '(' type_name ')'
          {
            $$ = (struct unary_expr *) malloc(sizeof(struct unary_expr));
            $$->type = _SIZEOF_TYPE;
            $$->v1._type_name = $3;
          }
	;

unary_operator
	: '&'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _ADDRESS_OF;
          }
	| '*'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _DEREFERENCE;
          }
	| '+'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _POSITIVE;
          }
	| '-'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _NEGATIVE;
          }
	| '~'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _BIT_NOT;
          }
	| '!'
          {
            $$ = (struct unary_operator *) malloc(sizeof(struct unary_operator));
            $$->type = _LOGIC_NOT;
          }
	;

cast_expr
	: unary_expr
          {
            $$ = (struct cast_expr *) malloc(sizeof(struct cast_expr));
            $$->type = _UNARY_EXPR;
            $$->v1._unary_expr = $1;
          }
	| '(' type_name ')' cast_expr
          {
            $$ = (struct cast_expr *) malloc(sizeof(struct cast_expr));
            $$->type = _TYPE_CAST;
            $$->v1._type_name = $2;
            $$->v2 = $4;
          }
	;

multiplicative_expr
	: cast_expr
          {
            $$ = (struct multiplicative_expr *) malloc(sizeof(struct multiplicative_expr));
            $$->type = _CAST_EXPR;
            $$->v1._cast_expr = $1;
          }
	| multiplicative_expr '*' cast_expr
          {
            $$ = (struct multiplicative_expr *) malloc(sizeof(struct multiplicative_expr));
            $$->type = _MULTIPLY;
            $$->v1._multiplicative_expr = $1;
            $$->v2 = $3;
          }
	| multiplicative_expr '/' cast_expr
          {
            $$ = (struct multiplicative_expr *) malloc(sizeof(struct multiplicative_expr));
            $$->type = _DIVIDE;
            $$->v1._multiplicative_expr = $1;
            $$->v2 = $3;
          }
	| multiplicative_expr '%' cast_expr
          {
            $$ = (struct multiplicative_expr *) malloc(sizeof(struct multiplicative_expr));
            $$->type = _MODULO;
            $$->v1._multiplicative_expr = $1;
            $$->v2 = $3;
          }
	;

additive_expr
	: multiplicative_expr
          {
            $$ = (struct additive_expr *) malloc(sizeof(struct additive_expr));
            $$->type = _MULTIPLICATIVE_EXPR;
            $$->v1._multiplicative_expr = $1;
          }
	| additive_expr '+' multiplicative_expr
          {
            $$ = (struct additive_expr *) malloc(sizeof(struct additive_expr));
            $$->type = _ADD;
            $$->v1._additive_expr = $1;
            $$->v2 = $3;
          }
	| additive_expr '-' multiplicative_expr
          {
            $$ = (struct additive_expr *) malloc(sizeof(struct additive_expr));
            $$->type = _SUBTRACT;
            $$->v1._additive_expr = $1;
            $$->v2 = $3;
          }
	;

shift_expr
	: additive_expr
          {
            $$ = (struct shift_expr *) malloc(sizeof(struct shift_expr));
            $$->type = _ADDITIVE_EXPR;
            $$->v1._additive_expr = $1;
          }
	| shift_expr LEFT_OP additive_expr
          {
            $$ = (struct shift_expr *) malloc(sizeof(struct shift_expr));
            $$->type = _LEFT_SHIFT;
            $$->v1._shift_expr = $1;
            $$->v2 = $3;
          }
	| shift_expr RIGHT_OP additive_expr
          {
            $$ = (struct shift_expr *) malloc(sizeof(struct shift_expr));
            $$->type = _RIGHT_SHIFT;
            $$->v1._shift_expr = $1;
            $$->v2 = $3;
          }
	;

relational_expr
	: shift_expr
          {
            $$ = (struct relational_expr *) malloc(sizeof(struct relational_expr));
            $$->type = _SHIFT_EXPR;
            $$->v1._shift_expr = $1;
          }
	| relational_expr '<' shift_expr
          {
            $$ = (struct relational_expr *) malloc(sizeof(struct relational_expr));
            $$->type = _LESS;
            $$->v1._relational_expr = $1;
            $$->v2 = $3;
          }
	| relational_expr '>' shift_expr
          {
            $$ = (struct relational_expr *) malloc(sizeof(struct relational_expr));
            $$->type = _GREATER;
            $$->v1._relational_expr = $1;
            $$->v2 = $3;
          }
	| relational_expr LE_OP shift_expr
          {
            $$ = (struct relational_expr *) malloc(sizeof(struct relational_expr));
            $$->type = _LE;
            $$->v1._relational_expr = $1;
            $$->v2 = $3;
          }
	| relational_expr GE_OP shift_expr
          {
            $$ = (struct relational_expr *) malloc(sizeof(struct relational_expr));
            $$->type = _GE;
            $$->v1._relational_expr = $1;
            $$->v2 = $3;
          }
	;

equality_expr
	: relational_expr
          {
            $$ = (struct equality_expr *) malloc(sizeof(struct equality_expr));
            $$->type = _RELATIONAL_EXPR;
            $$->v1._relational_expr = $1;
          }
	| equality_expr EQ_OP relational_expr
          {
            $$ = (struct equality_expr *) malloc(sizeof(struct equality_expr));
            $$->type = _EQUAL;
            $$->v1._equality_expr = $1;
            $$->v2 = $3;
          }
	| equality_expr NE_OP relational_expr
          {
            $$ = (struct equality_expr *) malloc(sizeof(struct equality_expr));
            $$->type = _NEQUAL;
            $$->v1._equality_expr = $1;
            $$->v2 = $3;
          }
	;

and_expr
	: equality_expr
          {
            $$ = (struct and_expr *) malloc(sizeof(struct and_expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| and_expr '&' equality_expr
          {
            $$ = (struct and_expr *) malloc(sizeof(struct and_expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

exclusive_or_expr
	: and_expr
          {
            $$ = (struct exclusive_or_expr *) malloc(sizeof(struct exclusive_or_expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| exclusive_or_expr '^' and_expr
          {
            $$ = (struct exclusive_or_expr *) malloc(sizeof(struct exclusive_or_expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

inclusive_or_expr
	: exclusive_or_expr
          {
            $$ = (struct inclusive_or_expr *) malloc(sizeof(struct inclusive_or_expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| inclusive_or_expr '|' exclusive_or_expr
          {
            $$ = (struct inclusive_or_expr *) malloc(sizeof(struct inclusive_or_expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

logical_and_expr
	: inclusive_or_expr
          {
            $$ = (struct logical_and_expr *) malloc(sizeof(struct logical_and_expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| logical_and_expr AND_OP inclusive_or_expr
          {
            $$ = (struct logical_and_expr *) malloc(sizeof(struct logical_and_expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

logical_or_expr
	: logical_and_expr
          {
            $$ = (struct logical_or_expr *) malloc(sizeof(struct logical_or_expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| logical_or_expr OR_OP logical_and_expr
          {
            $$ = (struct logical_or_expr *) malloc(sizeof(struct logical_or_expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

conditional_expr
	: logical_or_expr
          {
            $$ = (struct conditional_expr *) malloc(sizeof(struct conditional_expr));
            $$->end = 1;
            $$->v1 = $1;
          }
	| logical_or_expr '?' logical_or_expr ':' conditional_expr
          {
            $$ = (struct conditional_expr *) malloc(sizeof(struct conditional_expr));
            $$->end = 1;
            $$->v1 = $1;
            $$->v2 = $3;
            $$->v3 = $5;
          }
	;

assignment_expr
	: conditional_expr
          {
            $$ = (struct assignment_expr *) malloc(sizeof(struct assignment_expr));
            $$->type = _CONDITIONAL_EXPR;
            $$->v1._conditional_expr = $1;
          }
	| unary_expr assignment_operator assignment_expr
          {
            $$ = (struct assignment_expr *) malloc(sizeof(struct assignment_expr));
            $$->type = _ASSIGNMENT;
            $$->v1._unary_expr = $1;
            $$->v2 = $2;
            $$->v3 = $3;
          }
	;

assignment_operator
	: '='
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _ASSIGN;
          }
	| MUL_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _MUL_ASSIGN;
          }
	| DIV_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _DIV_ASSIGN;
          }
	| MOD_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _MOD_ASSIGN;
          }
	| ADD_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _ADD_ASSIGN;
          }
	| SUB_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _SUB_ASSIGN;
          }
	| LEFT_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _LEFT_ASSIGN;
          }
	| RIGHT_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _RIGHT_ASSIGN;
          }
	| AND_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _AND_ASSIGN;
          }
	| XOR_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _XOR_ASSIGN;
          }
	| OR_ASSIGN
          {
            $$ = (struct assignment_operator *) malloc(sizeof(struct assignment_operator));
            $$->type = _OR_ASSIGN;
          }
	;

expr
	: assignment_expr
          {
            $$ = (struct expr *) malloc(sizeof(struct expr));
            $$->end = 1;
            $$->v2 = $1;
          }
	| expr ',' assignment_expr
          {
            $$ = (struct expr *) malloc(sizeof(struct expr));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

constant_expr
	: conditional_expr
	;

declaration
	: declaration_specifiers ';'
          {
            $$ = (struct declaration *) malloc(sizeof(struct declaration));
            $$->has_init_declarator_list = 0;
            $$->v1 = $1;
          }
	| declaration_specifiers init_declarator_list ';'
          {
            $$ = (struct declaration *) malloc(sizeof(struct declaration));
            $$->has_init_declarator_list = 1;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

declaration_specifiers
	: storage_class_specifier
          {
            $$ = (struct declaration_specifiers *) malloc(sizeof(struct declaration_specifiers));
            $$->type = _STORAGE_CLASS_SPECIFIER;
            $$->end = 1;
            $$->v1._storage_class_specifier = $1;
          }
	| storage_class_specifier declaration_specifiers
          {
            $$ = (struct declaration_specifiers *) malloc(sizeof(struct declaration_specifiers));
            $$->type = _STORAGE_CLASS_SPECIFIER;
            $$->end = 0;
            $$->v1._storage_class_specifier = $1;
            $$->v2 = $2;
          }
	| type_specifier
          {
            $$ = (struct declaration_specifiers *) malloc(sizeof(struct declaration_specifiers));
            $$->type = _TYPE_SPECIFIER;
            $$->end = 1;
            $$->v1._type_specifier = $1;
          }
	| type_specifier declaration_specifiers
          {
            $$ = (struct declaration_specifiers *) malloc(sizeof(struct declaration_specifiers));
            $$->type = _TYPE_SPECIFIER;
            $$->end = 0;
            $$->v1._type_specifier = $1;
            $$->v2 = $2;
          }
	;

init_declarator_list
	: init_declarator
          {
            $$ = (struct init_declarator_list *) malloc(sizeof(struct init_declarator_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| init_declarator_list ',' init_declarator
          {
            $$ = (struct init_declarator_list *) malloc(sizeof(struct init_declarator_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

init_declarator
	: declarator
          {
            $$ = (struct init_declarator *) malloc(sizeof(struct init_declarator));
            $$->assign = 0;
            $$->v1 = $1;
          }
	| declarator '=' initializer
          {
            $$ = (struct init_declarator *) malloc(sizeof(struct init_declarator));
            $$->assign = 1;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

storage_class_specifier
	: TYPEDEF
          {
            $$ = (struct storage_class_specifier *) malloc(sizeof(struct storage_class_specifier));
            $$->type = _TYPEDEF;
          }
	| EXTERN
          {
            $$ = (struct storage_class_specifier *) malloc(sizeof(struct storage_class_specifier));
            $$->type = _EXTERN;
          }
	| STATIC
          {
            $$ = (struct storage_class_specifier *) malloc(sizeof(struct storage_class_specifier));
            $$->type = _STATIC;
          }
	| AUTO
          {
            $$ = (struct storage_class_specifier *) malloc(sizeof(struct storage_class_specifier));
            $$->type = _AUTO;
          }
	| REGISTER
          {
            $$ = (struct storage_class_specifier *) malloc(sizeof(struct storage_class_specifier));
            $$->type = _REGISTER;
          }
	;

type_specifier
	: CHAR
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _CHAR;
          }
	| SHORT
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _SHORT;
          }
	| INT
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _INT;
          }
	| LONG
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _LONG;
          }
	| SIGNED
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _SIGNED;
          }
	| UNSIGNED
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _UNSIGNED;
          }
	| FLOAT
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _FLOAT;
          }
	| DOUBLE
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _DOUBLE;
          }
	| CONST
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _CONST;
          }
	| VOLATILE
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _VOLATILE;
          }
	| VOID
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _VOID;
          }
	| struct_or_union_specifier
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _STRUCT_OR_UNION_SPECIFIER;
            $$->v._struct_or_union_specifier = $1;
          }
	| enum_specifier
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _ENUM_SPECIFIER;
            $$->v._enum_specifier = $1;
          }
	| TYPE_NAME
          {
            $$ = (struct type_specifier *) malloc(sizeof(struct type_specifier));
            $$->type = _TYPE_NAME;
          }
	;

struct_or_union_specifier
	: struct_or_union identifier '{' struct_declaration_list '}'
          {
            $$ = (struct struct_or_union_specifier *) malloc(sizeof(struct struct_or_union_specifier));
            $$->has_identifier = 1;
            $$->has_struct_declaration_list = 1;
            $$->v1 = $1;
            $$->v2 = $2;
            $$->v3 = $4;
          }
	| struct_or_union '{' struct_declaration_list '}'
          {
            $$ = (struct struct_or_union_specifier *) malloc(sizeof(struct struct_or_union_specifier));
            $$->has_identifier = 0;
            $$->has_struct_declaration_list = 1;
            $$->v1 = $1;
            $$->v3 = $3;
          }
	| struct_or_union identifier
          {
            $$ = (struct struct_or_union_specifier *) malloc(sizeof(struct struct_or_union_specifier));
            $$->has_identifier = 1;
            $$->has_struct_declaration_list = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

struct_or_union
	: STRUCT
          {
            $$ = (struct struct_or_union *) malloc(sizeof(struct struct_or_union));
            $$->type = _STRUCT;
          }
	| UNION
          {
            $$ = (struct struct_or_union *) malloc(sizeof(struct struct_or_union));
            $$->type = _UNION;
          }
	;

struct_declaration_list
	: struct_declaration
          {
            $$ = (struct struct_declaration_list *) malloc(sizeof(struct struct_declaration_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| struct_declaration_list struct_declaration
          {
            $$ = (struct struct_declaration_list *) malloc(sizeof(struct struct_declaration_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

struct_declaration
	: type_specifier_list struct_declarator_list ';'
          {
            $$ = (struct struct_declaration *) malloc(sizeof(struct struct_declaration));
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

struct_declarator_list
	: struct_declarator
          {
            $$ = (struct struct_declarator_list *) malloc(sizeof(struct struct_declarator_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| struct_declarator_list ',' struct_declarator
          {
            $$ = (struct struct_declarator_list *) malloc(sizeof(struct struct_declarator_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

struct_declarator
	: declarator
          {
            $$ = (struct struct_declarator *) malloc(sizeof(struct struct_declarator));
            $$->has_declarator = 1;
            $$->has_bitwidth = 0;
            $$->v1 = $1;
          }
	| ':' constant_expr
          {
            $$ = (struct struct_declarator *) malloc(sizeof(struct struct_declarator));
            $$->has_declarator = 0;
            $$->has_bitwidth = 1;
            $$->v2 = $2;
          }
	| declarator ':' constant_expr
          {
            $$ = (struct struct_declarator *) malloc(sizeof(struct struct_declarator));
            $$->has_declarator = 1;
            $$->has_bitwidth = 1;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
          {
            $$ = (struct enum_specifier *) malloc(sizeof(struct enum_specifier));
            $$->has_identifier = 0;
            $$->has_enumerator_list = 1;
            $$->v2 = $3;
          }
	| ENUM identifier '{' enumerator_list '}'
          {
            $$ = (struct enum_specifier *) malloc(sizeof(struct enum_specifier));
            $$->has_identifier = 1;
            $$->has_enumerator_list = 1;
            $$->v1 = $2;
            $$->v2 = $4;
          }
	| ENUM identifier
          {
            $$ = (struct enum_specifier *) malloc(sizeof(struct enum_specifier));
            $$->has_identifier = 1;
            $$->has_enumerator_list = 0;
            $$->v1 = $2;
          }
	;

enumerator_list
	: enumerator
          {
            $$ = (struct enumerator_list *) malloc(sizeof(struct enumerator_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| enumerator_list ',' enumerator
          {
            $$ = (struct enumerator_list *) malloc(sizeof(struct enumerator_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

enumerator
	: identifier
          {
            $$ = (struct enumerator *) malloc(sizeof(struct enumerator));
            $$->assign = 0;
            $$->v1 = $1;
          }
	| identifier '=' constant_expr
          {
            $$ = (struct enumerator *) malloc(sizeof(struct enumerator));
            $$->assign = 1;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

declarator
	: declarator2
          {
            $$ = (struct declarator *) malloc(sizeof(struct declarator));
            $$->pointer = 0;
            $$->v2 = $1;
          }
	| pointer declarator2
          {
            $$ = (struct declarator *) malloc(sizeof(struct declarator));
            $$->pointer = 1;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

declarator2
	: identifier
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _IDENTIFIER;
            $$->v1._identifier = $1;
          }
	| '(' declarator ')'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _DECLARATOR;
            $$->v1._declarator = $2;
          }
	| declarator2 '[' ']'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _SIMPLE_ARRAY;
            $$->v1._declarator2 = $1;
          }
	| declarator2 '[' constant_expr ']'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _ARRAY;
            $$->v1._declarator2 = $1;
            $$->v2._conditional_expr = $3;
          }
	| declarator2 '(' ')'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _SIMPLE_FUNC;
            $$->v1._declarator2 = $1;
          }
	| declarator2 '(' parameter_type_list ')'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _FUNC_BY_TYPE;
            $$->v1._declarator2 = $1;
            $$->v2._parameter_type_list = $3;
          }
	| declarator2 '(' parameter_identifier_list ')'
          {
            $$ = (struct declarator2 *) malloc(sizeof(struct declarator2));
            $$->type = _FUNC_OLD_STYLE;
            $$->v1._declarator2 = $1;
            $$->v2._parameter_identifier_list = $3;
          }
	;

pointer
	: '*'
          {
            $$ = (struct pointer *) malloc(sizeof(struct pointer));
            $$->has_type_specifier_list = 0;
            $$->end = 1;
          }
	| '*' type_specifier_list
          {
            $$ = (struct pointer *) malloc(sizeof(struct pointer));
            $$->has_type_specifier_list = 1;
            $$->end = 1;
            $$->v1 = $2;
          }
	| '*' pointer
          {
            $$ = (struct pointer *) malloc(sizeof(struct pointer));
            $$->has_type_specifier_list = 0;
            $$->end = 0;
            $$->v2 = $2;
          }
	| '*' type_specifier_list pointer
          {
            $$ = (struct pointer *) malloc(sizeof(struct pointer));
            $$->has_type_specifier_list = 1;
            $$->end = 0;
            $$->v1 = $2;
            $$->v2 = $3;
          }
	;

type_specifier_list
	: type_specifier
          {
            $$ = (struct type_specifier_list *) malloc(sizeof(struct type_specifier_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| type_specifier_list type_specifier
          {
            $$ = (struct type_specifier_list *) malloc(sizeof(struct type_specifier_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

parameter_identifier_list
	: identifier_list
          {
            $$ = (struct parameter_identifier_list *) malloc(sizeof(struct parameter_identifier_list));
            $$->varargs = 0;
            $$->v = $1;
          }
	| identifier_list ',' ELIPSIS
          {
            $$ = (struct parameter_identifier_list *) malloc(sizeof(struct parameter_identifier_list));
            $$->varargs = 1;
            $$->v = $1;
          }
	;

identifier_list
	: identifier
          {
            $$ = (struct identifier_list *) malloc(sizeof(struct identifier_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| identifier_list ',' identifier
          {
            $$ = (struct identifier_list *) malloc(sizeof(struct identifier_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

parameter_type_list
	: parameter_list
          {
            $$ = (struct parameter_type_list *) malloc(sizeof(struct parameter_type_list));
            $$->varargs = 0;
            $$->v = $1;
          }
	| parameter_list ',' ELIPSIS
          {
            $$ = (struct parameter_type_list *) malloc(sizeof(struct parameter_type_list));
            $$->varargs = 1;
            $$->v = $1;
          }
	;

parameter_list
	: parameter_declaration
          {
            $$ = (struct parameter_list *) malloc(sizeof(struct parameter_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| parameter_list ',' parameter_declaration
          {
            $$ = (struct parameter_list *) malloc(sizeof(struct parameter_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

parameter_declaration
	: type_specifier_list declarator
          {
            $$ = (struct parameter_declaration *) malloc(sizeof(struct parameter_declaration));
            $$->type = _DECLARATION;
            $$->v1._type_specifier_list = $1;
            $$->v2 = $2;
          }
	| type_name
          {
            $$ = (struct parameter_declaration *) malloc(sizeof(struct parameter_declaration));
            $$->type = _TYPE_NAME;
            $$->v1._type_name = $1;
          }
	;

type_name
	: type_specifier_list
          {
            $$ = (struct type_name *) malloc(sizeof(struct type_name));
            $$->has_declarator = 0;
            $$->v1 = $1;
          }
	| type_specifier_list abstract_declarator
          {
            $$ = (struct type_name *) malloc(sizeof(struct type_name));
            $$->has_declarator = 1;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

abstract_declarator
	: pointer
          {
            $$ = (struct abstract_declarator *) malloc(sizeof(struct abstract_declarator));
            $$->has_pointer = 1;
            $$->has_abstract_declarator2 = 0;
            $$->v1 = $1;
          }
	| abstract_declarator2
          {
            $$ = (struct abstract_declarator *) malloc(sizeof(struct abstract_declarator));
            $$->has_pointer = 0;
            $$->has_abstract_declarator2 = 1;
            $$->v2 = $1;
          }
	| pointer abstract_declarator2
          {
            $$ = (struct abstract_declarator *) malloc(sizeof(struct abstract_declarator));
            $$->has_pointer = 1;
            $$->has_abstract_declarator2 = 1;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

abstract_declarator2
	: '(' abstract_declarator ')'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _ABSTRACT_DECLARATOR;
            $$->end = 1;
            $$->v1._abstract_declarator = $2;
          }
	| '[' ']'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _SIMPLE_ARRAY;
            $$->end = 1;
          }
	| '[' constant_expr ']'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _ARRAY;
            $$->end = 1;
            $$->v2._conditional_expr = $2;
          }
	| abstract_declarator2 '[' ']'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _SIMPLE_ARRAY;
            $$->end = 0;
            $$->v1._abstract_declarator2 = $1;
          }
	| abstract_declarator2 '[' constant_expr ']'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _ARRAY;
            $$->end = 0;
            $$->v1._abstract_declarator2 = $1;
            $$->v2._conditional_expr = $3;
          }
	| '(' ')'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _SIMPLE_FUNC;
            $$->end = 1;
          }
	| '(' parameter_type_list ')'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _FUNC_BY_TYPE;
            $$->end = 1;
            $$->v2._parameter_type_list = $2;
          }
	| abstract_declarator2 '(' ')'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _SIMPLE_FUNC;
            $$->end = 0;
            $$->v1._abstract_declarator2 = $1;
          }
	| abstract_declarator2 '(' parameter_type_list ')'
          {
            $$ = (struct abstract_declarator2 *) malloc(sizeof(struct abstract_declarator2));
            $$->type = _FUNC_BY_TYPE;
            $$->end = 0;
            $$->v1._abstract_declarator2 = $1;
            $$->v2._parameter_type_list = $3;
          }
	;

/* FIXME: what does that trailing , mean, and how should it be in the AST? */
initializer
	: assignment_expr
          {
            $$ = (struct initializer *) malloc(sizeof(struct initializer));
            $$->type = _ASSIGNMENT_EXPR;
            $$->v._assignment_expr = $1;
          }
	| '{' initializer_list '}'
          {
            $$ = (struct initializer *) malloc(sizeof(struct initializer));
            $$->type = _INITIALIZER_LIST;
            $$->v._initializer_list = $2;
          }
	| '{' initializer_list ',' '}'
          {
            $$ = (struct initializer *) malloc(sizeof(struct initializer));
            $$->type = _INITIALIZER_LIST;
            $$->v._initializer_list = $2;
          }
	;

initializer_list
	: initializer
          {
            $$ = (struct initializer_list *) malloc(sizeof(struct initializer_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| initializer_list ',' initializer
          {
            $$ = (struct initializer_list *) malloc(sizeof(struct initializer_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $3;
          }
	;

statement
	: labeled_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _LABELED_STATEMENT;
            $$->v._labeled_statement = $1;
          }
	| compound_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _COMPOUND_STATEMENT;
            $$->v._compound_statement = $1;
          }
	| expression_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _EXPRESSION_STATEMENT;
            $$->v._expression_statement = $1;
          }
	| selection_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _SELECTION_STATEMENT;
            $$->v._selection_statement = $1;
          }
	| iteration_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _ITERATION_STATEMENT;
            $$->v._iteration_statement = $1;
          }
	| jump_statement
          {
            $$ = (struct statement *) malloc(sizeof(struct statement));
            $$->type = _JUMP_STATEMENT;
            $$->v._jump_statement = $1;
          }
	;

labeled_statement
	: identifier ':' statement
          {
            $$ = (struct labeled_statement *) malloc(sizeof(struct labeled_statement));
            $$->type = _IDENTIFIER;
            $$->v1._identifier = $1;
            $$->v2 = $3;
          }
	| CASE constant_expr ':' statement
          {
            $$ = (struct labeled_statement *) malloc(sizeof(struct labeled_statement));
            $$->type = _CASE;
            $$->v1._conditional_expr = $2;
            $$->v2 = $4;
          }
	| DEFAULT ':' statement
          {
            $$ = (struct labeled_statement *) malloc(sizeof(struct labeled_statement));
            $$->type = _DEFAULT;
            $$->v2 = $3;
          }
	;

compound_statement
	: '{' '}'
          {
            $$ = (struct compound_statement *) malloc(sizeof(struct compound_statement));
            $$->has_declaration_list = 0;
            $$->has_statement_list = 0;
          }
	| '{' statement_list '}'
          {
            $$ = (struct compound_statement *) malloc(sizeof(struct compound_statement));
            $$->has_declaration_list = 0;
            $$->has_statement_list = 1;
            $$->v2 = $2;
          }
	| '{' declaration_list '}'
          {
            $$ = (struct compound_statement *) malloc(sizeof(struct compound_statement));
            $$->has_declaration_list = 1;
            $$->has_statement_list = 0;
            $$->v1 = $2;
          }
	| '{' declaration_list statement_list '}'
          {
            $$ = (struct compound_statement *) malloc(sizeof(struct compound_statement));
            $$->has_declaration_list = 1;
            $$->has_statement_list = 1;
            $$->v1 = $2;
            $$->v2 = $3;
          }
	;

declaration_list
	: declaration
          {
            $$ = (struct declaration_list *) malloc(sizeof(struct declaration_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| declaration_list declaration
          {
            $$ = (struct declaration_list *) malloc(sizeof(struct declaration_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

statement_list
	: statement
          {
            $$ = (struct statement_list *) malloc(sizeof(struct statement_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| statement_list statement
          {
            $$ = (struct statement_list *) malloc(sizeof(struct statement_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

expression_statement
	: ';'
          {
            $$ = (struct expression_statement *) malloc(sizeof(struct expression_statement));
            $$->has_expr = 0;
          }
	| expr ';'
          {
            $$ = (struct expression_statement *) malloc(sizeof(struct expression_statement));
            $$->has_expr = 1;
            $$->v = $1;
          }
	;

selection_statement
	: IF '(' expr ')' statement
          {
            $$ = (struct selection_statement *) malloc(sizeof(struct selection_statement));
            $$->type = _IF;
            $$->v1 = $3;
            $$->v2 = $5;
          }
	| IF '(' expr ')' statement ELSE statement
          {
            $$ = (struct selection_statement *) malloc(sizeof(struct selection_statement));
            $$->type = _IF_ELSE;
            $$->v1 = $3;
            $$->v2 = $5;
            $$->v3 = $7;
          }
	| SWITCH '(' expr ')' statement
          {
            $$ = (struct selection_statement *) malloc(sizeof(struct selection_statement));
            $$->type = _SWITCH;
            $$->v1 = $3;
            $$->v2 = $5;
          }
	;

iteration_statement
	: WHILE '(' expr ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _WHILE;
            $$->v1 = $3;
            $$->v4 = $5;
          }
	| DO statement WHILE '(' expr ')' ';'
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _DO_WHILE;
            $$->v1 = $5;
            $$->v4 = $2;
          }
	| FOR '(' ';' ';' ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 0;
            $$->has_condition = 0;
            $$->has_post = 0;
            $$->v4 = $6;
          }
	| FOR '(' ';' ';' expr ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 0;
            $$->has_condition = 0;
            $$->has_post = 1;
            $$->v3 = $5;
            $$->v4 = $7;
          }
	| FOR '(' ';' expr ';' ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 0;
            $$->has_condition = 1;
            $$->has_post = 0;
            $$->v2 = $4;
            $$->v4 = $7;
          }
	| FOR '(' ';' expr ';' expr ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 0;
            $$->has_condition = 1;
            $$->has_post = 1;
            $$->v2 = $4;
            $$->v3 = $6;
            $$->v4 = $8;
          }
	| FOR '(' expr ';' ';' ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 1;
            $$->has_condition = 0;
            $$->has_post = 0;
            $$->v1 = $3;
            $$->v4 = $7;
          }
	| FOR '(' expr ';' ';' expr ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 1;
            $$->has_condition = 0;
            $$->has_post = 1;
            $$->v1 = $3;
            $$->v3 = $6;
            $$->v4 = $8;
          }
	| FOR '(' expr ';' expr ';' ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 1;
            $$->has_condition = 1;
            $$->has_post = 0;
            $$->v1 = $3;
            $$->v2 = $5;
            $$->v4 = $8;
          }
	| FOR '(' expr ';' expr ';' expr ')' statement
          {
            $$ = (struct iteration_statement *) malloc(sizeof(struct iteration_statement));
            $$->type = _FOR;
            $$->has_initializer = 1;
            $$->has_condition = 1;
            $$->has_post = 1;
            $$->v1 = $3;
            $$->v2 = $5;
            $$->v3 = $7;
            $$->v4 = $9;
          }
	;

jump_statement
	: GOTO identifier ';'
          {
            $$ = (struct jump_statement *) malloc(sizeof(struct jump_statement));
            $$->type = _GOTO;
            $$->v._identifier = $2;
          }
	| CONTINUE ';'
          {
            $$ = (struct jump_statement *) malloc(sizeof(struct jump_statement));
            $$->type = _CONTINUE;
          }
	| BREAK ';'
          {
            $$ = (struct jump_statement *) malloc(sizeof(struct jump_statement));
            $$->type = _BREAK;
          }
	| RETURN ';'
          {
            $$ = (struct jump_statement *) malloc(sizeof(struct jump_statement));
            $$->type = _RETURN;
            $$->has_expr = 0;
          }
	| RETURN expr ';'
          {
            $$ = (struct jump_statement *) malloc(sizeof(struct jump_statement));
            $$->type = _RETURN;
            $$->has_expr = 1;
            $$->v._expr = $2;
          }
	;

external_definition_list
	: external_definition
          {
            $$ = (struct external_definition_list *) malloc(sizeof(struct external_definition_list));
            $$->end = 1;
            $$->v2 = $1;
          }
	| external_definition_list external_definition
          {
            $$ = (struct external_definition_list *) malloc(sizeof(struct external_definition_list));
            $$->end = 0;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

file
        : external_definition_list
          {
            ast_root = $$ = (struct file *) malloc(sizeof(struct file));
            $$->v = $1;
          }
        ;

external_definition
	: function_definition
          {
            $$ = (struct external_definition *) malloc(sizeof(struct external_definition));
            $$->type = _FUNCTION_DEFINITION;
            $$->v._function_definition = $1;
          }
	| declaration
          {
            $$ = (struct external_definition *) malloc(sizeof(struct external_definition));
            $$->type = _DECLARATION;
            $$->v._declaration = $1;
          }
	;

function_definition
	: declarator function_body
          {
            $$ = (struct function_definition *) malloc(sizeof(struct function_definition));
            $$->has_declaration_specifiers = 0;
            $$->v2 = $1;
            $$->v3 = $2;
          }
	| declaration_specifiers declarator function_body
          {
            $$ = (struct function_definition *) malloc(sizeof(struct function_definition));
            $$->has_declaration_specifiers = 1;
            $$->v1 = $1;
            $$->v2 = $2;
            $$->v3 = $3;
          }
	;

function_body
	: compound_statement
          {
            $$ = (struct function_body *) malloc(sizeof(struct function_body));
            $$->has_declaration_list = 0;
            $$->v2 = $1;
          }
	| declaration_list compound_statement
          {
            $$ = (struct function_body *) malloc(sizeof(struct function_body));
            $$->has_declaration_list = 1;
            $$->v1 = $1;
            $$->v2 = $2;
          }
	;

identifier
	: IDENTIFIER
          {
            $$ = (struct identifier *) malloc(sizeof(struct identifier));
            $$->v = $1;
          }
	;
%%

#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
