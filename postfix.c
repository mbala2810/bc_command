
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


#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "oprndstack.h"
/*postfix calculator*/
char *postfix(char *str) {
	token *t;
	char *x, *y;
	char *result;
	oprndstack a;
	inits(&a);
	int reset = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND) { 
			pushopnd(&a, t->s);
		}
		else if (t->type == OPERATOR) { 
			if(!iempty(&a))
				x = popopnd(&a);
			else
				return NULL; 
			if(!iempty(&a))
				y = popopnd(&a);
			else
				return NULL; 
			result = calc(y, x, t->op);
			pushopnd(&a, result);
		}
		else if (t->type == ERROR) 
			return NULL; 
		else {
			if(!iempty(&a))
				result = popopnd(&a);
			else
				return NULL;
			if(iempty(&a))
				return result;
			else
				return NULL; 
		}
	}
}
