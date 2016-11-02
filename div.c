
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

#include"integer.h"
#include"token.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
int check2, a, checklen, h;
int find_ans(char *s, char *p);
char *div_ans(char *s, char *p);
char *divide(char *s, char *p);
/*divides two numbers*/
char *division(char *s, char *p){
	int res = compare(s, p), l = 0, check1 = 0, count = 0, k, lens, lenp, len;
	if(strcmp(s, "0") == 0 && strcmp(p, "0") != 0)
		return "0";
	if(strcmp(p, "0") == 0)
		return NULL;
	if(strcmp(p, "1") == 0)
		return s;
	if(res == 0)
		return "1";
	h = 0;
	char *ans = NULL, *tmp1;
	a = 0; 
	int test = 0;
	if(res > 0){
		ans = (char *)malloc(strlen(s) - strlen(p) + 2);
		lenp = strlen(p);
		while(check1 != 1){
			lens = strlen(s);
			len = lens - lenp;
			h = l;
			count = 0;
			k = find_ans(s, p);
			ans[h] = k + '0';
			h++;
			if(check2 == 1 && test == 0){
				count++;
				check2 = 0;
			}
			if(test == 0){
				while(count != len){
					ans[h] = '0';
					h++;
					count++;
				}
				test = 1;
				ans[h] = '\0';
			}
			h = l + checklen + 1;
			l = h;
			if(strlen(p) <= strlen(&ans[a]))
				tmp1 = multiply(&ans[a], p);
			else
				tmp1 = multiply(p, &ans[a]);
			res = compare(s, tmp1);
			if(res > 0){
				s = sub(s, tmp1);
				a = a + checklen + 1;
				res = compare(s, p);
				if(res < 0){
					free(tmp1);
					check1 = 1;
				}
			}
			else if(res == 0){
				free(tmp1);
				return ans;
			}
		}
		char *temp = div_ans(s, p);
		ans = (char *)realloc(ans, strlen(ans) + strlen(temp) + 1);
		strcat(ans, temp);
		free(temp);
		return ans;
	}
	if(res < 0){
		ans = div_ans(s, p);
		return ans;	
	}
	return ans;
}
int find_ans(char *s, char *p){
	int i, count = 1, j, lenp, len;
	lenp = strlen(p);
	len  = strlen(s) - lenp;
	char *temp = (char *)malloc(lenp + 2);
	checklen = 0;
	for(i = 0, j = 0; j < lenp; i++){
		temp[j] = s[i];
		j++;
	}
	temp[j] = '\0';
	check2 = 0;
	char *temp1, *temp2, *tmp, *temp3;
	temp1 = (char *)malloc(strlen(p) + 1);
	strcpy(temp1, p);
	int res = compare(temp, p);
	tmp = (char *)malloc(2);
	while(1){
		if(res < 0){
			temp[j] = s[i];
			j++;
			i++;
			check2 = 1;
			temp[j] = '\0';
			temp = (char *)realloc(temp, strlen(temp) + 1);
			res = compare(temp, p);
		}
		else if(res == 0){
			temp3 = (char *)malloc(2);
			temp3[0] = '0';
			temp3[1] = '\0';
			if(s[i] != '\0'){
				do{
					temp3 = multiply(temp3, "10");
					tmp[1] = '\0';			
					tmp[0] = s[i];
					i++;
					checklen++;
					temp3 = add(temp3, tmp);
					res = compare(temp3, p);
				}while(res < 0);
			}
			checklen = checklen - 1;
			free(temp);
			free(temp1);
			free(tmp);
			free(temp3);
			return 1;
		}
		else {
			temp2 = sub(temp, temp1);
			while(temp2[0] != '-'){
				temp3 = temp2;
				temp2 = sub(temp2, temp1);
				count++;
			}
			if(s[i] != '\0'){
				do{
					temp3 = multiply(temp3, "10");
					tmp[1] = '\0';
					tmp[0] = s[i];
					i++;
					checklen++;
					temp3 = add(temp3, tmp);
					res = compare(temp3, p);
				}while(res < 0);	
			}
			checklen = checklen - 1;
			free(temp);
			free(temp1);
			free(temp2);
			free(temp3);
			free(tmp);
			return count - 1;
		}
	}
}
char *div_ans(char *s, char *p){
	char *tmp1, *ans, *tmp;
	int res, i = 1, j, count = 0, length;
	int lenp = strlen(p);
	int lens = strlen(s);
	if(lenp - lens >= 21){
		ans = (char *)malloc(lenp - lens + 10);
		length = lenp - lens + 8;
	}
	else{
		ans = (char *)malloc(22);
		length = 22;
	}
		ans[0] = '.';
	do{
		s = multiply(s, "10");
		res = compare(s, p);
		if(count != 0){
			ans[i] = '0';
			i++;
		}
		count = 1;
	}while(res < 0);
	int k;
	ans[i] = '\0';
	tmp1 = (char *)malloc(strlen(p) + 1);
	strcpy(tmp1, p);
	while(1){
		k = 0;
		tmp = s;
		while(tmp[0] != '-'){
			s = tmp;
			tmp = sub(tmp, p);
			k++;
		}
		ans[i] = k - 1 + '0';
		j = i;
		i++;
		if(strcmp(s, "0") == 0)
			break;
		else if(i >= length - 1)
			break;
		p = tmp1;
		s = multiply(s, "10");
	}
	ans[i] = '\0';
	free(tmp);
	free(tmp1);
	return ans;

}
char *modulus(char *s, char *p){
	int res;
	if(strcmp(p, "1") == 0)
		return "0";
	res = compare(s, p);
	if(res == 0)
		return "0";
	char *ans = divide(s, p);
	ans = multiply(ans, p);
	ans = sub(s, ans);
	return ans;
}
char *divide(char *s, char *p){
	int dotlen1, dotlen2, len;
	dotlen1 = checkdot(s);
	dotlen2 = checkdot(p);
	char *ans;
	if(dotlen1 == 0 && dotlen2 == 0){
		ans = division(s, p);
		return ans;
	}
	char *tmp;
	if(dotlen1 >= dotlen2){
		tmp = (char *)malloc(dotlen1 + 2);
		len = dotlen1;
	}
	else{
		tmp = (char *)malloc(dotlen2 + 2);
		len = dotlen2;
	}
	int i;
	tmp[0] = '1';
	for(i = 1; i <= len; i++)
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
	ans = division(s, p);
	return ans;
}
char *divides(char *x, char *y){
	char *temp, *result;
	if(x[0] == '-' && y[0] == '-')
		result = divide(&x[1], &y[1]);
	else if(x[0] != '-' && y[0] != '-')
		result = divide(x, y);
	else{
		if(x[0] == '-' && y[0] != '-')
			result = divide(&x[1], y);
		else if(x[0] != '-' && y[0] == '-')
			result = divide(x, &y[1]);
		temp = (char *)malloc(strlen(result) + 2);
		temp[0] = '-';
		temp[1] = '\0';
		strcat(temp, result);
		return temp;
	}
	return result;
}
