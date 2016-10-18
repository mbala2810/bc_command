#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "oprndstack.h"
char *postfix(char *str) {
	token *t;
	char *x, *y;
	char *result;
	oprndstack a;
	inits(&a);
	int reset = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND) { 
			pushopnd(&a, t->s);
		}
		else if (t->type == OPERATOR) { 
			if(!iempty(&a))
				x = popopnd(&a);
			else
				return NULL; 
			if(!iempty(&a))
				y = popopnd(&a);
			else
				return NULL; 
			result = calc(y, x, t->op);
			pushopnd(&a, result);
		}
		else if (t->type == ERROR) 
			return NULL; 
		else {
			if(!iempty(&a))
				result = popopnd(&a);
			else
				return NULL;
			if(iempty(&a))
				return result;
			else
				return NULL; 
		}
	}
}
