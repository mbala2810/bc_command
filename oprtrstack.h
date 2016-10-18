typedef struct oprtrstack{
	char c[128];
	int i;
}oprtrstack;

void pushoptr(oprtrstack *s, char ch);
int popoptr(oprtrstack *s);
int cempty(oprtrstack *s);
void initop(oprtrstack *s);