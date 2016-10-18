#define OPERAND 10 
#define OPERATOR 20
#define	END	30
#define ERROR	40

typedef struct token{
	int type;	// type takes values OPERAND/OPERATOR/END/
	char *s;
	char op;
}token;
int test;
char *add(char *a, char *b);
char *sub(char *a, char *b);
char *calc(char *x, char *y, char op);
char *postfix(char *s);
token *getnext(char *, int *);
