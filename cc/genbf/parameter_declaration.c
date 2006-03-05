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

void genbf_parameter_declaration(struct parameter_declaration *a)
{
    struct type *vt;
    
    /* the tree here should look like this:
       -parameter_declaration
       |(type must be _DECLARATION)
       |
       |-type_specifier_list (v1._type_specifier_list)
       ||FIXME: this is ignored at the moment
       |
       |-declarator (v2)
       ||
       ||-declarator2 (v2) (guaranteed)
       |||genbf_declarator2_get_identifier is used to find the identifier
       */
    if (a->type != _DECLARATION)
        ERROR("parameter_declaration", "Type name parameters are not yet supported.\n");
    
    pushVar(genbf_declarator2_get_identifier(a->v2->v2), 1);
    
    /* find its type */
    vt = genbf_declarator(a->v2, NULL);
    curvar->type = vt;
    curvar->width = vt->size;
}
