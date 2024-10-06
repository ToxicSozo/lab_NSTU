#include "../include/stack.h"

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
 
stack* push(stack* top, char value) { 
    stack* ptr = (stack*)malloc(sizeof(stack)); 
    ptr->data = value; 
    ptr->next = top; 
    return ptr; 
} 
 
stack* pop(stack* top) { 
    if (top == NULL) return NULL; 
 
    stack* ptr = top->next; 
    free(top); 
    return ptr; 
} 
 
void show(const stack* top) { 
    const stack* current = top; 
 
    while (current != NULL) { 
        printf("%c\n", current->data); 
        current = current->next; 
    } 
 
    printf("\n"); 
}