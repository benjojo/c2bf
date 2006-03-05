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

void genbf_statement(struct statement *a)
{
    switch (a->type) {
        case _LABELED_STATEMENT:
            genbf_labeled_statement(a->v._labeled_statement);
            break;
            
        case _COMPOUND_STATEMENT:
            genbf_compound_statement(a->v._compound_statement);
            break;
            
        case _EXPRESSION_STATEMENT:
            genbf_expression_statement(a->v._expression_statement);
            break;
            
        case _SELECTION_STATEMENT:
            genbf_selection_statement(a->v._selection_statement);
            break;
            
        case _ITERATION_STATEMENT:
            genbf_iteration_statement(a->v._iteration_statement);
            break;
            
        case _JUMP_STATEMENT:
            genbf_jump_statement(a->v._jump_statement);
            break;
    }
}
