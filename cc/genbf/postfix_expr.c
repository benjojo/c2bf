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

int genbf_postfix_expr(struct postfix_expr *a, int lval, struct type **t)
{
    struct primary_expr *p_e;
    struct type *vt;
    char *f;
    int i, loc;
    
    switch (a->type) {
        case _PRIMARY_EXPR:
            return genbf_primary_expr(a->v1._primary_expr, lval, t);
            break;
            
        case _SIMPLE_FCALL:
        case _FCALL:
            if (lval)
                ERROR("postfix_expr", "Invalid l-value.");
            
            /* for builtins, the tree should look like this:
               -postfix_expr
               |
               |-postfix_expr (v1._postfix_expr)
               ||(type must be _PRIMARY_EXPR)
               ||
               ||-primary_expr (v1._primary_expr)
               |||(type must be _IDENTIFIER)
               |||
               |||-identifier (v1._identifier)
               ||||v is the name of the function to call
               |
               |-argument_expr_list (v2._argument_expr_list) (_FCALL)
               ||(this contains the arguments)
               */
            if (a->v1._postfix_expr->type != _PRIMARY_EXPR)
                ERROR("postfix_expr", "Invalid function call!");
            
            p_e = a->v1._postfix_expr->v1._primary_expr;
            if (p_e->type != _IDENTIFIER)
                ERROR("postfix_expr", "Invalid function call!");
            
            f = p_e->v._identifier->v;
            
#include "builtin_functions.c"
            else {
                int topop = 0;
                
                /* this is a real function call */
                pushCall(f);
                if (a->type == _FCALL) {
                    topop = genbf_argument_expr_list(a->v2._argument_expr_list);
                    for (; topop > 0; topop--)
                        ignoreVar(); /* these aren't ours */
                }
                outBlock();
            }
            break;
            
        case _ARRAY_REF:
            /* get the location of the array being referenced */
            genbf_postfix_expr(a->v1._postfix_expr, 0, NULL);
            
            /* the returned type will be one farther in vt
             * FIXME: this should verify that this is indeed an array*/
            if (lval)
                *t = curvar->type->next;
            
            genbf_expr(a->v2._expr, 0, NULL);
            
            /* add the new location */
            printf("[<<<<<");
            for (i = 0; i < curvar->type->size; i++)
                printf("++");
            printf(">>>>>-]");
            
            /* pop off this location */
            popVar();
            
            if (lval) {
                /* it's already on top, we're done */
                return -1;
            }
            
            /* deref */
            /* FIXME: this should do size checking */
            vt = curvar->type;
            curvar->type = curvar->type->next;
            free(vt);
            
            /* get there */
            printf("[>>>+<<<-]");
            STACK_PTR_TO_POS;
            
            /* and move the value up */
            printf("[>>>+>+<<<<-]" /* copied into W and C */
                   ">>>>[<<<<+>>>>-]" /* now in S and W */
                   "<<[>[>>>>>+<<<<<-]>>>>]" /* walk it over */
                   ">[<<<+>>>-]<<<" /* and drop it in */
                   );
            break;
            
        /* case _DOT:
            genbf_postfix_expr(a->v1._postfix_expr);
            SPC; printf(".\n");
            genbf_identifier(a->v2._identifier);
            break;
            
        case _PTR_OP:
            genbf_postfix_expr(a->v1._postfix_expr);
            SPC; printf("->\n");
            genbf_identifier(a->v2._identifier);
            break;
            
        case _INC:
            genbf_postfix_expr(a->v1._postfix_expr);
            SPC; printf("++\n");
            break;
            
        case _DEC:
            genbf_postfix_expr(a->v1._postfix_expr);
            SPC; printf("--\n");
            break; */
            
        default:
            UNIMPL("postfix_expr");
    }
}

char *genbf_postfix_expr_get_primary(int type, struct postfix_expr *a)
{
    if (a->type != _PRIMARY_EXPR) return NULL;
    return genbf_primary_expr_get_primary(type, a->v1._primary_expr);
}
