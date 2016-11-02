
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
void PrintInteger(Integer I);
int sign, dotlen, len1, len2, check;
int len_ans;
char *multiply(char *s, char *r);
char *mul(char *s, char *r);
char *addition(char *s, char *r);
char *subtract(char *s, char *r);
char *power(char *s, int y);
int find_ans(char *s, char *p);
char *div_ans(char *s, char *p);
char *divide(char *s, char *p);
int compare(char *s, char *r);
char *modulus(char *s, char *p);
char *sub1(char *s, char *p);
char *divides(char *s, char *p);
char *base_change(char *a, int n);
char *removezero(char *s);
char *inttochar(int n);
int obasechecker(char *s);
char *sine(char *s);
char *tangent(char *s);
char *cosine(char *s);
