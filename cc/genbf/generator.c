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

#include "generator.h"

struct block *curblock = NULL;
struct var *curvar = NULL;

/* pushNamedBlock
 * input: name of the block to push
 * output: none
 * effect: curblock now points at a block with the name given
 */
void pushNamedBlock(const char *name)
{
    struct block *prevblock = curblock;
    NEW(curblock, struct block);
    
    curblock->next = prevblock;
    curblock->name = strdup(name);
    if (!curblock->name) { perror("strdup"); exit(1); }
    curblock->num = 0;
    curblock->vars = 0;
    curblock->stack = 0;
}

/* pushSubBlock
 * input: an offset
 * output: none
 * effect: curblock now points at a block with the previous name!num+1+offset,
 *         and num 0
 */
void pushSubBlock(int offset)
{
    char *nname;
    
    pushBlock();
    /* nname contains the new multi-! name */
    nname = (char *) malloc(strlen(curblock->name) + 11);
    if (!nname) { perror("malloc"); exit(1); }
    /* this num is what makes this a "subblock" */
    sprintf(nname, "%s!%d", curblock->name, curblock->num + offset);
    free(curblock->name);
    curblock->name = nname;
    curblock->num = 0;
}

/* pushBlock
 * input: none
 * output: none
 * effect: curblock now points at a block with the previous name, but a new
 *         number
 */
void pushBlock()
{
    struct block *prevblock = curblock;
    NEW(curblock, struct block);
    
    if (!prevblock) {
        fprintf(stderr, "Internal compiler error in pushBlock()\n");
        exit(1);
    }
    
    curblock->next = prevblock;
    curblock->name = strdup(prevblock->name);
    if (!curblock->name) { perror("strdup"); exit(1); }
    curblock->num = prevblock->num + 1;
    curblock->vars = 0;
    curblock->stack = 0;
}

/* pushCall
 * input: the function to call
 * output: none
 * effect: the function is called with the return address of pushBlock()
 */
void pushCall(const char *func)
{
    if (!curblock) {
        fprintf(stderr, "Internal compiler error in pushCall()\n");
        exit(1);
    }
    
    BF_PUSH;
    pushTempVar(1);
    
    printf("(*%s!%d)(%s)", curblock->name, curblock->num + 1, func);
    
    pushBlock();
}

/* popNamedBlock
 * input: none
 * output: none
 * effect: pop down to the last named block
 */
void popNamedBlock()
{
    if (!curblock) {
        fprintf(stderr, "Internal compiler error 1 in popNamedBlock()\n");
        exit(1);
    }
    
    /* keep popping until we pop one with num=0 */
    while (curblock->num > 0) {
        popBlock();
        
        if (!curblock) {
            fprintf(stderr, "Internal compiler error 2 in popNamedBlock()\n");
            exit(1);
        }
    }
    
    /* this one has num = 0, pop it */
    popBlock();
}

/* popBlock
 * input: none
 * output: none
 * effect: pop a single block
 */
void popBlock()
{
    struct block *nextblock;
    int i;
    
    if (!curblock) {
        fprintf(stderr, "Internal compiler error in popBlock()\n");
        exit(1);
    }
    
    /* pop off the vars */
    for (i = 0; i < curblock->vars; i++) {
        popVar();
    }
    
    free(curblock->name);
    
    nextblock = curblock->next;
    free(curblock);
    curblock = nextblock;
}

/* outBlock
 * input: none
 * output: none
 * effect: "\n", the appropriate block name and ": " are printed on stdout
 */
void outBlock()
{
    if (!curblock) {
        fprintf(stderr, "Internal compiler error in outBlock()\n");
        exit(1);
    }

    /* if the number is nonzero, name!num, otherwise just name */
    if (curblock->num) {
        printf("\n%s!%d: ", curblock->name, curblock->num);
    } else {
        printf("\n%s: ", curblock->name);
    }
    
    fflush(stdout);
}

/* pushVar
 * input: a variable name and width in stack cells
 * output: none
 * effect: a variable is pushed onto the variable stack, and the previous
 *         variable's depth is set
 */
void pushVar(const char *name, int width)
{
    /* this is pushed like a temp var, then named */
    pushTempVar(width);
    
    curvar->name = strdup(name);
    if (!curvar->name) { perror("strdup"); exit(1); }
    
    /* and added the var to the block */
    curblock->vars++;
    curblock->stack += width;
}

