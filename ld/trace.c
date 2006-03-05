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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ld.h"
#include "staticize.h"

void traceBlock(struct block *tostat)
{
    char *code;
    int codelen, num;
    int i, j, o;
    struct block *fblock;
    
    code = strdup(tostat->code);
    if (!code) { perror("strdup"); exit(1); }
    
    /* loop through the code */
    o = 0;
    for (i = 0; code[i]; i++) {
        switch (code[i]) {
            case '(':
                /* find the end and null it */
                for (j = i + 1; code[j] && code[j] != ')'; j++);
                if (!code[j]) {
                    /* no ending ) ! */
                    fprintf(stderr, "Invalid reference %s"
                            " at column %d"
                            " in label %s\n", code + i,
                            i,
                            tostat->label);
                    exit(1);
                }
                code[j] = '\0';
                
                i++;
                if (code[i] == '*') i++;
                
                /* get the block */
                num = blockNum(code + i, &fblock);
                if (num == -1) {
                    fprintf(stderr, "Undefined symbol: '%s'"
                            " at column %d"
                            " in label %s\n", code + i,
                            i,
                            tostat->label);
                    exit(1);
                }
                
                /* recurse if we haven't */
                if (fblock->used == 0) {
                    fblock->used = 1;
                    traceBlock(fblock);
                }
                /* now we can continue */
                i = j;
                break;
                
            case '!':
                /* this symbol means "ignore any further input for this block" */
                for (; code[i]; i++);
                i--;
                break;
        }
    }
    
    free(code);
}
