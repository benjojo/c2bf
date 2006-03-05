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

struct type *genbf_declarator(struct declarator *a, struct type *into)
{
    struct type *t, *nt;
    
    t = genbf_declarator2(a->v2, into);
    
    if (a->pointer) {
        /* FIXME: this should handle type_specifier_list */
        struct pointer *cur = a->v1;
        while (cur) {
            NEW(nt, struct type);
            nt->next = t;
            nt->basic_type = TYPE_PTR;
            nt->array = 0;
            nt->size = 1;
            t = nt;
            
            /* if this is the end, no more curs */
            if (cur->end) {
                cur = NULL;
            } else {
                cur = cur->v2;
            }
        }
    }
    
    return t;
}
