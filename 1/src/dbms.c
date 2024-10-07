#include "../include/dbms.h"

QueryData parse_query(const char* query) {
    QueryData data;
    memset(&data, 0, sizeof(data));

    if (sscanf(query, "%s %s %s %s", data.command, data.variable, data.key, data.value) == 4) {
        return data;
    }
    
    else if (sscanf(query, "%s %s %s", data.command, data.variable, data.value) == 3) {
        return data;
    }
    
    else {
        fprintf(stderr, "Invalid query format\n");
        data.command[0] = '\0';
        return data;
    }
}

DBMS *read_from_file(DBMS *dbms, QueryData q_data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    char line[256];
    char name[256];
    char value[256];

    switch (dbms->v_type)
    {
    case _STACK:
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;

            if(sscanf(line, "%s = %[^\n]", name, value) == 2) {
                if(strcmp(name, q_data.variable) == 0) {
                    char *token = strtok(value, " ");
                    
                    while(token != NULL) {
                        dbms->data.stack = push(dbms->data.stack, token);
                        token = strtok(NULL, " ");
                    }
                }
            }
        }
    }

    fclose(file);
    return dbms;
}

void write_to_file(DBMS *dbms, QueryData q_data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        perror("Failed to open temp file for writing");
        fclose(file);
        return;
    }

    char line[256];
    char name[256];
    char value[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%s = %[^\n]", name, value) == 2) {
            if (strcmp(name, q_data.variable) == 0) {
                if (dbms->data.stack != NULL) {
                    fprintf(temp_file, "%s =", name);
                    stack* current = dbms->data.stack;
                    while (current != NULL) {
                        fprintf(temp_file, " %s", current->data);
                        current = current->next;
                    }
                    fprintf(temp_file, "\n");
                }
                found = 1;
            } 
            else {
                fprintf(temp_file, "%s\n", line);
            }
        } 
        
        else {
            fprintf(temp_file, "%s\n", line);
        }
    }

    if (!found && dbms->data.stack != NULL) {
        fprintf(temp_file, "%s =", q_data.variable);
        stack* current = dbms->data.stack;
        while (current != NULL) {
            fprintf(temp_file, " %s", current->data);
            current = current->next;
        }
        fprintf(temp_file, "\n");
    }

    fclose(file);
    fclose(temp_file);

    // Заменяем оригинальный файл временным файлом
    if (remove(filename) != 0) {
        perror("Failed to remove original file");
        return;
    }
    if (rename("temp.txt", filename) != 0) {
        perror("Failed to rename temp file");
        return;
    }
}

void comand_handler(DBMS *dbms, QueryData data, const char* filename) {
    switch (data.command[0]) {
        case 'S':
            if (strcmp(data.command, "SPUSH") == 0) {
                dbms->v_type = _STACK;
                dbms->data.stack = NULL;
                dbms = read_from_file(dbms, data, filename);
                dbms->data.stack = push(dbms->data.stack, data.value);
                dbms->data.stack = reverse_stack(dbms->data.stack);
                write_to_file(dbms, data, filename);
            }
            else {
                fprintf(stderr, "Unsupported command\n");
            }

            break;
        case 'L':
            break;
    }
}