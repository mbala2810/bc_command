#include"oprtrstack.h"

void pushoptr(oprtrstack *s, char ch){
	s->c[s->i] = ch;
	(s->i)++;
}
int popoptr(oprtrstack *s){
	char ch = s->c[s->i - 1];
	(s->i)--;
	return ch;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack 
 */
void initop(oprtrstack *s){
	s->i = 0;
}
/* the caller should check that the stack is not empty before calling pop() 
 */
int cempty(oprtrstack *s){
	return s->i == 0;
}