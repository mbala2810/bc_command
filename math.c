
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


/*Math library functions
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"integer.h"
#include"token.h"
int test1, test2;
int length1(int n){
	int i = 0;
	while(n){
		n = n / 10;
		i++;
	}
	return i;
}
char *inttochar(int n){
	int i;
	char *s;
	i = length1(n);
	int len = i;
	s = (char *)malloc(i + 1);
	for(i = len - 1; i >= 0; i--){
		s[i] = (n % 10) + '0';
		n = n / 10;
	}
	s[len] = '\0';
	return s;
}
/*if sign = 0 it means it is sin else it is cos
 */
char *reduce(char *s, int sign){
	char *t1, *t2;
	t1 = divides(s, "3.141529");
	int len = checkdot(t1);
	len = strlen(t1) - len - 1;
	t1[len] = '\0';
	t1 = addition(t1, "1");
	t2 = divides(t1, "2");
	if(sign == 0){
		if(checkdot(t2) == 0)
			test1 = 1;
		else
			test1 = 0;
	}
	else{
		int j = checkdot(t2);
		t2 = multiply(t1, "3.141529");
		t2 = subtract(t2, s);
		if(j == 0){
			int res = compare(t2, "1.5707645");
			if(res >= 0)
				test1 = 1;
			else
				test1 = 0;
		}
		else{
			int res = compare(t2, "1.5707645");
			if(res >= 0)
				test1 = 0;
			else
				test1 = 1;
		}
		return t2;
	}
	t2 = multiply(t1, "3.141529");
	t2 = subtract(t2, s);
	free(t1);
	return t2;
}
/*sine of an angle*/
char *sine(char *p){
	if(strcmp(p, "0") == 0)
		return "0";
	test1 = 0;
	char *s = (char *)malloc(strlen(p) + 1);
	strcpy(s, p);
	if(compare(s, "6.283058") > 0)							/* 2 * pi = 6.283058 */
		s = reduce(s, 0);
	char *ans, *d;
	d = (char *)malloc(2);
	d[0] = '1';
	d[1] = '\0';
	ans = s;
	char *t = s, *t1;
	int n = 1;
	char *denominator;
	char *x = mul(s, s);
	do{
		denominator = inttochar(2 * n * (2 * n + 1));
		d = mul(d, denominator);
		t = mul(t, x);
		t1 = divides(t, d);
		if(n % 2 == 0){
			ans = addition(ans, t1);
		}
		else{
			ans = subtract(ans, t1);
		}
		n = n + 1;
	}while(n <= 15);
	if(test1 == 1){
		if(ans[0] == '-'){
			char *temp = (char *)malloc(strlen(ans) + 1);
			strcpy(temp, &ans[1]);
			return temp;
		}
		else{
			char *temp = (char *)malloc(strlen(ans) + 2);
			temp[0] = '-';
			temp[1] = '\0';
			strcat(temp, ans);
			return temp;
		}
	}
	free(d);
	free(t);
	free(denominator);
	free(x);
	free(t1);
	free(s);
	return ans;
}

/*cosine of an angle*/
char *cosine(char *p){
	if(strcmp(p, "0") == 0)
		return "1";
	char *ans, *temp, *tmp, *x, *t1, *d;
	test1 = 0;
	char *s = (char *)malloc(strlen(p) + 1);
	strcpy(s, p);
	if(compare(s, "6.283058") > 0)							/* 2 * pi = 6.283058 */
		s = reduce(s, 1);

	ans = (char *)malloc(2);
	ans[0] = '1';
	ans[1] = '\0';
	temp = ans;
	d = ans;
	x = mul(s, s);
	int n = 1;
	do{
		tmp = inttochar(2 * n * (2 * n - 1));
		d = mul(tmp, d);
		temp = mul(temp, x);
		t1 = divides(temp, d); 
		if(n % 2 == 0)
			ans = addition(ans, t1);
		else
			ans = subtract(ans, t1);
		n++;
	}while(n <= 15);
	if(test1 == 1){
		if(ans[0] == '-'){
			char *temp = (char *)malloc(strlen(ans) + 1);
			strcpy(temp, &ans[1]);
			return temp;
		}
		else{
			char *temp = (char *)malloc(strlen(ans) + 2);
			temp[0] = '-';
			temp[1] = '\0';
			strcat(temp, ans);
			return temp;
		}
	}

	free(d);
	free(tmp);
	free(temp);
	free(x);
	free(t1);
	return ans;
}
/*tangent of an angle*/
char *tangent(char *s){
	char *temp1, *temp2;
	temp1 = sine(s);
	temp2 = cosine(s);
	temp1 = divides(temp1, temp2);
	return temp1;
}
