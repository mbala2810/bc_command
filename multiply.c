
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
#include<math.h>
#include"integer.h"
int len;
/*Creates a node from the string*/
Integer CreateIntegerFromString(char *s){
	Integer l;
	init(&l);
	int count;
	char *a = (char *)malloc(4);
	int i, x;
	int j = strlen(s) - 1;
	if(s[0] == '-'){
		x = 1;
		l.flag = 1;
	}
	else{ 
		x = 0;
		l.flag = 0;
	}
	LOOP:
	i = 0;
	count = 0;
	while(j >= x && i < 4){
		if(s[j] == '.'){
			j--;
			dotlen = len;
			continue;
		}
		a[i] = s[j];
		i++;
		j--;
		len++;
		count++;
	}
	char *c = (char *)malloc(count + 1);
	int k;
	for(i = count - 1, k = 0; i >= 0; i--, k++)
		c[k] = a[i];
	c[k] = '\0';
	insert(&l, c);
	if(j == x - 1){
		free(a);
		free(c);
		return l;
	}
	else
		goto LOOP;
}
/*works just as itoa*/
char *myitoa(int i){
	int j, k = 0;
	char *s = (char *)malloc(4);
	while(i){
		j = i % 10;
		i = i / 10;
		s[k] = j + '0';
		k++;
	}
	if(check == 0){
		if(k != len1){
			for(;k < len1; k++)
				s[k] = '0';
		}
	}
	if(check == 1){
		if(k != len2){
			for(;k < len2; k++)
				s[k] = '0';
		}
	}
	s[k] = '\0';
	char *c = (char *)malloc(k + 1);
	for(i = 0; k > 0; i++, k--)
		c[i] = s[k - 1];
	c[i] = '\0';
	free(s);
	return c;
}
/* multiplication of two numbers using nodes*/
Integer Mul(Integer p1, Integer p2){
	Integer pro;
	init(&pro);
	char *str;
	node *temp1, *temp2;
	temp1 = p1.head;
	temp2 = p2.head;
	int carry = 0;
	int k, i, h;
	while(temp1 != NULL){
		i = carry + atoi(temp1->str) * atoi(temp2->str);
		len1 = strlen(temp1->str);
		len2 = strlen(temp2->str);
		if(len1 >= len2){
			k = pow(10, len1);
                        check = 0;
                }
                else{
                        k = pow(10, len2);
                       check = 1;
		}
		carry = i / k;
		i = i % k;
		if(i == 0){
			if(check == 0){
				str = (char*)malloc(len1);
				for(h = 0; h < len1; h++)
					str[h] = '0';
				str[h] = '\0';
			}
			else{
				str = (char*)malloc(len2);
				for(h = 0; h < len2; h++)
					str[h] = '0';
				str[h] = '\0';
			}
		}
		else
			str = myitoa(i);
		insert(&pro, str);
		temp1 = temp1->next;
	}
	if(carry != 0){
		str = myitoa(carry);
		insert(&pro, str);
	}
	carry = 0;
	temp2 = temp2->next;
	if(temp1 == NULL && temp2 == NULL)
		return pro;
	temp1 = p1.head;
	node *temp = pro.head->next;
	node *p = pro.head->next;
	int pos = 1, j = pos;
	while(temp2 != NULL){
		temp1 = p1.head;
		carry = 0;
		while(temp1 != NULL){
			if(temp != NULL)
				i = carry + atoi(temp->str) + atoi(temp1->str) * atoi(temp2->str);
			else
				i = carry + atoi(temp1->str) * atoi(temp2->str);
			len1 = strlen(temp1->str);
			len2 = strlen(temp2->str);
			if(len1 >= len2){	
				k = pow(10, len1);
        	    check = 0;
        	 }
        	 else{
        	    k = pow(10, len2);
        	    check = 1;
			}
			carry = i / k;
			i = i % k;
			if(i == 0){
				if(check == 0){
				str = (char*)malloc(len1);
				for(h = 0; h < len1; h++)
					str[h] = '0';
				str[h] = '\0';
				}
				else{
				str = (char*)malloc(len2);
				for(h = 0; h < len2; h++)
					str[h] = '0';
				str[h] = '\0';
				}
			}
			else
				str = myitoa(i);
			if(pos != pro.len){
				replace(&pro, str, pos);
				pos++;
				temp = temp->next;
			}
			else
				insert(&pro, str);
			temp1 = temp1->next;
		}
		if(carry != 0){
			str = myitoa(carry);
			insert(&pro, str);
		}
		temp2 = temp2->next;
		if(p != NULL)
			p = p->next;
		temp = p;
		pos = j + 1;
		j = pos;
	}
	free(str);
	return pro;
}
/* returns the number of integers present after decimal point*/
int checkdot(char *s){
	int i = 0;
	while(s[i] != '.' && s[i] != '\0')
		i++;
	if(s[i] == '.')
		return strlen(s) - i - 1;	
	else
		return 0;
}
/* length of final answer i.e. product*/
int ans_length(Integer l){
	node *p = l.head;
	int i = 0;
	while(p != NULL){
		i = i + strlen(p->str);
		p = p->next;
	}
	return i;
}
/*Converts the node again into string*/
char *CreateStringfromnode(Integer l){
	char *ans;
	if(len_ans - dotlen >= 0)
		ans = (char *)malloc(len_ans + 2);
	else
		ans = (char *)malloc(dotlen + 2);
	node *p;
	p = l.tail;
	int len = len_ans - dotlen;
	int n = 0, count = 0, i = 0, k = 0, check = 0;
	do{
		k = strlen(p->str);
		if(dotlen == 0){
			for(n = 0; n < k; n++){
				if(p->str[n] == '0' && check != 1);
				else{
					ans[i] = p->str[n];
					i++;
					check = 1;
				}
			}
		}
		else {
			if(len < 0){
				ans[0] = '.';
				for(i = 1; len != 0; i++){
					ans[i] = '0';
					len++;
					check = 1;
				}
			}
			for(n = 0; n < k; n++){
				if(len_ans - dotlen == count){
					ans[i] = '.';
					i++;
					count++;
					check = 1;
					n--;
					continue;
				}
				if(p->str[n] == '0' && check != 1);
				else{
					ans[i] = p->str[n];
					i++;
					check = 1;
				}
				count++;
			}

		}
		free(p->str);
		p = p->prev;
	}while(p != NULL);
	ans[i] = '\0';
	free(l.head);
	return ans;
}
char *multiply(char *s, char *p){
	if(strcmp(s, "0") == 0 || strcmp(p, "0") == 0)
		return "0";
	Integer I, J;
	if(strlen(s) >= strlen(p)){
		I = CreateIntegerFromString(s);
		J = CreateIntegerFromString(p);
	}
	else{
		I = CreateIntegerFromString(p);
		J = CreateIntegerFromString(s);
	}
	dotlen = checkdot(s) + checkdot(p);
	Integer pro;
	pro = Mul(I, J);
	len_ans = ans_length(pro);
	char *final = CreateStringfromnode(pro);
	return final;
}
/* mul function handles negative and positive integers and accordingly calls multiply*/
char *mul(char *x, char *y){
	char *temp, *result;
	if(x[0] == '-' && y[0] == '-')
		result = multiply(&x[1], &y[1]);
	else if(x[0] != '-' && y[0] != '-')
		result = multiply(x, y);
	else {
		if(x[0] == '-' && y[0] != '-'){
			result = multiply(&x[1], y);	
		}
		else if(x[0] != '-' && y[0] == '-'){
			result = multiply(x, &y[1]);
		}
		temp = (char *)malloc(strlen(result) + 2);
		temp[0] = '-';
		temp[1] = '\0';
		strcat(temp, result);
		return temp;
	}
	return result;
}