/* pushTempVar
 * input: a variable width in stack cells
 * output: none
 * effect: an unnamed variable is pushed onto the internal variable stack
 */
void pushTempVar(int width)
{
    struct var *prevvar;
    
    if (!curblock) {
        fprintf(stderr, "Internal compiler error in pushVar()\n");
        exit(1);
    }
    
    /* and push the var on the stack */
    prevvar = curvar;
    NEW(curvar, struct var);
    
    curvar->next = prevvar;
    curvar->name = NULL;
    curvar->width = width;
    curvar->type = NULL;
}

/* newVar
 * input: none
 * output: an empty MALLOC'D struct var
 * effect: none
 */
struct var *newVar()
{
    struct var *nv;
    
    NEW(nv, struct var);
    
    nv->next = NULL;
    nv->name = NULL;
    nv->width = 0;
    nv->type = NULL;
    
    return nv;
}

/* popVar
 * input: none
 * output: none
 * effect: a variable is popped from the variable stack
 */
void popVar()
{
    struct var *nextvar;
    int i;
    
    if (!curvar) {
        fprintf(stderr, "Internal compiler error in popVar()\n");
        exit(1);
    }
    
    for (i = 0; i < curvar->width; i++)
        BF_POP;
    
    freeType(curvar->type);
    
    free(curvar->name);
    nextvar = curvar->next;
    free(curvar);
    curvar = nextvar;
}

/* ignoreVar
 * input: none
 * output: none
 * effect: a variable is popped from the internal stack but left in the BF stack
 */
void ignoreVar()
{
    struct var *nextvar;
    int i;
    
    if (!curvar) {
        fprintf(stderr, "Internal compiler error in ignoreVar()\n");
        exit(1);
    }
    
    free(curvar->name);
    nextvar = curvar->next;
    free(curvar);
    curvar = nextvar;
}

/* getVar
 * input: variable name
 * output: the depth of the variable in the current stack or -1 on error
 * effect: v is set to the variable
 */
int getVar(const char *name, struct var **v)
{
    int depth = 0;
    struct var *cur;
    
    /* start with the top */
    cur = curvar;
    
    while (cur) {
        /* we need the left end of the variable */
        depth += cur->width - 1;
        
        /* if it matches, return the current depth */
        if (cur->name && !strcmp(cur->name, name)) {
            if (v) {
                *v = cur;
            }
            return depth;
        }
        
        depth += 1;
        cur = cur->next;
    }
    
    /* no match! */
    return -1;
}

/* blockDepth
 * input: none
 * output: the depth of the current block
 * effect: none
 */
int blockDepth()
{
    int depth = 0;
    struct var *cur;
    
    /* start with the top */
    cur = curvar;
    
    while (cur) {
        /* add the current depth */
        depth += cur->width;
        cur = cur->next;
    }
    
    return depth;
}

/* dupType
 * input: a struct type to be duplicated
 * output: the duplicated version, MALLOC'D
 * effect: none
 */
struct type *dupType(struct type *t)
{
    struct type *cur, *o, *oc, *on;
    
    o = NULL;
    oc = NULL;
    on = NULL;
    
    cur = t;
    
    /* go through, each time adding a level */
    while (cur) {
        if (!o) {
            /* start the chain */
            NEW(o, struct type);
            oc = o;
        } else {
            /* continue the chain */
            NEW(on, struct type);
            oc->next = on;
            oc = on;
        }
        
        /* copy it in */
        memcpy(oc, cur, sizeof(struct type));
        
        /* set next to NULL */
        oc->next = NULL;
        
        /* step */
        cur = cur->next;
    }
    
    /* now o is our newly created list */
    return o;
}

/* freeType
 * input: a struct type *
 * output: none
 * effect: the linear linked list's memory is free'd
 */
void freeType(struct type *t)
{
    struct type *cur, *next;
    
    cur = t;
    
    while (cur) {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

/* intType
 * input: none
 * output: a MALLOC'D struct type with a simple int
 * effect: none
 */
struct type *intType()
{
    struct type *t;
    
    NEW(t, struct type);
    t->next = NULL;
    t->basic_type = TYPE_INT;
    t->array = 0;
    t->size = 1;
    
    return t;
}
