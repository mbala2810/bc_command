
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
