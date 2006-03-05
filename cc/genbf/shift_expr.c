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

int genbf_shift_expr(struct shift_expr *a, int lval, struct type **t)
{
    switch (a->type) {
        case _ADDITIVE_EXPR:
            return genbf_additive_expr(a->v1._additive_expr, lval, t);
            break;
            
        /* case _LEFT_SHIFT:
            genbf_shift_expr(a->v1._shift_expr);
            SPC; printf("<<\n");
            genbf_additive_expr(a->v2);
            break;
            
        case _RIGHT_SHIFT:
            genbf_shift_expr(a->v1._shift_expr);
            SPC; printf(">>\n");
            genbf_additive_expr(a->v2);
            break; */
            
        default:
            UNIMPL("shift_expr");
    }
}

char *genbf_shift_expr_get_primary(int type, struct shift_expr *a)
{
    if (a->type != _ADDITIVE_EXPR) return NULL;
    return genbf_additive_expr_get_primary(type, a->v1._additive_expr);
}
