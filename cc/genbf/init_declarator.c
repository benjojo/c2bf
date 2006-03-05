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

void genbf_init_declarator(struct init_declarator *a)
{
    struct type *vt;
    int i;
    
    /* push this variable */
    pushVar(genbf_declarator2_get_identifier(a->v1->v2), 1);
    
    /* then use genbf_declarator to get its type */
    vt = genbf_declarator(a->v1, NULL);
    curvar->type = vt;
    curvar->width = vt->size;
    
    /* and push it in BF */
    for (i = 0; i < curvar->width; i++)
        BF_PUSH;
    
    if (a->assign) {
        UNIMPL("init_declarator with assignment");
    }
}
