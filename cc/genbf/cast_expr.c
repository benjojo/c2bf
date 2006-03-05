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

int genbf_cast_expr(struct cast_expr *a, int lval, struct type **t)
{
    switch (a->type) {
        case _UNARY_EXPR:
            return genbf_unary_expr(a->v1._unary_expr, lval, t);
            break;
            
        /* case _TYPE_CAST:
            SPC; printf("(\n");
            genbf_type_name(a->v1._type_name);
            SPC; printf(")\n");
            genbf_cast_expr(a->v2);
            break; */
            
        default:
            UNIMPL("cast_expr");
    }
}

char *genbf_cast_expr_get_primary(int type, struct cast_expr *a)
{
    if (a->type != _UNARY_EXPR) return NULL;
    return genbf_unary_expr_get_primary(type, a->v1._unary_expr);
}
