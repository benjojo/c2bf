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

void putchar(char c) { asm("."); }

void puts(char *s)
{
    int i;
    for (i = 0; s[i]; i = i + 1) {
        putchar(s[i]);
    }
}

void main()
{
    char a[13];
    a[0] = 'H';
    a[1] = 'e';
    a[2] = 'l';
    a[3] = 'l';
    a[4] = 'o';
    a[5] = ' ';
    a[6] = 'w';
    a[7] = 'o';
    a[8] = 'r';
    a[9] = 'l';
    a[10] = 'd';
    a[11] = '!';
    a[12] = 0;
    
    puts(a);
}
