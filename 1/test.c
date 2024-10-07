#include "../include/stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Функция для считывания данных из файла по имени переменной и записи их в стек
stack* read_from_file(const char* filename, const char* variable_name) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    stack* top = NULL;  // Инициализация пустого стека
    char line[256];
    char name[256];
    char value[256];

    while (fgets(line, sizeof(line), file)) {
        // Удаляем символ новой строки, если он есть
        line[strcspn(line, "\n")] = 0;

        // Разделяем строку на имя переменной и значение
        if (sscanf(line, "%s = %s", name, value) == 2) {
            // Сравниваем имя переменной с заданным именем
            if (strcmp(name, variable_name) == 0) {
                // Добавляем значение в стек
                top = push(top, value);
            }
        }
    }

    fclose(file);
    return top;
}

int main() {
    stack* top = read_from_file("data.txt", "variable1");

    if (top != NULL) {
        printf("Stack contents:\n");
        show(top);
        free_stack(top);
    } else {
        printf("Failed to read data from file.\n");
    }

    return 0;
}