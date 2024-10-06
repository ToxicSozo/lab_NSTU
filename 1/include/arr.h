#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringArray {
  char **data;
  size_t capacity;
  size_t size;
} StringArray;

StringArray* create_string_array(size_t capacity);
void resizeStringArray(struct StringArray* arr);
void append_string(struct StringArray* arr, const char* str);
void insertStringAt(struct StringArray* arr, int index, const char* str);
void deleteStringAt(struct StringArray* arr, int index);
char* getStringAt(struct StringArray* arr, int index);
void replaceStringAt(struct StringArray* arr, int index, const char* str);
int getStringArraySize(struct StringArray* arr);
void printStringArray(struct StringArray* arr);
void freeStringArray(struct StringArray* arr);

#endif