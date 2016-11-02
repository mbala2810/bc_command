
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
#include"token.h"
char *sub1(char *s, char *p);
/*character by character subtraction*/
char *sub(char *num1, char *num2){
	int i, k, count;
	int x = strlen(num1);
	int y = strlen(num2);
	char *c, *s, *a, *b;
	a = (char *)malloc(x + 1);
	b = (char *)malloc(y + 1);
	strcpy(a, num1);
	strcpy(b, num2);
	if(x >= y){
		c = (char *)malloc(x + 1);
		s = (char *)malloc(x + 1);
	}
	else{
		c = (char *)malloc(y + 1);
		s = (char *)malloc(y + 1);
	}
	int dota = 0;
	int dotb = 0;
	int j, x1 = x;
	int y1 = y;
	for(i = 0; i < x1; i++){
		if(a[i] == '0'){
			for(j = 0; j < x1; j++)
				a[j] = a[j + 1];
			x--;
			x1 = x;
			i = 0;
		}
		else
			break;
	}
	for(i = 0; i < y1; i++){
		if(b[i] == '0'){
			for(j = i; j < y1; j++)
				b[j] = b[j + 1];
			y--;
			y1 = y;
			i = 0;
		}
		else
			break;
	}
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
	else if(x < y)
		count = 0;
	else
		count = 2;
	int l, check1 = 0;
	if(count == 2){
			if(a[0] > b[0]){
				count = 1;
				check1 = 1;
			}
			else if(a[0] < b[0]){
				count = 0;
				check1 = 1;
			}
	}
	if(check1 == 0 && count == 2){
		for(i = 1, j = 1; i < x; i++, j++){
			if(a[i] > b[j]){
				count = 1;
				break;
			}
			else if(a[i] < b[j]){
				count = 0;
				break;
			}
		}
		if(i == x)
			count = 1;
	}
	int ans1, d;
		for(i = x - 1,j = y - 1, k = 0; i >= 0 || j >= 0; k++){
			if(a[i] == '.' || b[j] == '.'){
				c[k] = '.';
					i--;
					j--;
				continue;
			}
			if(count == 1){
				if(j != -1){
					if(a[i] >= b[j])
						ans1 = a[i] - b[j];
					else{
						ans1 = 10 + a[i] - b[j];
						if(a[i - 1] != '.' && a[i - 1] != '0')
							a[i - 1] = a[i - 1] - 1;
						else if(a[i - 1] == '.' && a[i - 2] != '0')
							a[i - 2] = a[i - 2] - 1;
						else if(a[i - 1] == '0'){
							for(d = i - 1; a[d] == '0'; d--){
								a[d] = '9';
							}
							a[d] = a[d] - 1;
						}
						else if(a[i - 1] == '.' && a[i - 2] == '0'){
							for(d = i - 2; a[d] == '0'; d--){
								a[d] = '9';
							}
							a[d] = a[d] - 1;
						}	
					}	
					i--;
					j--;
				}
				else{
					ans1 = a[i] - '0';
					i--;
				}
			}
			else if(count == 0){
				if(i != -1){
					if(b[j] >= a[i])
						ans1 = b[j] - a[i];
					else{
						ans1 = 10 + b[j] - a[i];
						if(b[j - 1] != '.' && b[j - 1] != '0')
							b[j - 1] = b[j - 1] - 1;
						else if(b[j - 1] == '.' && b[j - 2] != '0')
							b[j - 2] = b[j - 2] - 1;
						else if(b[j - 1] == '0'){
							for(d = j - 1; b[d] == '0'; d--){
								b[d] = '9';
							}
							b[d] = b[d] - 1;
						}
						else if(b[j - 1] == '.' && b[j - 2] == '0'){
							for(d = j - 2; b[d] == '0'; d--){
								b[d] = '9';
							}
							b[d] = b[d] - 1;
						}	
					}
					i--;
					j--;
				}
				else{
					ans1 = b[j] - '0';
					j--;
				}
			}
			c[k] = ans1 + '0';
		}
	int z = k;
	for(i = z - 1; i > 0; i--){
		if(c[i] == '0')
			k--;
		else 
			break;
	}
	if(count == 0){
			c[k] = '-';
			l = k;
	}
	else
		l = k - 1;
	for(i = 0, j = l; j >= 0; j--, i++){
		s[i] = c[j];
	}
	s[i] = '\0';
	free(c);
	return s;
}
char *subtract(char *x, char *y){
	if(strcmp(x, "0") == 0 && strcmp(y, "0") == 0)
		return "0";
	if(strcmp(y, "0") == 0)
		return x;
	char *result, *temp;
	if(x[0] == '-' && y[0] != '-'){
		result = add(&x[1], y);
		temp = (char *)malloc(strlen(result) + 2);
		temp[0] = '-';
		temp[1] = '\0';
		strcat(temp, result);
		return temp;
	}
	else if(x[0] == '-' && y[0] == '-')
		result = sub1(&y[1], &x[1]);
	else if(x[0] != '-' && y[0] == '-')
		result = add(x, &y[1]);
	else if(x[0] != '-' && y[0] != '-')
		result = sub1(x, y);
	return result;
}
/* sub1 is a function that handles -ve and +ve integers and acc. calls the sub function*/
char *sub1(char *s, char *p){
	int dotlen1, dotlen2, len1;
	dotlen1 = checkdot(s);
	dotlen2 = checkdot(p);
	char *ans;
	if(dotlen1 == 0 && dotlen2 == 0){
		ans = sub(s, p);
		return ans;
	}
	char *tmp;
	if(dotlen1 >= dotlen2){
		tmp = (char *)malloc(dotlen1 + 2);
		len1 = dotlen1;
	}
	else{
		tmp = (char *)malloc(dotlen2 + 2);
		len1 = dotlen2;
	}
	int i;
	tmp[0] = '1';
	for(i = 1; i <= len1; i++)
		tmp[i] = '0';
	tmp[i] = '\0';
	s = multiply(s, tmp);
	p = multiply(p, tmp);
	if(dotlen1 != 0){
		for(i = 0; s[i] != '.'; i++);
		s[i] = '\0';
	}
	if(dotlen2 != 0){
		for(i = 0; p[i] != '.'; i++);
		p[i] = '\0';
	}
	s = sub(s, p);
	s = divides(s, tmp);
	return s;
}
