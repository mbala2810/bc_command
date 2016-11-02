
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


#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "integer.h"
#include "token.h"
/*calc is a function which returns the answer after the operation*/
char* calc(char *x, char *y, char op){
	char *result, *temp;
	int res;
	switch(op){
		case '+':
			result = addition(x, y);
			break;
		case '-':
			result = subtract(x, y);
			break;
		case '*':
			result = mul(x, y);	
			break;
		case '/':
			result = divides(x, y);		
			break;
		case '%':
			if(x[0] != '-' && y[0] != '-')
				result = modulus(x, y);
			else if(x[0] != '-' && y[0] == '-')
				result = modulus(x, &y[1]);
			else{
				if(x[0] == '-' && y[0] != '-')
					result = modulus(&x[1], y);
				else if(x[0] == '-' && y[0] == '-')
					result = modulus(&x[1], &y[1]);
				temp = (char *)malloc(strlen(result) + 2);
				temp[0] = '-';
				temp[1] = '\0';
				strcat(temp, result);
				return temp;
			}
			break;
		case '^':
			if(strlen(y) > 10 || checkdot(y) != 0){
				return NULL;
			}
			if(x[0] == '-' && y[0] != '-'){
				result = power(&x[1], atoi(y));
				if(atoi(y) % 2 == 1){
					temp = (char *)malloc(strlen(result) + 2);
					temp[0] = '-';
					temp[1] = '\0';
					strcat(temp, result);
					return temp;
				}	
				else
					return result;
			}
			if(x[0] == '-' && y[0] == '-'){
				result = power(&x[1], atoi(y));
				if(atoi(y) % 2 == 1){
					temp = (char *)malloc(strlen(result) + 2);
					temp[0] = '-';
					temp[1] = '\0';
					strcat(temp, result);
					temp = divides("1", temp);
					return temp;
				}	
				else{
					result = divides("1", result);
					return result;
				}
			}

			if(y[0] != '-')
				result = power(x, atoi(y));
			else{
				result = power(x, atoi(&y[1]));
				result = divide("1", result);
			}
			break;
		case '@':
			if(strcmp(x, "0") == 0 && strcmp(y, "0") == 0)
				return "0";
			else
				return "1";
			break;
		case '~':
			if(strcmp(x, "0") == 0 || strcmp(y, "0") == 0)
				return "0";
			else
				return "1";
		case '>':
			if(x[0] == '-' && y[0] != '-')
				return "0";
			else if(x[0] != '-' && y[0] == '-')
				return "1";
			res = compare(x, y);
			if(res > 0)
				return "1";
			else
				return "0";
			break;
		case '<':
			if(x[0] == '-' && y[0] != '-')
				return "1";
			else if(x[0] != '-' && y[0] == '-')
				return "0";
			res = compare(x, y);
			if(res >= 0)
				return "0";
			else
				return "1";
			break;
		case '=':									/* same as == */
			res = compare(x, y);
			if(res == 0)
				return "1";
			else
				return "0";
			break;
		case '$':									/* $ same as >= */
			if(x[0] == '-' && y[0] != '-')
				return "0";
			else if(x[0] != '-' && y[0] == '-')
				return "1";
			res = compare(x, y);
			if(res >= 0)
				return "1";
			else
				return "0";
			break;
		case '#':									/* # same as <= */
			if(x[0] == '-' && y[0] != '-')
				return "1";
			else if(x[0] != '-' && y[0] == '-')
				return "0";
			res = compare(x, y);
			if(res > 0)
				return "0";
			else
				return "1";
			break;
	}
	return result;
}
