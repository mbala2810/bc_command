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
	while((ch = getchar()) != '\n' && i < len - 1) {
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
int precendence(char s){
	switch(s){
		case '!':
			return 0;
			break;
		case '+': case '-':
			return 1;
			break;
		case '*': case '/':
			return 2;
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
	//			printf("%c\n", t->op);
				if(t->op == '('){
					result = infixeval(str);
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
		pushopnd(&a, result);
	}
		return popopnd(&a);
}

int main(int argc, char *argv[]){
	char str[128];
	int x, reset = 1;
	int i;
	char *ans;
	token *t;
	if(argc == 1)
		goto LOOP1;
	if(strcmp(argv[1],"-h") == 0){
LOOP1:		printf("usage: ./project [options]\n");
			printf("  -h --help       print this usage and exit\n");
			printf("  -p --postfix    evaluates postfix expression\n");
			printf("  -i --infix      evaluates infix expression\n");
			printf("  -l --mathlib    math library functions\n");
			return 0;
	}
	else if(strcmp(argv[1], "-i") == 0){
			printf("Enter infix expression (other than division or mod or power)\n");	
			i = 1;
	}
	else if(strcmp(argv[1], "-p") == 0){
			printf("Enter postfix expression (other than division or mod or power)\n");	
			i = 2;
	}
	else if(strcmp(argv[1], "-l") == 0){
		printf("Math library functions not yet added\n");
		return 0;
	}
	else{
		goto LOOP1;
	}

	while((x = readline(str, 1024))) {
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
			if(test == 1)
				printf("-");
			fprintf(stdout, "%s\n", ans);
		}
	}
	return 0;
}
