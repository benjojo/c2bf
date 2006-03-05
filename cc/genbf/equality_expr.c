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

int genbf_equality_expr(struct equality_expr *a, int lval, struct type **t)
{
    if (a->type == _RELATIONAL_EXPR) {
        return genbf_relational_expr(a->v1._relational_expr, lval, t);
    }
    
    if (lval)
        ERROR("equality_expr", "Invalid l-value.");
    
    genbf_equality_expr(a->v1._equality_expr, 0, NULL);
    genbf_relational_expr(a->v2, 0, NULL);
    switch (a->type) {
        case _EQUAL:
            printf("<<<<<[>>>>+<<<<-]+"
                   ">>>>>[<-<+>>-]"
                   "<<[>>+<<-]"
                   ">[<<<<->>>>[-]]>");
            break;
            
        case _NEQUAL:
            printf("<<<<<[>>>>+<<<<-]"
                   ">>>>>[<-<+>>-]"
                   "<<[>>+<<-]"
                   ">[<<<<+>>>>[-]]>");
            break;
    }
    
    popVar();
    fflush(stdout);
}

char *genbf_equality_expr_get_primary(int type, struct equality_expr *a)
{
    if (a->type != _RELATIONAL_EXPR) return NULL;
    return genbf_relational_expr_get_primary(type, a->v1._relational_expr);
}
