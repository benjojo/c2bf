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

/* this file is #include'd in the middle of postfix_expr.c, to not clutter it
 * with builtins */

if (!strcmp(f, "asm")) {
    char *asmc;
    
    /* the tree should look like this:
       -postfix_expr
       |(type must be _FCALL)
       |
       |-argument_expr_list (v2._argument_expr_list)
       ||(end must be 1)
       ||
       ||-assignment_expr (v2)
       |||genbf_assignment_expr_get_primary is used to get the deeply nested
       ||| string value
       */
    if (a->type != _FCALL)
        ERROR("builtin_functions", "asm: no parameters provided");
    
    if (!a->v2._argument_expr_list->end)
        ERROR("builtin_functions", "asm: too many parameters provided");
    
    asmc = genbf_assignment_expr_get_primary(_STRING,
                                            a->v2._argument_expr_list->v2);
    
    if (!asmc)
        ERROR("builtin_functions", "asm: wrong parameter type");
    
    printf(asmc);
    BF_PUSH;
    pushTempVar(1);
}
