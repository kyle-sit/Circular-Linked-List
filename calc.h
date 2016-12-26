/****************************************
*					*
*	DO NOT CHANGE THIS FILE		*
*					*
****************************************/

#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include "stack.h"

/* declare public functions for stack words */
void delete_CalcWord (void *);
FILE * write_CalcWord (void *, FILE *);

/* basic calculator functions */
long eval (Stack *);
long intopost (Stack *);

#endif
