#ifndef STACK_H
#define STACK_H

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

typedef struct _stack { 
    char *data; 
    struct _stack* next; 
} stack; 

stack* push(stack* top, const char* value);
stack* pop(stack* top);
void show(const stack* top);
void free_stack(stack* top);

stack* reverse_stack(stack* top);
#endif
