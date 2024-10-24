#include "../include/set.h"

Set *create_set(int capacity) {
    Set *set = malloc(sizeof(Set));
    set->elements = (char **)malloc(capacity * sizeof(char *));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

bool contains(Set *set, const char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            return true;
        }
    }
    return false;
}

void resize_set(Set *set) {
    set->capacity *= 2;
    set->elements = realloc(set->elements, set->capacity * sizeof(char *));
}

void set_add(Set *set, const char *element) {
    if (set->size == set->capacity) {
        resize_set(set);
    }

    if (contains(set, element)) {
        return;
    }

    set->elements[set->size] = strdup(element);
    set->size++;
}

void set_at(Set *set, const char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            printf("Элемент '%s' найден в множестве.\n", element);
            return;
        }
    }
    printf("Элемент '%s' не найден в множестве.\n", element);
}

void set_del(Set *set, const char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            free(set->elements[i]);
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            return;
        }
    }
}

void free_set(Set *set) {
    for (int i = 0; i < set->size; i++) {
        free(set->elements[i]);
    }
    free(set->elements);
    free(set);
}