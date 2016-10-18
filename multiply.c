#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"integer.h"
int len;
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
	if(j == x - 1)
		return l;
	else
		goto LOOP;
}
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
	return c;
}
Integer Mul(Integer p1, Integer p2){
	Integer pro;
	init(&pro);
	char *str;
	node *temp1, *temp2;
	temp1 = p1.head;
	temp2 = p2.head;
	int carry = 0;
	int k, i;
	int len;
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
		p = p->next;
		temp = p;
		pos = j + 1;
		j = pos;
	}

	return pro;
}
int checkdot(char *s){
	int i = 0;
	while(s[i] != '.' && s[i] != '\0')
		i++;
	if(s[i] == '.')
		return strlen(s) - i - 1;	
	else
		return 0;
}
int ans_length(Integer l){
	node *p = l.head;
	int i = 0;
	while(p != NULL){
		i = i + strlen(p->str);
		p = p->next;
	}
	return i;
}
char *CreateStringfromnode(Integer l){
	char *ans;
	ans = (char *)malloc(len_ans + 2);
	node *p;
	p = l.tail;
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
		p = p->prev;
	}while(p != NULL);
	ans[i] = '\0';
	return ans;
}
