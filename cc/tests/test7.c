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

void main()
{
    char a[14];
    a[0] = 0;
    a[1] = 'H';
    a[2] = 'e';
    a[3] = 'l';
    a[4] = 'l';
    a[5] = 'o';
    a[6] = ' ';
    a[7] = 'w';
    a[8] = 'o';
    a[9] = 'r';
    a[10] = 'l';
    a[11] = 'd';
    a[12] = '!';
    a[13] = 0;
    
    asm("<<<<<[<<<<<]>>>>>[.>>>>>]");
}
