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

#include <string.h>

#include "../genbf.h"
#include "generator.h"

int genbf_primary_expr(struct primary_expr *a, int lval, struct type **t)
{
    int i, v;
    struct var *sv;
    
    switch (a->type) {
        case _IDENTIFIER:
            /* where is this variable? */
            v = getVar(a->v._identifier->v, &sv);
            
            /* there's a special case: if !lval but it's an array, we actually
             * want to treat it as an lval (get the data's location).  If lval
             * and it's an array, we die (that's not allowed) */
            if (sv->type->basic_type == TYPE_PTR &&
                sv->type->array) {
                if (!lval) {
                    lval = 1;
                } else {
                    ERROR("primary_expr", "Changing array pointer values is not currently possible.");
                }
            }
            
            if (!lval) {
                BF_PUSH;
                pushTempVar(1);
                curvar->type = dupType(sv->type);
                
                /* FIXME: this needs to support a whole range of other idents */
                if (v == -1)
                    ERROR("primary_expr", "Undefined identifier.");
                
                v++;
                /* now go and get it */
                printf("[-]");
                for (i = 0; i < v; i++)
                    printf("<<<<<");
                /* dup */
                printf("[>>>+>+<<<<-]>>>[<<<+>>>-]>[");
                /* carry it up */
                for (i = 0; i < v; i++)
                    printf(">>>>>");
                printf("+");
                for (i = 0; i < v; i++)
                    printf("<<<<<");
                printf("-]");
                /* and put it in place */
                for (i = 0; i < v; i++)
                    printf(">>>>>");
                printf("[<<<<+>>>>-]<<<<");
                fflush(stdout);
            } else {
                /* lval - turn the identifier into a location */
                if (v == -1)
                    ERROR("primary_expr", "Undefined identifier.");
                
                if (t) *t = sv->type;
                
                /* now we must turn this depth into a location */
                BF_PUSH;
                pushTempVar(1);
                
                curvar->type = dupType(sv->type);
                /* this is now a pointer at the array */
                curvar->type->array = 0;
                curvar->type->size = 1;
                
                printf("[-]");
                v++;
                for (i = 0; i < v; i++)
                    printf("<<<<<");
                STACK_POS_TO_PTR;
                
                return -1;
            }
            break;
        
        case _CONSTANT:
            if (lval)
                ERROR("primary_expr", "Invalid l-value.");
            
            /* FIXME: this is a ridiculous way to generate a constant ... */
            BF_PUSH;
            pushTempVar(1);
            curvar->type = intType();
            
            printf("[-]");
            
            /* constants can be either numbers or 'characters' */
            if (a->v._token[0] == '\'') {
                v = *genbf_parse_string(a->v._token);
            } else {
                v = atoi(a->v._token);
            }
            if (v >= 0)
                for (i = 0; i < v; i++)
                    printf("+");
            else
                for (i = 0; i > v; i--)
                    printf("-");
            
            fflush(stdout);
            break;
            
        case _EXPR:
            return genbf_expr(a->v._expr, lval, t);
            break;
        
        /*case _IDENTIFIER:
            genbf_identifier(a->v._identifier);
            break;
            
        case _CONSTANT:
            SPC; printf("CONSTANT: %s\n", a->v._token);
            break;
            
        case _STRING:
            SPC; printf("STRING: %s\n", a->v._token);
            break;
            
        case _EXPR:
            genbf_expr(a->v._expr);
            break;*/
        default:
            UNIMPL("primary_expr");
    }
}

char *genbf_primary_expr_get_primary(int type, struct primary_expr *a)
{
    /*if (a->type == _EXPR)
        return genbf_expr_get_primary(type, a->v._expr);*/
    
    if (type != a->type) return NULL;
    if (type == _IDENTIFIER)
        return a->v._identifier->v;
    if (type == _CONSTANT)
        return a->v._token;
    if (type == _STRING)
        return genbf_parse_string(a->v._token);
}

char *genbf_parse_string(char *inp)
{
    static char *toret = NULL;
    int osl, i, o;
    
    if (!toret) {
        toret = (char *) malloc(strlen(inp) + 1);
        if (!toret) { perror("malloc"); exit(1); }
    } else {
        toret = (char *) realloc(toret, strlen(inp) + 1);
        if (!toret) { perror("realloc"); exit(1); }
    }
    
    /* now set osl, and walk */
    osl = strlen(inp);
    o = 0;
    for (i = 1; i < osl - 1; i++) {
        switch (inp[i]) {
            case '\\':
                i++;
                switch (inp[i]) {
                    case 'n':
                        toret[o] = '\n';
                        break;
                        
                    case 'r':
                        toret[o] = '\r';
                        break;
                        
                    default:
                        toret[o] = inp[i];
                        break;
                }
                break;
                
            default:
                toret[o] = inp[i];
                break;
        }
        o++;
    }
    toret[o] = '\0';
    
    return toret;
}
