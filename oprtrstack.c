
/*****************************************************************************
 * Copyright (C) Balasubramanian M. mbasubram@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include"oprtrstack.h"

void pushoptr(oprtrstack *s, char ch){
	s->c[s->i] = ch;
	(s->i)++;
}
int popoptr(oprtrstack *s){
	char ch = s->c[s->i - 1];
	(s->i)--;
	return ch;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack 
 */
void initop(oprtrstack *s){
	s->i = 0;
}
/* the caller should check that the stack is not empty before calling pop() 
 */
int cempty(oprtrstack *s){
	return s->i == 0;
}
