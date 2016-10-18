#include "integer.h"
#include "token.h"
char* calc(char *x, char *y, char op){
	char *result;
	Integer I;
	Integer J;
	test = 0;
	switch(op){
		case '+':
			result = add(x, y);
			break;
		case '-':
			if(x[0] == '-'){
				result = add(&x[1], y);
				test = 1;
			}
			else
				result = sub(x, y);
			break;
		case '*':
			I = CreateIntegerFromString(x);
			J = CreateIntegerFromString(y);
			dotlen = checkdot(x) + checkdot(y);
			Integer pro;
			pro = Mul(I, J);
			len_ans = ans_length(pro);
			result = CreateStringfromnode(pro);
			break;/*
		case '/':
			result = x / y;
			break;*/
	}
	return result;
}
