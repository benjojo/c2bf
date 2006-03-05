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

void genbf_iteration_statement(struct iteration_statement *a)
{
    char *pblockname;
    int pblocknum;
    
    if (a->type == _DO_WHILE) {
        UNIMPL("iteration_statement");
        exit(1);
    }
    
    /* initializer if applicable */
    if (a->type == _FOR && a->has_initializer) {
        /* just run this now */
        genbf_expr(a->v1, 0, NULL);
        popVar();
    }
    
    pblockname = curblock->name;
    pblocknum = curblock->num;
    
    /* now, the condition (1st time) */
    if (a->type != _FOR || a->has_condition) {
        if (a->type == _FOR) {
            genbf_expr(a->v2, 0, NULL);
        } else {
            genbf_expr(a->v1, 0, NULL);
        }
    } else {
        struct type *t;
        
        /* just invent one */
        pushTempVar(1);
        NEW(t, struct type);
        t->next = NULL;
        t->basic_type = TYPE_INT;
        t->array = 0;
        t->size = 1;
        BF_PUSH;
        printf("[-]+");
        
        curvar->type = t;
    }
    
    /* get an "if-not" as well */
    printf("[>>>+>+<<<<-]>>>>[<<<<+>>>>-]+"
           "<[[-]>-<<<<(%s!%d)>>>]"
           ">[-<<<<(%s!%d)>>>>]"
           "<<<<",
           pblockname, pblocknum + 1,
           pblockname, pblocknum + 2);
    
    popVar();
    
    /* now push on the for's subblock */
    pushSubBlock(0);
    outBlock();
    
    /* and the for's content */
    genbf_statement(a->v4);
    
    /* this follows the other content */
    if (a->type == _FOR && a->has_post) {
        genbf_expr(a->v3, 0, NULL);
        popVar();
    }
    
    /* now, the condition (2nd time) */
    if (a->type != _FOR || a->has_condition) {
        if (a->type == _FOR) {
            genbf_expr(a->v2, 0, NULL);
        } else {
            genbf_expr(a->v1, 0, NULL);
        }
    } else {
        struct type *t;
        
        /* just invent one */
        pushTempVar(1);
        NEW(t, struct type);
        t->next = NULL;
        t->basic_type = TYPE_INT;
        t->array = 0;
        t->size = 1;
        BF_PUSH;
        printf("[-]+");
        
        curvar->type = t;
    }
    
    /* get an "if-not" as well */
    printf("[>>>+>+<<<<-]>>>>[<<<<+>>>>-]+"
           "<[[-]>-<<<<(%s!%d)>>>]"
           ">[-<<<<(%s!%d)>>>>]"
           "<<<<",
           pblockname, pblocknum + 1,
           pblockname, pblocknum + 2);
            
    popVar();
    
    /* pop off the for's block */
    popNamedBlock();
    pushBlock();
    curblock->num += 1;
    outBlock();
    
    /* now we're back to normal code */
    fflush(stdout);
}
