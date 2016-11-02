
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

#include"oprndstack.h"
#include<stdlib.h>
#include<string.h>

void pushopnd(oprndstack *s, char *str){
	s->a[s->i] = (char *)malloc(strlen(str) + 1);
	strcpy(s->a[s->i], str);
	(s->i)++;
}
char *popopnd(oprndstack *s){
	char *t;
	t = (char *)malloc(strlen(s->a[s->i - 1]));
	strcpy(t, s->a[s->i - 1]);
	(s->i)--;
	return t;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack 
 */
void inits(oprndstack *s){
	s->i = 0;
}
/* the caller should check that the stack is not empty before calling pop() 
 */
int iempty(oprndstack *s){
	return s->i == 0;
}
