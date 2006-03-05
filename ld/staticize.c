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

void staticizeBlock(struct block *tostat)
{
    char *newcode, *code;
    int codelen, num;
    int i, j, o;
    
    /* start with newcode the same size as code, and expand as necessary */
    code = tostat->code;
    codelen = strlen(code);
    newcode = (char *) malloc(codelen + 1);
    if (!newcode) { perror("malloc"); exit(1); }
    
    /* then loop through the original code and associate */
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
                /* now switch for * or no * */
                switch (code[i]) {
                    case '*':
                        /* just put a pointer */
                        num = blockNum(code + i + 1, NULL);
                        if (num == -1) {
                            fprintf(stderr, "Undefined symbol: '%s'"
                                    " at column %d"
                                    " in label %s\n", code + i + 1,
                                    i + 1,
                                    tostat->label);
                            exit(1);
                        }
                        
                        /* FIXME: some better number-generation code is in order */
                        codelen += num + 3;
                        newcode = (char *) realloc(newcode, codelen);
                        if (!newcode) { perror("realloc"); exit(1); }
                        
                        /* zero the cell */
                        sprintf(newcode + o, "[-]");
                        o += 3;
                        
                        /* then just + a bunch */
                        for (; num > 0; num--) {
                            newcode[o] = '+';
                            o++;
                        }
                        break;
                        
                    default:
                        /* more difficult: go to the proper location and set
                         * a 1 */
                        num = blockNum(code + i, NULL);
                        if (num == -1) {
                            fprintf(stderr, "Undefined symbol: '%s'"
                                    " at column %d"
                                    " in label %s\n", code + i,
                                    i,
                                    tostat->label);
                            exit(1);
                        }
                        
                        codelen += 25 + (5 * num);
                        newcode = (char *) realloc(newcode, codelen);
                        if (!newcode) { perror("realloc"); exit(1); }
                        
                        /* step one: get back to the beginning of the stack */
                        sprintf(newcode + o, "<<<[<<<<<]>>>");
                        o += 13;
                        
                        /* step two: the right number of >s */
                        for (; num > 0; num--) {
                            sprintf(newcode + o, ">>>>>");
                            o += 5;
                        }
                        
                        /* step three: set it properly */
                        newcode[o] = '+';
                        o++;
                        
                        /* step four: get back */
                        sprintf(newcode + o, ">>[>>>>>]<<");
                        o += 11;
                }
                /* now we can continue */
                i = j;
                break;
                
            case '!':
                /* this symbol means "ignore any further input for this block" */
                for (; code[i]; i++);
                i--;
                break;
            
            default:
                newcode[o] = code[i];
                o++;
        }
    }
    
    newcode[o] = '\0';
    
    /* now newcode is in order, so put it in the struct */
    tostat->code = newcode;
}
