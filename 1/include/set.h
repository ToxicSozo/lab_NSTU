#ifndef SET_H
#define SET_H   

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Set {
    char **elements;
    size_t capacity;
    size_t size;
} Set;

Set *create_set(int capacity);
bool contains(Set *set, const char *element);
void set_add(Set *set, const char *element);
void set_at(Set *set, const char *element);
void set_del(Set *set, const char *element);
void free_set(Set *set);

#endif