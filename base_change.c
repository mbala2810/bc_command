#include<stdio.h>
#include<stdlib.h>

char *base_change(int a, int n){
	char *b = (char *)malloc(100 * sizeof(char));
	int i = 0;
	int t;
	while(a){
		t = a % n;
		if(t < 10)
			b[i++] = t + '1' - 1;
	    else if(t >= 10)
			b[i++] = t + 'A' - 10;
		a = a / n;
	}
	char *c = (char *)malloc(100 * sizeof(char));
	int j = i;
	int k;
	for(i = j - 1, k = 0; i >= 0; i--, k++)
		c[k] = b[i];
	c[k] = '\0';
	return c;
}
int main(){
	int a, n;
	scanf("%d%d", &a, &n);
	char *c = base_change(a, n);
	printf("%s\n", c);

}
