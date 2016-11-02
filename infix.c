
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
#include <limits.h>
#include <string.h>
#include "oprtrstack.h"
#include "oprndstack.h"
#include "token.h"
#include "integer.h"
/*Reads the string inputted by the user and stores it in an character array
 */
int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n') {
		if(i == len - 1){
			len = len + 1024;
			arr = (char *)realloc(arr, len + 1);
		}
		arr[i] = ch;
		i++;
	}
	/*Need to add the null character at the end to make it a string
	 */
	arr[i] = '\0';
	return i;
}
/*A function precedence which returns the value of the precedence of an operator
 */
int quitornot(char *s){
	if(strcmp(s, "quit") == 0)
		return 0;
	else
		return 1;
}
int precendence(char s){
	switch(s){
		case '!':
			return 0;
			break;
		case '>': case '<':
		case '=': case '$':
		case '#':
			return 1;
			break;
		case '@': case '~':				/* @ same as logical or and ~ same as logical and*/
			return 2;
			break;
		case '+': case '-':
			return 3;
			break;
		case '*': case '/':
			return 4;
			break;
		case '%':
			return 5;
			break;
		case '^':
			return 6;
			break;
	}
	return -1;
}
char *infixeval(char *str) {
	token *t;
	char *result;
	oprndstack a;
	oprtrstack s;
	inits(&a);
	initop(&s);
	int reset = 0;
	char op;
	char  *x, *y;
	pushoptr(&s, '!');
	while(1) {
		t = getnext(str, &reset);
LOOP:	if(t->type == OPERAND) { 
			pushopnd(&a, t->s);
		}
		else if (t->type == OPERATOR) { 
				if(t->op == 's' || t->op == 'c' || t->op == 't'){
					char op = t->op;
					char *ans = infixeval(str);
					switch(op){
						case 's':
							ans = sine(ans);
							pushopnd(&a, ans);
							break;
						case 'c':
							ans = cosine(ans);
							pushopnd(&a, ans);
							break;
						case 't':
							ans = tangent(ans);
							pushopnd(&a, ans);
							break;
					}
					t = getnext(str, &reset);
					if(t->type != END)
						goto LOOP;
					else
						break;
				}
				if(t->op == '('){
					result = infixeval(str);
					if(result == NULL)
						return NULL;
					pushopnd(&a, result);
					t = getnext(str, &reset);
					if(t->type != END){
							goto LOOP;
					}
					else
						break;
				}
				else if(t->op == ')'){
					break;
				}
				if(!cempty(&s))	
					op = popoptr(&s);
				else
					return NULL;	
				if(precendence(op) < precendence(t->op)){
					pushoptr(&s, op);
					pushoptr(&s, t->op);
				}
				else{
					while(precendence(op) >= precendence(t->op)){
						if(!iempty(&a))
							x = popopnd(&a);
						else
							return NULL;
						if(!iempty(&a))
							y = popopnd(&a);
						else
							return NULL;
						result = calc(y, x, op);
						if(result == NULL)
							return NULL;
						pushopnd(&a, result);
						if(!cempty(&s))
							op = popoptr(&s);
						else
							return NULL;
					}
					pushoptr(&s, op);
					pushoptr(&s, t->op);
				}
		}
		else if(t->type == END){
			break;
		}
		else
			return NULL;
	}
	char ch;
	while((ch = popoptr(&s)) != '!'){
		if(!iempty(&a)){
			x = popopnd(&a);
		}
		else
			return NULL;
		if(!iempty(&a)){
			y = popopnd(&a);
		}
		else
			return NULL;
		result = calc(y, x, ch);
		if(result == NULL)
			return NULL;
		pushopnd(&a, result);
	}
		return popopnd(&a);
}
void printans(char *s){
	if(strlen(s) <= 70){
		printf("%s\n",s);
		return;
	}
	else{
		int i, len = strlen(s);
		for(i = 0; i < len; i++){
			printf("%c", s[i]);
			if(i % 70 == 0 && i != 0){
				printf("\\");
				printf("\n");
			}
		}
		printf("\n");
		return;
	}
}

int main(int argc, char *argv[]){
	char *str;
	str = (char *)malloc(1024);
	int x, reset = 1;
	int i;
	char *ans;
	token *t;
	if(argc == 1 ||  argc != 2 || strcmp(argv[1],"-h") == 0){
			printf("usage: ./project [options]\n");
			printf("  -h --help       print this usage and exit\n");
			printf("  -p --postfix    evaluates postfix expression\n");
			printf("  -i --infix      evaluates infix expression\n");
			return 0;
	}
	else if(strcmp(argv[1], "-i") == 0){
		printf("BASIC CALCULATOR\nfor sin, cos or tan use s(), c() and t() respectively and only one at a time\np remembers the previous result\n");
		printf("for changing output base use obase = base you want and base should be between 2 and 16\n");	
		printf("to exit enter quit\n\n");
		i = 1;
	}
	else if(strcmp(argv[1], "-p") == 0){
		printf("operators are +, -, / and * and two operands or operators can be separated by a space or comma\n");
		i = 2;
	}
	else{
		printf("usage: ./project [options]\n");
		printf("  -h --help       print this usage and exit\n");
		printf("  -p --postfix    evaluates postfix expression\n");
		printf("  -i --infix      evaluates infix expression\n");
		return 0;
	}
	int j, h = 0;
	while((x = readline(str, 1024))) {
		int q = quitornot(str);
		if(q == 0){
			free(str);
			return 0;
		}
		j = obasechecker(str);
		if(j == 0){
			t = getnext(str, &reset);
			if(i == 1)
				ans = infixeval(str);	
			else if(i == 2)
				ans = postfix(str);
			if(ans == NULL) {
				reset = 1;
				fprintf(stderr, "Error in expression\n");
			} 
	   		else{
				reset = 1;
				if(h != 0){
					ans = base_change(ans, h);
				}
				printans(ans);
			//	fprintf(stdout, "%s\n", ans);
				pushopnd(&s1, ans);
			}
		}
		if(h == 0 || j != 0){
			h = j;
			reset = 1;
		}
	}
	free(str);
	return 0;
}
