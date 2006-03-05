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

int genbf_conditional_expr(struct conditional_expr *a, int lval, struct type **t)
{
    return genbf_logical_or_expr(a->v1, lval, t);
    if (!a->end) {
        /* FIXME: how should lval be handled here? */
        
        /* SPC; printf("?\n");
        genbf_logical_or_expr(a->v2);
        SPC; printf(":\n");
        genbf_conditional_expr(a->v3); */
        UNIMPL("conditional_expr");
    }
}

char *genbf_conditional_expr_get_primary(int type, struct conditional_expr *a)
{
    if (!a->end) return NULL;
    return genbf_logical_or_expr_get_primary(type, a->v1);
}
