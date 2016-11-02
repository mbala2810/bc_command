
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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"integer.h"
/*compares two numbers and returns 0 if both are same and answer less than zero if p < q and greater than zero if p > q*/
int compare(char *p, char *q){
	char *s = removezero(p);
	char *r = removezero(q);
	int j = strlen(s) - checkdot(s);
	int k = strlen(r) - checkdot(r);
	if(j < k)
		return -1;
	else if(j > k)
		return 1;
	else {
		return strcmp(s, r);
	}

}
char *removezero(char *s){
	int i = 0, lens, j;
	char *a;
	lens = strlen(s);
	if(s[0] != '0')
		return s;
	a = (char *)malloc(strlen(s) + 1);
	strcpy(a, s);
	while(a[i] == '0' && a[i] != '\0'){
		for(j = 0; j < lens; j++)
			a[j] = a[j + 1];
		lens = lens - 1;
	}
	if(i == lens){
		a[0] = '0';
		a[1] = '\0';
	}
	return a;
}
