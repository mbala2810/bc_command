#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*char ninecomp(char a){
	char c = '9' - ((int)a - '0');
	printf("%c\n",c);
	return c;
}*/
char *sub(char *a, char *b){
	char *c = (char *)malloc(101 * sizeof(char));
	int i, k, count;
	char *s = (char *)malloc(101 * sizeof(char));
	int x = strlen(a);
	int y = strlen(b);
	//printf("a = %s b = %s\n",a, b);
	int dota = 0;
	int dotb = 0;
	int j, x1 = x;
	int y1 = y;
	for(i = 0; i < x1; i++){
		if(a[i] == '0'){
			for(j = 0; j < x1; j++)
				a[j] = a[j + 1];
			x--;
			x1 = x;
			i = 0;
		}
		else
			break;
	}
	for(i = 0; i < y1; i++){
		if(b[i] == '0'){
			for(j = i; j < y1; j++)
				b[j] = b[j + 1];
			y--;
			y1 = y;
			i = 0;
		}
		else
			break;
	}
	for(i = 0; a[i] != '.' && a[i] != '\0'; i++)
		dota++;
	for(i = 0; b[i] != '.' && b[i] != '\0'; i++)
		dotb++;
	int m = (x - dota - 1) - (y - dotb - 1);
	if(m > 0){
		for(i = y, j = 0; j < m; j++, i++){
			if(dotb == y && j == 0)
				b[i] = '.';
			else
				b[i] = '0';
		}
		y = i;
		b[i] = '\0';
	}
	else if(m < 0){
		m = -m;
		for(i = x, j = 0; j < m; j++, i++){
			if(dota == x && j == 0)
				a[i] = '.';
			else
				a[i] = '0';
		}
		x = i;
		a[i] = '\0';
	}
	if(x > y)
		count = 1;
	else if(x < y)
		count = 0;
	else
		count = 2;
	int l, check = 0;
	if(count == 2){
			if(a[0] > b[0]){
				count = 1;
				check = 1;
			}
			else if(a[0] < b[0]){
				count = 0;
				check = 1;
			}
	}
	if(check == 0 && count == 2){
		for(i = 1, j = 1; i < x; i++, j++){
			if(a[i] > b[j]){
				count = 1;
				break;
			}
			else if(a[i] < b[j]){
				count = 0;
				break;
			}
		}
		if(i == x)
			count = 1;
	}
	int temp, d;
		for(i = x - 1,j = y - 1, k = 0; i >= 0 || j >= 0; k++){
			if(a[i] == '.' || b[j] == '.'){
				c[k] = '.';
				i--;
				j--;
				continue;
			}
			if(count == 1){
				if(j != -1){
					if(a[i] >= b[j])
						temp = a[i] - b[j];
					else{
						temp = 10 + a[i] - b[j];
						if(a[i - 1] != '.' && a[i - 1] != '0')
							a[i - 1] = a[i - 1] - 1;
						else if(a[i - 1] == '.' && a[i - 2] != '0')
							a[i - 2] = a[i - 2] - 1;
						else if(a[i - 1] == '0'){
							for(d = i - 1; a[d] == '0'; d--){
								a[d] = '9';
							}
							a[d] = a[d] - 1;
						}
						else if(a[i - 1] == '.' && a[i - 2] == '0'){
							for(d = i - 2; a[d] == '0'; d--){
								a[d] = '9';
							}
							a[d] = a[d] - 1;
						}	
					}	
					i--;
					j--;
				}
				else{
					temp = a[i] - '0';
					i--;
				}
			}
			else if(count == 0){
				if(i != -1){
					if(b[j] >= a[i])
						temp = b[j] - a[i];
					else{
						temp = 10 + b[j] - a[i];
						if(b[j - 1] != '.' && b[j - 1] != '0')
							b[j - 1] = b[j - 1] - 1;
						else if(b[j - 1] == '.' && b[j - 2] != '0')
							b[j - 2] = b[j - 2] - 1;
						else if(b[j - 1] == '0'){
							for(d = j - 1; b[d] == '0'; d--){
								b[d] = '9';
							}
							b[d] = b[d] - 1;
						}
						else if(b[j - 1] == '.' && b[j - 2] == '0'){
							for(d = j - 2; b[d] == '0'; d--){
								b[d] = '9';
							}
							b[d] = b[d] - 1;
						}	
					}
					i--;
					j--;
				}
				else{
					temp = b[j] - '0';
					j--;
				}
			}
			c[k] = temp + '0';

	}
	int z = k;
	for(i = z - 1; i > 0; i--){
		if(c[i] == '0' && c[i - 1] != '.')
			k--;
		else 
			break;
	}
	if(count == 0){
			c[k] = '-';
			l = k;
	}
	else
		l = k - 1;
	for(i = 0, j = l; j >= 0; j--, i++)
		s[i] = c[j];
	s[i] = '\0';
	return s;
}
int main(){
	char *a = (char *)malloc(100 * sizeof(char));
	char *b = (char *)malloc(100 * sizeof(char));
	scanf("%s%s", a, b);
//	char *s = sub(a, b);
	char *s = (char *)malloc(100 * sizeof(char));
	strcpy(s, a);
	char *t = (char *)malloc(100 * sizeof(char));
	strcpy(t, b);
	int count = 0;
	while(1){
		s = sub(s, t);
		strcpy(t, b);
		count++;
		//printf("s = %s\n",s);
		if(s[0] == '-')
			break;
	}
	printf("ans = %d\n", count - 1);
	return 0;
}
