
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"integer.h"
/*DOUBLY LINKED NULL TERMINATED LIST*/
/* intialises the Integer*/
void init(Integer *i){
	i->tail = i->head = NULL;
	i->len = 0;
	return;
}
/*returns length of Integer *l*/
int length(Integer *l){
	return l->len;
}
/* appends a node at the end*/
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
/* Replaces a given string with the given string at given position*/
void replace(Integer *l, char *s, int pos){
	node *p;
	p = l->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	strcpy(p->str, s);
	return;
}
