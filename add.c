
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
/*Adds two character arrays char by char and ignores the decimal point if it at all exists*/
char *add(char *a, char *b){
	char *c = (char *)malloc(strlen(a) + 2);
	char *s = (char *)malloc(strlen(a) + 2);
	int i, k, count;
	int x = strlen(a);
	int y = strlen(b);
	int dota = 0;
	int dotb = 0;
	int j;
	for(i = 0; a[i] != '.' && a[i] != '\0'; i++)
		dota++;
	for(i = 0; b[i] != '.' && b[i] != '\0'; i++)
		dotb++;
	int m = (x - dota - 1) - (y - dotb - 1);
	if(m > 0){
		for(i = y, j = 0; j < m; j++, i++)
			b[i] = '0';
		y = i;
		b[i] = '\0';
	}
	else if(m < 0){
		m = -m;
		for(i = x, j = 0; j < m; j++, i++)
			a[i] = '0';
		x = i;
		a[i] = '\0';
	}
	if(x > y)
		count = 1;
	else
		count = 0;

	int carry = 0, l;
	int ans, temp;
	
	for(i = x - 1,j = y - 1, k = 0; i >= 0 || j >= 0; k++){
			if(a[i] == '.'){
				c[k] = '.';
				i--;
				j--;
				continue;
			}
			if(count == 1){
				if(j != -1){
					ans = a[i] + b[j] + carry - '0' - '0';
					i--;
					j--;
				}
				else{
					ans = a[i] + carry - '0';
					i--;
				}
			}
			else if(count == 0){
				if(i != -1){
					ans = a[i] + b[j] + carry - '0' - '0';
					i--;
					j--;
				}
				else{
					ans = b[j] + carry - '0';
					j--;
				}
			}
			temp = ans % 10;
			carry = ans / 10;
			c[k] = temp + '0';
		}
	if(count == 1 && carry == 1 && i == -1){
			c[k] = carry + '0';
			l = k;
	}
	else if(count == 0 && carry == 1 && j == -1){
			c[k] = carry + '0';
			l = k;
	}
	else
		l = k - 1;
	int check = 0;
	i = 0;
	for(j = l; j >= 0; j--){
		if(c[j] == '0' && check != 1);
		else{
			s[i] = c[j];
			check = 1;
			i++;
		}
	}
	s[i] = '\0';
	free(c);
	return s;
}
/* function addition which takes care of negative and positive integers and accordingly calls add*/
char *addition(char *x, char *y){
	if(strcmp(x, "0") == 0 && strcmp(y, "0") == 0)
		return "0";
	char *result, *temp;
	if(x[0] == '-' && y[0] == '-'){
		result = add(&x[1], &y[1]);
		temp = (char *)malloc(strlen(result) + 2);
		temp[0] = '-';
		temp[1] = '\0';
		strcat(temp, result);
		return temp;
	}
	else if(x[0] == '-' && y[0] != '-')
		result = sub1(y, &x[1]);
	else if(x[0] != '-' && y[0] == '-')
		result = sub1(x, &y[1]);
	else if(x[0] != '-' && y[0] != '-')
		result = add(x, y);
	return result;

}
