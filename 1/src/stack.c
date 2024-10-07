#include "../include/stack.h"

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

stack* push(stack* top, const char* value) {
    stack* ptr = (stack*)malloc(sizeof(stack));
    ptr->data = strdup(value);  // Копируем строку
    ptr->next = top;
    return ptr;
}

stack* pop(stack* top) {
    if (top == NULL) return NULL;

    stack* ptr = top->next;
    free(top->data);
    free(top);
    return ptr;
}

void show(const stack* top) {
    const stack* current = top;

    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    printf("\n");
}

void free_stack(stack* top) {
    while (top != NULL) {
        top = pop(top);
    }
}

stack* reverse_stack(stack* top) {
    stack* new_top = NULL;
    while (top != NULL) {
        new_top = push(new_top, top->data);
        top = pop(top);
    }
    return new_top;
}