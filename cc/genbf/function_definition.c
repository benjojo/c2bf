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

#include "../genbf.h"
#include "generator.h"

void genbf_function_definition(struct function_definition *a)
{
    struct declarator2 *decla, *declb;
    
    /* FIXME: this should store a list of declared functions and refer to that
     * for function calls */
    
    /* the tree here should look like this for a standard definition:
       -function_definition
       |-declarator (v2) (guaranteed)
       ||
       ||-declarator2 (v2) (guaranteed)
       |||(type must be _SIMPLE_FUNC or _FUNC_BY_TYPE)
       |||
       |||-declarator2 (v1._declarator2)
       ||||(type must be _IDENTIFIER)
       ||||
       ||||-identifier (v1._identifier)
       |||||v is the function name
       |||
       |||-parameter_type_list (v2._parameter_type_list) (_FUNC_BY_TYPE)
       ||||these must be pushed to stack
       |
       |-function_body (v3)
       ||(has_declaration_list must be 0)
       ||
       ||-compound_statement (v2)
       
       or like this for an olde-style definition (not yet supported):
       -function_definition
       |-declarator (v2) (guaranteed)
       ||
       ||-declarator2 (v2) (guaranteed)
       |||(type must be _FUNC_OLD_STYLE)
       |||
       |||-declarator2 (v1._declarator2)
       ||||(type must be _IDENTIFIER)
       ||||
       ||||-identifier (v1._identifier)
       |||||v is the function name
       |||
       |||-parameter_identifier_list (v2._parameter_identifier_list) (_FUNC_OLD_STYLE)
       ||||these must correspond to the declaration_list below
       |
       |-function_body (v3)
       ||(has_declaration_list must be 1)
       ||
       ||-declaration_list (v1)
       |||these must be pushed onto the stack
       ||
       ||-compound_statement (v2)
       */
    
    decla = a->v2->v2;
    /* decla must have type _SIMPLE_FUNC or _FUNC_BY_TYPE */
    if (decla->type != _SIMPLE_FUNC && decla->type != _FUNC_BY_TYPE)
        ERROR("function_definition", "Invalid function definition!\n");
    
    declb = decla->v1._declarator2;
    /* declb must have type _IDENTIFIER */
    if (declb->type != _IDENTIFIER)
        ERROR("function_definition", "Invalid function definition!\n");
    
    /* now we can start the block */
    pushNamedBlock(declb->v1._identifier->v);
    outBlock();
    
    /* and push all the parameter_identifier_list variables on */
    if (decla->type != _SIMPLE_FUNC)
        genbf_parameter_type_list(decla->v2._parameter_type_list);
    
    if (a->v3->has_declaration_list)
        ERROR("function_definition", "Invalid function definition!\n");
    
    /* FIXME: this should transmit down in some way whether the function needs
     * to return */
    genbf_compound_statement(a->v3->v2);
    
    /* now we need to pop the block */
    popNamedBlock();
    
    /* now the stack should look like this:
     * {return address}{return code}
     * but the return code is actually above the top of the stack
     * so, move the return address into the walk cell, and use it to set the
     * return */
    printf("[<<+>>-]>>>>>[<<<<<+>>>>>-]"
           "<<<<<<<<[>[<<<<<+>>>>>-]<<<<<<]"
           ">[>>>>>+<<<<<-]>>>>>"
           "[[>>>>>+<<<<<-]>>>>>-]"
           "<<<+"
           ">>[>>>>>]<<");
    fflush(stdout);
}
