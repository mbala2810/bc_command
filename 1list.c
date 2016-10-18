#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"integer.h"

void init(Integer *i){
	i->tail = i->head = NULL;
	i->len = 0;
	return;
}

int length(Integer *l){
	return l->len;
}

void insert(Integer *l, char *s){
	node *temp;
	temp = (node *)malloc(sizeof(node));
	temp->str = (char *)malloc(strlen(s) + 1);
	strcpy(temp->str, s);
	if(l->head == NULL){
		l->head = l->tail = temp;
		temp->next = temp->prev = NULL;		
		l->len++;
		return;
	}
	int i;
	node *p = l->head;
	for(i = 0; i < l->len - 1; i++)
		p = p->next;
		
	p->next = temp;
	temp->next = NULL;
	l->tail = temp;
	temp->prev = p;
	l->len++;
	return;
}
void replace(Integer *l, char *s, int pos){
	node *p;
	p = l->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	strcpy(p->str, s);
	return;
}
