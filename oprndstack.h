typedef struct oprndstack{
	char *a[128];
	int i;
}oprndstack;

void pushopnd(oprndstack *s, char *n);
char *popopnd(oprndstack *s);
int iempty(oprndstack *s);
void inits(oprndstack *s);
