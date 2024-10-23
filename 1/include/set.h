#ifndef SET_H
#define SET_H   

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Set {
    int *elements;
    size_t capacity;
    size_t size;
} Set;

Set *create_set(int capacity);
bool contains(Set *set, int element);
void set_add(Set *set, int element);
void set_at(Set *set, int element);
void set_del(Set *set, int element);

#endif