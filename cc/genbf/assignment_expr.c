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

int genbf_assignment_expr(struct assignment_expr *a, int lval, struct type **t)
{
    int i, d;
    struct type *st;
    
    switch (a->type) {
        case _CONDITIONAL_EXPR:
            return genbf_conditional_expr(a->v1._conditional_expr, lval, t);
            break;
            
        case _ASSIGNMENT:
            if (lval)
                ERROR("assignment_expr", "Invalid l-value.");
            
            /* get the location as an lval (this will return the depth of the
             * variable in the stack, or -1 and push a pointer to the stack) */
            d = genbf_unary_expr(a->v1._unary_expr, 1, &st);
            if (d == -1) {
                struct type *ttype;
                
                /* generate the value and put it in the carry */
                genbf_assignment_expr(a->v3, 0, NULL);
                printf("[<+<+>>-]<<[>>+<<-]>>");
                
                /* then swap-n-pop (essentially, we're leaving the value on
                   top, even though there's one below it) */
                ttype = curvar->type;
                curvar->type = curvar->next->type;
                curvar->next->type = ttype;
                popVar();
                
                /* put this var in walk */
                printf("[>>>+<<<-]");
                
                /* get to the proper location */
                STACK_PTR_TO_POS_CARRY;
                
                /* set it to the carry */
                printf("[-]>>>>[<<<<+>>>>-]"
                       "<<[>>>>>]<<");
                
                /* then move the value into this slot to pass down */
                fflush(stdout);
                return 0;
            }
            
            /* FIXME: only primitive (=) assignments :) */
            if (a->v2->type != _ASSIGN)
                ERROR("assignment_expr", "Only primitive assignments are supported thusfar.");
            
            genbf_assignment_expr(a->v3, 0, NULL);
            /* this put one more on the stack, so our depth is greater */
            d += curvar->width;
            
            /* carry this value ... */
            printf("[>>>+>+<<<<-]>>>[<<<+>>>-]>");
            
            /* the proper distance */
            printf("[");
            for (i = 0; i < d; i++)
                printf("<<<<<");
            printf("+");
            for (i = 0; i < d; i++)
                printf(">>>>>");
            printf("-]");
            for (i = 0; i < d; i++)
                printf("<<<<<");
            /* then put it in place */
            printf("<<<<[-]>>>>[<<<<+>>>>-]<<<<");
            /* and come back */
            for (i = 0; i < d; i++)
                printf(">>>>>");
            
            fflush(stdout);
            
            /* leave the value of the expression to pass up */
            break;
    }
}

char *genbf_assignment_expr_get_primary(int type, struct assignment_expr *a)
{
    if (a->type != _CONDITIONAL_EXPR) return NULL;
    return genbf_conditional_expr_get_primary(type, a->v1._conditional_expr);
}
