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

int genbf_multiplicative_expr(struct multiplicative_expr *a, int lval, struct type **t)
{
    switch (a->type) {
        case _CAST_EXPR:
            return genbf_cast_expr(a->v1._cast_expr, lval, t);
            break;
        
        case _MULTIPLY:
            if (lval)
                ERROR("multiplicative_expr", "Invalid l-value.");
            /* call the builtin function */
            pushCall("__builtin_mul");
            genbf_multiplicative_expr(a->v1._multiplicative_expr, 0, NULL);
            genbf_cast_expr(a->v2, 0, NULL);
            ignoreVar(); ignoreVar(); /* these are for the next function */
            outBlock();
            break;
            
        case _DIVIDE:
            if (lval)
                ERROR("multiplicative_expr", "Invalid l-value.");
            /* call the builtin function */
            pushCall("__builtin_div");
            genbf_multiplicative_expr(a->v1._multiplicative_expr, 0, NULL);
            genbf_cast_expr(a->v2, 0, NULL);
            ignoreVar(); ignoreVar(); /* these are for the next function */
            outBlock();
            break;
            
        case _MODULO:
            if (lval)
                ERROR("multiplicative_expr", "Invalid l-value.");
            /* call the builtin function */
            pushCall("__builtin_mod");
            genbf_multiplicative_expr(a->v1._multiplicative_expr, 0, NULL);
            genbf_cast_expr(a->v2, 0, NULL);
            ignoreVar(); ignoreVar(); /* these are for the next function */
            outBlock();
            break;
            
        /* case _MULTIPLY:
            genbf_multiplicative_expr(a->v1._multiplicative_expr);
            SPC; printf("*\n");
            genbf_cast_expr(a->v2);
            break;
            
        case _DIVIDE:
            genbf_multiplicative_expr(a->v1._multiplicative_expr);
            SPC; printf("/\n");
            genbf_cast_expr(a->v2);
            break;
            
        case _MODULO:
            genbf_multiplicative_expr(a->v1._multiplicative_expr);
            SPC; printf("%\n");
            genbf_cast_expr(a->v2);
            break; */
            
        default:
            UNIMPL("multiplicative_expr");
    }
}

char *genbf_multiplicative_expr_get_primary(int type, struct multiplicative_expr *a)
{
    if (a->type != _CAST_EXPR) return NULL;
    return genbf_cast_expr_get_primary(type, a->v1._cast_expr);
}
