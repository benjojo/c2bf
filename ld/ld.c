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

struct block *curblock = NULL;

int main()
{
    char *line;
    struct block *newblock, *cur;
    int i, osl, cbs, rs;
    int startblock;
    
    /* read in the blocks ... */
    while (!feof(stdin) && !ferror(stdin)) {
        cbs = 2048;
        line = (char *) malloc(cbs + 1);
        if (!line) { perror("malloc"); exit(1); }
        line[cbs] = '\0';
        
        /* read in the line */
        if (!fgets(line, cbs, stdin)) {
            free(line);
            continue;
        } else {
            while (line[cbs - 2]) {
                /* expand the line */
                line = (char *) realloc(line, (cbs * 2) + 1);
                if (!line) { perror("realloc"); exit(1); }
                line[cbs * 2] = '\0';
                
                /* read more */
                if (!fgets(line + cbs - 1, cbs + 1, stdin))
                    break;
                
                cbs *= 2;
            }
        }
        
        /* get rid of trailing newlines */
        osl = strlen(line) - 1;
        while (line[osl] == '\n' ||
               line[osl] == '\r') {
            line[osl] = '\0';
            osl--;
        }
        
        /* make sure it's not blank */
        if (!line[0]) {
            free(line);
            continue;
        }
        
        /* realloc conservatively */
        osl++;
        line = (char *) realloc(line, osl);
        if (!line) { perror("realloc"); exit(1); }
        
        /* start the new block */
        newblock = (struct block *) malloc(sizeof(struct block));
        newblock->next = curblock;
        newblock->prev = NULL;
        if (curblock) curblock->prev = newblock;
        curblock = newblock;
        if (curblock->next) {
            curblock->num = curblock->next->num + 1;
        } else {
            curblock->num = 0;
        }
        curblock->used = 0;
        
        /* and divide in the string */
        for (i = 0; line[i] && line[i] != ':'; i++);
        if (!line[i]) {
            /* no :!  Bad line! */
            fprintf(stderr, "Bad line: %s\n", line);
            free(line);
            continue;
        }
        line[i] = '\0';
        i++;
        for (; line[i] && (line[i] == ':' || line[i] == ' '); i++);
        
        /* put it in curblock */
        curblock->label = line;
        curblock->code = line + i;
    }
    
    if (!curblock) {
        /* what, no blocks at all?! */
        return 0;
    }
    
    /* trace the blocks (to avoid writing out unused blocks) */
    if ((startblock = blockNum("__start", &cur)) == -1) {
        fprintf(stderr, "No __start function (perhaps you forgot to include __start.o?)!\n");
        exit(1);
    }
    cur->used = 1;
    traceBlock(cur);
    
    /* now that we've read in all the blocks, make the proper associations */
    cur = curblock;
    while (cur) {
        staticizeBlock(cur);
        cur = cur->next;
    }
    
    /* start the labelling code */
    printf(">>");
    for (i = 0; i < curblock->num; i++) {
        printf("[>+>>>>+<<<<<-]>[<+>-]>>>>+");
    }
    printf(">>>");
    for (i = 0; i < curblock->num; i++) {
        printf("<<<<<");
    }
    
    /* set the proper block active */
    osl = startblock;
    
    /* get there ... */
    for (; startblock > 0; startblock--)
        printf(">>>>>");
    startblock = osl;
    
    /* set it ... */
    printf("+");
    
    /* get back ... */
    for (; startblock > 0; startblock--)
        printf("<<<<<");
    
    /* get our static 1 to loop off of */
    printf("<<<<<+[");
    
    /* now, starting with block #0, put in the real magic */
    cur = curblock;
    while (cur->next) cur = cur->next;
    
    while (cur) {
        if (cur->used) {
            /* if it's used, put in the code */
            printf(">>>>>[->>[>>>>>]<<");
            printf(cur->code);
            printf("<<<[<<<<<]>>>");
            for (i = 0; i < cur->num; i++) {
                printf(">>>>>");
            }
            printf("]");
        } else {
            /* otherwise, just stub it */
            printf(">>>>>");
        }
        
        cur = cur->prev;
    }
    
    /* finally, end our magic loop */
    printf("<<<[<<<<<]<<]");
    
    return 0;
}

/* blockNum
 * input: the name of a symbol
 * output: its number (or -1 on error)
 * effect: none
 */
int blockNum(const char *label, struct block **into)
{
    struct block *cur = curblock;
    
    while (cur) {
        if (!strcmp(cur->label, label)) {
            if (into)
                *into = cur;
            return cur->num;
        }
        cur = cur->next;
    }
    
    return -1;
}
