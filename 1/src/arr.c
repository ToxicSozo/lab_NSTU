
#include "../include/arr.h"

struct StringArray* create_string_array(size_t capacity) {
    StringArray* arr = (StringArray*)malloc(sizeof(StringArray));
    arr->data = (char**)malloc(capacity * sizeof(char*));
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

void resizeStringArray(struct StringArray* arr) {
    arr->capacity *= 2;
    arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));
}

void append_string(struct StringArray* arr, const char* str) {
    if (arr->size == arr->capacity) {
        resizeStringArray(arr);
    }
    arr->data[arr->size++] = strdup(str); // Копируем строку для хранения в массиве
    printf("Added '%s' to array\n", str);
}

void insertStringAt(struct StringArray* arr, int index, const char* str) {
    if (index < 0 || index > arr->size) {
        printf("Invalid index\n");
        return;
    }
    if (arr->size == arr->capacity) {
        resizeStringArray(arr);
    }
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = strdup(str); // Копируем строку для вставки
    arr->size++;
    printf("Inserted '%s' at index %d\n", str, index);
}

void deleteStringAt(struct StringArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index\n");
        return;
    }
    free(arr->data[index]); // Освобождаем память для удаляемой строки
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    printf("Deleted string at index %d\n", index);
}

char* getStringAt(struct StringArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index\n");
        return NULL;
    }
    return arr->data[index];
}

void replaceStringAt(struct StringArray* arr, int index, const char* str) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index\n");
        return;
    }
    free(arr->data[index]);
    arr->data[index] = strdup(str);
    printf("Replaced string at index %d with '%s'\n", index, str);
}

int getStringArraySize(struct StringArray* arr) {
    return arr->size;
}

void printStringArray(struct StringArray* arr) {
    if (arr->size == 0) {
        printf("Array is empty\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < arr->size; i++) {
        printf("'%s' ", arr->data[i]);
    }
    printf("\n");
}

void freeStringArray(struct StringArray* arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    free(arr);
}