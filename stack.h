/****************************************
*					*
*	DO NOT CHANGE THIS FILE		*
*					*
****************************************/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include "list.h"

typedef struct List Stack;

void delete_Stack (Stack **);
long isempty_Stack (Stack *);
Stack * new_Stack (void *(*copy_func) (void *),
        void (*delete_func) (void *),
        FILE *(*write_func) (void *, FILE *));
void * pop (Stack *);
long push (Stack *, void * element);
void * top (Stack *);
FILE * write_Stack (Stack *, FILE *);

#endif
