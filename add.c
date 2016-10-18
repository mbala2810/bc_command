#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *add(char *a, char *b){
	char *c = (char *)malloc(strlen(a) + 2);
	char *s = (char *)malloc(strlen(a) + 2);
	int i, k, count;
	int x = strlen(a);
	int y = strlen(b);
	int dota = 0;
	int dotb = 0;
	int j;
	for(i = 0; a[i] != '.' && a[i] != '\0'; i++)
		dota++;
	for(i = 0; b[i] != '.' && b[i] != '\0'; i++)
		dotb++;
	int m = (x - dota - 1) - (y - dotb - 1);
	if(m > 0){
		for(i = y, j = 0; j < m; j++, i++)
			b[i] = '0';
		y = i;
		b[i] = '\0';
	}
	else if(m < 0){
		m = -m;
		for(i = x, j = 0; j < m; j++, i++)
			a[i] = '0';
		x = i;
		a[i] = '\0';
	}
	if(x > y)
		count = 1;
	else
		count = 0;

	int carry = 0, l;
	int ans, temp;
	
	for(i = x - 1,j = y - 1, k = 0; i >= 0 || j >= 0; k++){
			if(a[i] == '.'){
				c[k] = '.';
				i--;
				j--;
				continue;
			}
			if(count == 1){
				if(j != -1){
					ans = a[i] + b[j] + carry - '0' - '0';
					i--;
					j--;
				}
				else{
					ans = a[i] + carry - '0';
					i--;
				}
			}
			else if(count == 0){
				if(i != -1){
					ans = a[i] + b[j] + carry - '0' - '0';
					i--;
					j--;
				}
				else{
					ans = b[j] + carry - '0';
					j--;
				}
			}
			temp = ans % 10;
			carry = ans / 10;
			c[k] = temp + '0';
		}
	if(count == 1 && carry == 1 && i == -1){
			c[k] = carry + '0';
			l = k;
	}
	else if(count == 0 && carry == 1 && j == -1){
			c[k] = carry + '0';
			l = k;
	}
	else
		l = k - 1;
	int check = 0;
	i = 0;
	for(j = l; j >= 0; j--){
		if(c[j] == '0' && check != 1);
		else{
			s[i] = c[j];
			check = 1;
			i++;
		}
	}
	s[i] = '\0';
	return s;
}
