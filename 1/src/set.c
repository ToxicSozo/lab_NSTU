#include "../include/set.h"

Set *create_set(int capacity) {
    Set *set = malloc(sizeof(Set));
    set->elements = (int *)malloc(capacity * sizeof(int));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

bool contains(Set *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return true;
        }
    }
    return false;
}

void resize_set(Set *set) {
    set->capacity *= 2;
    set->elements = realloc(set->elements, set->capacity * sizeof(int));
}

void set_add(Set *set, int element) {
    if(set->size == set->capacity) {
        resize_set(set);
    }

    if (contains(set, element)) {
        return;
    }

    if (set->size == set->capacity) {
        set->capacity *= 2;
        set->elements = (int *)realloc(set->elements, set->capacity * sizeof(int));
    }

    set->elements[set->size] = element;
    set->size++;
}

void set_at(Set *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            printf("Элемент %d найден в множестве.\n", element);
            return;
        }
    }
    printf("Элемент %d не найден в множестве.\n", element);
}

void set_del(Set *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            return;
        }
    }
}

void free_set(Set *set) {
    free(set->elements);
    free(set);
}
