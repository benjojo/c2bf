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

#include <string.h>

#include "../genbf.h"
#include "generator.h"

void genbf_selection_statement(struct selection_statement *a)
{
    char *nname, *pblockname;
    int pblocknum;
    
    switch (a->type) {
        case _IF:
        case _IF_ELSE:
            genbf_expr(a->v1, 0, NULL);
            
            /* this will use a sneaky "subblock" format to make the jump-back
             * location predictable.  basically:
             * main:
             *  if (blah) {
             *   main!0!1
             *  } else {
             *   main!1!1
             *  }
             * main!2
             */
            
            /* get an "if-not" as well */
            pblockname = curblock->name;
            pblocknum = curblock->num;
            printf("[>>>+>+<<<<-]>>>>[<<<<+>>>>-]+"
                   "<[[-]>-<<<<(%s!%d)>>>]"
                   ">[-<<<<(%s!%d)>>>>]"
                   "<<<<",
                   pblockname, pblocknum + 1,
                   pblockname, pblocknum + 2);
            
            popVar();
            
            /* go on to the if-block */
            pushSubBlock(0);
            outBlock();
            
            genbf_statement(a->v2);
            
            /* this needs to continue to the proper place */
            if (a->type == _IF) {
                printf("(%s!%d)", pblockname, pblocknum + 2);
            } else {
                printf("(%s!%d)", pblockname, pblocknum + 3);
                
                /* this is an if/else, so now we need yet another subblock */
                popNamedBlock();
                pushSubBlock(1);
                outBlock();
                
                genbf_statement(a->v3);
                
                printf("(%s!%d)", pblockname, pblocknum + 3);
            }
            
            /* finally continue with our regularly scheduled programming */
            popNamedBlock();
            pushBlock();
            if (a->type == _IF) {
                curblock->num += 1;
            } else {
                curblock->num += 2;
            }
            outBlock();
            
            break;
            
        case _SWITCH:
            UNIMPL("selection_statement");
            /* SPC; printf("switch (\n");
            genbf_expr(a->v1);
            SPC; printf(")\n");
            genbf_statement(a->v2); */
            break;
    }
}
