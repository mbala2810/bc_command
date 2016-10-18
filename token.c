#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#define SIZE 128
enum states { SPC, DIG, OPR, STOP, ERR};
char c;
token *getnext(char *arr, int *reset) {
	static int currstate, k, prevstate;
	int nextstate;
	static int i;
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
			case '%': case '(': case ')': 
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ': case ',':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(nextstate == DIG){
					if(prevstate == OPR){
						t->s[j] = c;
						prevstate = SPC;
						j++;
					}
					t->s[j] = arr[i];
					j++;
				}
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
			case OPR:
				if(nextstate == DIG){
					c = arr[i];
					prevstate = OPR;
				}
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				i++;
				return t;
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
