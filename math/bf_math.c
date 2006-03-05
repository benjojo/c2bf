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

int __builtin_mul(int a, int b)
{
    int r;
    r = 0;
    
    for (; a != 0; a = a - 1) {
        r = r + b;
    }
    
    return r + b;
}

int __builtin_div(int a, int b)
{
    int r;
    r = 0;
    
    while (a >= b) {
        a = a - b;
        r = r + 1;
    }
    
    return r;
}

int __builtin_mod(int a, int b)
{
    while (a >= b) {
        a = a - b;
    }
    
    return a;
}
