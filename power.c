
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
#include <string.h>
#include "integer.h"
/* power of two numbers where y is always an int*/
char *power(char *x, int y) {
	char *term, *result;
	result = (char *)malloc(2);
	result[0] = '1';
	result[1] = '\0';
	if(strcmp(x, "0") == 0) 
		if(y == 0) {
			return NULL;
		}
		else 
			return 	"0";
	else /* x!=0 */ {
		if(y == 0)
			return "1";
		else /* x!=0 y!=0 */{
			term = (char *)malloc(strlen(x) + 1);
			strcpy(term, x);
			while(y) {
				if(y % 2 == 1)
					result = multiply(result, term);
				y /= 2;
				term = multiply(term, term);
			}
		}	
	}
	return result;
}
