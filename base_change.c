
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
#include"token.h"
#include"integer.h"
/*base change of integer part */
char *integer_part(char *a, int n){
	char *b = (char *)malloc(1024);
	int i = 0, res;
	char *t, *t1, *t3;
	t3 = a;
	int count = 2, size = 1024;
	char *t2 = inttochar(n);
	do{
		t = divide(t3, t2);
		int len = checkdot(t);
		if(t[0] == '.'){
			t[0] = '0';
			t[1] = '\0';
			len = 0;
		}
		if(len == 0);
		else
			len = strlen(t) - len - 1;
		if(len != 0)
			t[len] = '\0';
		t1 = mul(t, t2);
		t3 = subtract(t3, t1);
	    int x  = atoi(t3);	
		if(x < 10)
			b[i++] = x + '1' - 1;
	    else if(x >= 10)
			b[i++] = x + 'A' - 10;
		t3 = t;
		res = compare(t3, "0");
		if(i == size - 1){
			b = realloc(b, count * 1024);
			count++;
			size = size + 1024;
		}
	}while(res > 0);
	char *c = (char *)malloc(strlen(b) + 1);
	int j = i;
	int k;
	for(i = j - 1, k = 0; i >= 0; i--, k++)
		c[k] = b[i];
	c[k] = '\0';/*
	free(b);
	free(t);
	free(t2);
	free(t1);
	free(t3);*/
	return c;
}
/*base change of decimal part */
char *decimal_part(char *a, int n){
	char *t, *t1, *t2, *t3;	
	t = a;
	int len = strlen(a) + 1;
	if(n <= 4)
		len = 2 * len;
	char *b = (char *)malloc(len + 1);
	int i = 1, x;
	t2 = inttochar(n);
	b[0] = '.';
	while(i <= len){
		t1 = mul(t, t2);
		t3 = mul(t, t2);
		int len1 = checkdot(t1);
		len1 = strlen(t1) - len1 - 1;
		if(len1 != 0)
			t1[len1] = '\0';
		else{
			t1[0] = '0';
			t1[1] = '\0';
		}
		x = atoi(t1);
		if(x < 10)
			b[i++] = x + '1' - 1;
	    else if(x >= 10)
			b[i++] = x + 'A' - 10;
		if(len1 != 0)
			t = subtract(t3, t1);
		else
			t = t3;
	}
	b[i] = '\0';
	return b;
}
/*main function of base change*/
char *base_change(char *a, int n){
	if(n == 10)
		return a;
	char *b;
	b = (char *)malloc(strlen(a) + 1);
	strcpy(b, a);
	int len;
	len = checkdot(a);
	if(len == 0){
		char *result = integer_part(b, n);
		return result;
	}
	len = strlen(a) - len - 1;
	if(len == 0){
		char *result = decimal_part(b, n);
		return result;
	}
	char *t, *t1;
	t = b;
	t[len] = '\0';
	t1 = subtract(a, t);
	t = integer_part(t, n);
	t1 = decimal_part(t1, n);
	t = realloc(t, strlen(t) + strlen(t1) + 1);
	strcat(t, t1);
	return t;
}
