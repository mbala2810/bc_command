
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

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "oprndstack.h"
#include "integer.h"
#include <string.h>
#define SIZE 128
enum states { SPC, DIG, OPR, OPND, SPEC_OPR, STOP, ERR};
char c;
/*Returns a token which maybe operator, operand , error or end*/
token *getnext(char *arr, int *reset) {
	static int currstate, k, prevstate;
	int nextstate;
	static int i;
	int count = 0;
	if(*reset == 1){
		*reset = 0;
		i = 0;
		prevstate = SPC;
		currstate = SPC;
		return NULL;
	}
	token *t = (token *)malloc(sizeof(token));
	t->s = (char *)malloc(SIZE);
	int j = 0;
	j = k;

	int size = SIZE;
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '>':
			case '<': case '=': case '|': case '&':
			case '^':
				nextstate = OPR;
				break;
			case 's': case 'c': case 't':
				nextstate = SPEC_OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ': case ',':
				nextstate = SPC;
				break;
			case 'p':
				nextstate = OPND;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(nextstate == OPR && (arr[0] == '-' || arr[0] == '+')){
					t->s[j] = arr[0];
					j++;
					nextstate = DIG;
					break;
				}
				else if(nextstate == DIG){
					if(prevstate == OPR){
						t->s[j] = c;
						prevstate = SPC;
						j++;
					}
					t->s[j] = arr[i];
					j++;
				}
				else if(nextstate == SPEC_OPR){
					if(arr[i + 1] != '('){
						t->type = ERROR;
						return t;
					}
				}
				break;
			case SPEC_OPR:
				t->op = arr[i - 1];
				currstate = nextstate;
				t->type = OPERATOR;
				i++;
				return t;
				break;
			case DIG:
				if(nextstate == DIG){
					if(j == size - 1){
						size = size + 128;
						t->s = (char *)realloc(t->s, size);
					}
					if(prevstate == OPR){
						t->s[j] = c;
						prevstate = SPC;
						j++;
					}
					t->s[j] = arr[i];
					j++;
				}
				else  {
					if(prevstate == OPR){
						t->s[j] = c;
						prevstate = SPC;
						j++;
					}
					t->type = OPERAND;
					currstate = nextstate;
					i++;
					t->s[j] = '\0';
					return t;
				}
				break;
			case OPND:
				if(!iempty(&s1)){
					t->s = popopnd(&s1);
					t->type = OPERAND;
					currstate = nextstate;
					i++;
					pushopnd(&s1, t->s);
				}
				else
					t->type = ERROR;
				return t;
				break;
			case OPR:
				if(nextstate == DIG){
					c = arr[i];
					prevstate = OPR;
				}
				else if(nextstate == SPEC_OPR){
					if(arr[i + 1] != '('){
						t->type = ERROR;
						return t;
					}
					break;
				}

				t->type = OPERATOR;
				if((nextstate != OPR && count == 0 )|| arr[i] == '(' || arr[i] == ')'){
					if(i == 0)
						t->op = arr[0];
					else
						t->op = arr[i - 1];	
					currstate = nextstate;
					i++;
					return t;
				}
				else if(count == 1 || nextstate == OPR){
					if(count == 1){
						if(arr[i - 1] == '=' && arr[i - 2] == '>')
							t->op = '$';									/* $ same as >= */
						else if(arr[i - 1] == '=' && arr[i - 2] == '=')
							t->op = '=';									/* = same as == */
						else if(arr[i - 1] == '=' && arr[i - 2] == '<')
							t->op = '#';									/* # same as <= */
						else if(arr[i - 1] == '|' && arr[i - 2] == '|')
							t->op = '@'	;									/* @ same as || (logical or) */
						else if(arr[i - 1] == '&' && arr[i - 2] == '&')
							t->op = '~';										/* ~ same as && (logical and) */
						else
							t->type = ERROR;
						currstate = nextstate;
						i++;
						return t;
					}
					count = 1;
				}
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				i++;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				i++;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}
int obasechecker(char *str){
	int i = 0, j = 0;
	char s[3];
	if(str[0] != ' ' && str[0] != 'o')
		return 0;
	while(str[i] != '\0'){
		if(str[i] == 'o'){
			char c[6];
			memcpy(c, &str[i], 5);
			c[5] = '\0';
			if(strcmp(c, "obase") == 0){
				check = 1;
			}
			else
				return 0;
			i = i + 5;
		}
		else if(str[i] == ' ' || str[i] == '=')
			i++;
		if(check == 1){
			if(str[i] >= '0' && str[i] <= '9'){
				if(strlen(str) - i > 2){
					printf("base should be between 2 and 16");
					return 0;
				}
				while(str[i] != '\0'){
					s[j] = str[i];
					i++;
					j++;
				}
				s[j] = '\0';
			}
		}
	}
	if(check != 1)
		return 0;
	i = atoi(s);
	if(i > 16){
		printf("base should be between 2 and 16");
		return 0;
	}
	return i;
}
