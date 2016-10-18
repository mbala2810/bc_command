typedef struct node{
	char *str;
	struct node *prev, *next;
}node;

typedef struct Integer{
	int len, flag;
	node *head, *tail;
}Integer;
void init(Integer *i);
int length(Integer *i);
void insert(Integer *i, char *s);
void traverse(Integer *i);
void replace(Integer *i, char *s, int pos);
Integer CreateIntegerFromString(char *s);
char *myitoa(int i);
Integer Mul(Integer I, Integer J);
int checkdot(char *s);
int ans_length(Integer i);
char *CreateStringfromnode(Integer i);
int sign, dotlen, len1, len2, check;
int len_ans;
