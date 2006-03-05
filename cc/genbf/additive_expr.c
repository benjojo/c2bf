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

int genbf_additive_expr(struct additive_expr *a, int lval, struct type **t)
{
    if (a->type == _MULTIPLICATIVE_EXPR) {
        return genbf_multiplicative_expr(a->v1._multiplicative_expr, lval, t);
    }
    
    if (lval)
        ERROR("additive_expr", "Invalid l-value.");
    
    /* generate the left and right side as temps, then do the add or subtract */
    genbf_additive_expr(a->v1._additive_expr, 0, NULL);
    genbf_multiplicative_expr(a->v2, 0, NULL);
    if (a->type == _ADD) {
        /* I should be on top of operand 2 */
        printf("[<<<<<+>>>>>-]");
    } else if (a->type == _SUBTRACT) {
        printf("[<<<<<->>>>>-]");
    }
    popVar();
    fflush(stdout);
}

char *genbf_additive_expr_get_primary(int type, struct additive_expr *a)
{
    if (a->type != _MULTIPLICATIVE_EXPR) return NULL;
    return genbf_multiplicative_expr_get_primary(type, a->v1._multiplicative_expr);
}
