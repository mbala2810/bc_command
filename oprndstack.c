#include"oprndstack.h"
#include<stdlib.h>
#include<string.h>
void pushopnd(oprndstack *s, char *str){
	s->a[s->i] = (char *)malloc(strlen(str) + 1);
	strcpy(s->a[s->i], str);
	(s->i)++;
}
char *popopnd(oprndstack *s){
	char *t;
	t = (char *)malloc(strlen(s->a[s->i - 1]));
	strcpy(t, s->a[s->i - 1]);
	(s->i)--;
	return t;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack 
 */
void inits(oprndstack *s){
	s->i = 0;
}
/* the caller should check that the stack is not empty before calling pop() 
 */
int iempty(oprndstack *s){
	return s->i == 0;
}
