#include "../include/set.h"

// Хэш-функция
unsigned long hash_function(const char *str, size_t capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % capacity;
}

// Создание множества с хэш-таблицей
Set *create_set(int capacity) {
    Set *set = malloc(sizeof(Set));
    set->elements = (char **)malloc(capacity * sizeof(char *));
    set->hash_table = (char **)calloc(capacity, sizeof(char *));  // Инициализация хэш-таблицы
    set->size = 0;
    set->capacity = capacity;
    set->hash_capacity = capacity;
    return set;
}

// Проверка наличия элемента в множестве
bool contains(Set *set, const char *element) {
    unsigned long hash_index = hash_function(element, set->hash_capacity);
    if (set->hash_table[hash_index] != NULL && strcmp(set->hash_table[hash_index], element) == 0) {
        return true;
    }
    return false;
}

// Увеличение размера множества
void resize_set(Set *set) {
    set->capacity *= 2;
    set->elements = realloc(set->elements, set->capacity * sizeof(char *));
    set->hash_table = realloc(set->hash_table, set->capacity * sizeof(char *));  // Увеличиваем размер хэш-таблицы
    for (int i = set->hash_capacity; i < set->capacity; i++) {
        set->hash_table[i] = NULL;  // Инициализируем новые элементы NULL
    }
    set->hash_capacity = set->capacity;
}

// Добавление элемента в множество и хэш-таблицу
void set_add(Set *set, const char *element) {
    if (set->size == set->capacity) {
        resize_set(set);
    }

    if (contains(set, element)) {
        return;
    }

    // Добавляем в оригинальный массив
    set->elements[set->size] = strdup(element);
    set->size++;

    // Добавляем элемент в хэш-таблицу
    unsigned long hash_index = hash_function(element, set->hash_capacity);
    set->hash_table[hash_index] = set->elements[set->size - 1];
}

// Поиск элемента в множестве
void set_at(Set *set, const char *element) {
    if (contains(set, element)) {
        printf("Элемент '%s' найден в множестве.\n", element);
    } else {
        printf("Элемент '%s' не найден в множестве.\n", element);
    }
}

// Удаление элемента из множества
void set_del(Set *set, const char *element) {
    unsigned long hash_index = hash_function(element, set->hash_capacity);
    if (set->hash_table[hash_index] != NULL && strcmp(set->hash_table[hash_index], element) == 0) {
        free(set->hash_table[hash_index]);
        set->hash_table[hash_index] = NULL;

        for (int i = 0; i < set->size; i++) {
            if (strcmp(set->elements[i], element) == 0) {
                free(set->elements[i]);
                for (int j = i; j < set->size - 1; j++) {
                    set->elements[j] = set->elements[j + 1];
                }
                set->size--;
                break;
            }
        }
    }
}

// Освобождение памяти
void free_set(Set *set) {
    for (int i = 0; i < set->size; i++) {
        free(set->elements[i]);
    }
    free(set->elements);
    free(set->hash_table);
    free(set);
}
