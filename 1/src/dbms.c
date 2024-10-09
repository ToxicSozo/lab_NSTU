#include "../include/single_linked_list.h"
#include "../include/dbms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

QueryData parse_query(const char* query) {
    QueryData data;
    memset(&data, 0, sizeof(data));

    if (sscanf(query, "%s %s %s %s", data.command, data.variable, data.key, data.value) == 4) {
        return data;
    }
    
    else if (sscanf(query, "%s %s %s", data.command, data.variable, data.value) == 3) {
        return data;
    }

    else if (sscanf(query, "%s %s", data.command, data.variable) == 2) {
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

    // Читаем файл построчно
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // Удаляем символ новой строки

        // Если строка имеет вид "переменная = значение"
        if (sscanf(line, "%s = %[^\n]", name, value) == 2) {
            if (strcmp(name, q_data.variable) == 0) {
                // Выбираем структуру данных в зависимости от dbms->v_type
                switch (dbms->v_type) {
                    case _STACK: {
                        // Работа со стеком
                        char *stack_token = strtok(value, " ");
                        while (stack_token != NULL) {
                            dbms->data.stack = push(dbms->data.stack, stack_token);
                            stack_token = strtok(NULL, " ");
                        }
                        break;
                    }
                    case _SINGLE_LINKED_LIST: {
                        // Работа с односвязным списком
                        char *list_token = strtok(value, " ");
                        while (list_token != NULL) {
                            push_back(dbms->data.list, list_token);
                            list_token = strtok(NULL, " ");
                        }
                        break;
                    }
                    case _ARR: {
                        // Работа с массивом
                        char *arr_token = strtok(value, " ");
                        while (arr_token != NULL) {
                            append_string(dbms->data.arr, arr_token);
                            arr_token = strtok(NULL, " ");
                        }
                        break;
                    }
                    case _HASH_MAP: {
                        // Работа с хэш-таблицей (поддержка строковых ключей)
                        char *hash_map_token = strtok(value, " ");
                        while (hash_map_token != NULL) {
                            char key[50], val[50];
                            if (sscanf(hash_map_token, "%49[^:]:%49s", key, val) == 2) {
                                dbms->data.hash_map = hash_map_insert(dbms->data.hash_map, key, val);
                            }
                            hash_map_token = strtok(NULL, " ");
                        }
                        break;
                    }
                    case _QUEUE: {
                        // Работа с очередью
                        char *queue_token = strtok(value, " ");
                        while (queue_token != NULL) {
                            push_queue(dbms->data.queue, queue_token);
                            queue_token = strtok(NULL, " ");
                        }
                        break;
                    }
                    case _DOUBLE_LINKED_LIST: {
                        char *dlist_token = strtok(value, " ");
                        while (dlist_token != NULL) {
                            addToDoublyLinkedListTail(dbms->data.dlist, dlist_token);
                            dlist_token = strtok(NULL, " ");
                        }
                        break;
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
                switch(dbms->v_type) {
                    case _STACK:
                        if (dbms->data.stack != NULL) {
                            fprintf(temp_file, "%s =", name);
                            stack* current = dbms->data.stack;
                            while (current != NULL) {
                                fprintf(temp_file, " %s", current->data);
                                current = current->next;
                            }
                            fprintf(temp_file, "\n");
                        }
                        break;
                    case _SINGLE_LINKED_LIST:
                        if (dbms->data.list != NULL && dbms->data.list->head != NULL) {
                            fprintf(temp_file, "%s =", name);
                            Node* current = dbms->data.list->head;
                            while (current != NULL) {
                                fprintf(temp_file, " %s", current->data);
                                current = current->next;
                            }
                            fprintf(temp_file, "\n");
                        }
                        break;
                    case _ARR:
                        if (dbms->data.arr != NULL && dbms->data.arr->size > 0) {
                            fprintf(temp_file, "%s =", name);
                            for (int i = 0; i < dbms->data.arr->size; i++) {
                                fprintf(temp_file, " %s", dbms->data.arr->data[i]);
                            }
                            fprintf(temp_file, "\n");
                        }
                        break;
                    case _HASH_MAP:
                        if (dbms->data.hash_map != NULL) {
                            int has_elements = 0;
                            for (size_t i = 0; i < dbms->data.hash_map->size; i++) {
                                if (dbms->data.hash_map->entries[i].key != NULL) {
                                    has_elements = 1;
                                    break;
                                }
                            }
                            if (has_elements) {
                                fprintf(temp_file, "%s =", name);
                                for (size_t i = 0; i < dbms->data.hash_map->size; i++) {
                                    if (dbms->data.hash_map->entries[i].key != NULL) {
                                        fprintf(temp_file, " %s:%s", dbms->data.hash_map->entries[i].key, dbms->data.hash_map->entries[i].value);
                                    }
                                }
                                fprintf(temp_file, "\n");
                            }
                        }
                        break;
                    case _QUEUE:
                        if (dbms->data.queue != NULL && dbms->data.queue->front != NULL) {
                            fprintf(temp_file, "%s =", name);
                            Node* current = dbms->data.queue->front;
                            while (current != NULL) {
                                fprintf(temp_file, " %s", current->data);
                                current = current->next;
                            }
                            fprintf(temp_file, "\n");
                        }
                        break;
                    case _DOUBLE_LINKED_LIST:
                        if (dbms->data.dlist != NULL && dbms->data.dlist->head != NULL) {
                            fprintf(temp_file, "%s =", name);
                            Node* current = dbms->data.dlist->head;
                            while (current != NULL) {
                                fprintf(temp_file, " %s", current->data);
                                current = current->next;
                            }
                            fprintf(temp_file, "\n");
                        }
                        break;
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

    if (!found) {
        switch(dbms->v_type) {
            case _STACK:
                if (dbms->data.stack != NULL) {
                    fprintf(temp_file, "%s =", q_data.variable);
                    stack* current = dbms->data.stack;
                    while (current != NULL) {
                        fprintf(temp_file, " %s", current->data);
                        current = current->next;
                    }
                    fprintf(temp_file, "\n");
                }
                break;
            case _SINGLE_LINKED_LIST:
                if (dbms->data.list != NULL && dbms->data.list->head != NULL) {
                    fprintf(temp_file, "%s =", q_data.variable);
                    Node* current = dbms->data.list->head;
                    while (current != NULL) {
                        fprintf(temp_file, " %s", current->data);
                        current = current->next;
                    }
                    fprintf(temp_file, "\n");
                }
                break;
            case _ARR:
                if (dbms->data.arr != NULL && dbms->data.arr->size > 0) {
                    fprintf(temp_file, "%s =", q_data.variable);
                    for (int i = 0; i < dbms->data.arr->size; i++) {
                        fprintf(temp_file, " %s", dbms->data.arr->data[i]);
                    }
                    fprintf(temp_file, "\n");
                }
                break;
            case _HASH_MAP:
                if (dbms->data.hash_map != NULL) {
                    int has_elements = 0;
                    for (size_t i = 0; i < dbms->data.hash_map->size; i++) {
                        if (dbms->data.hash_map->entries[i].key != NULL) {
                            has_elements = 1;
                            break;
                        }
                    }
                    if (has_elements) {
                        fprintf(temp_file, "%s =", q_data.variable);
                        for (size_t i = 0; i < dbms->data.hash_map->size; i++) {
                            if (dbms->data.hash_map->entries[i].key != NULL) {
                                fprintf(temp_file, " %s:%s", dbms->data.hash_map->entries[i].key, dbms->data.hash_map->entries[i].value);
                            }
                        }
                        fprintf(temp_file, "\n");
                    }
                }
                break;
            case _QUEUE:
                if (dbms->data.queue != NULL && dbms->data.queue->front != NULL) {
                    fprintf(temp_file, "%s =", q_data.variable);
                    Node* current = dbms->data.queue->front;
                    while (current != NULL) {
                        fprintf(temp_file, " %s", current->data);
                        current = current->next;
                    }
                    fprintf(temp_file, "\n");
                }
                break;
            case _DOUBLE_LINKED_LIST:
                if (dbms->data.dlist != NULL && dbms->data.dlist->head != NULL) {
                    fprintf(temp_file, "%s =", q_data.variable);
                    Node *current = dbms->data.dlist->head;
                    while (current != NULL) {
                        fprintf(temp_file, " %s", current->data);
                        current = current->next;
                    }
                    fprintf(temp_file, "\n");
                }
                break;
        }
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
            dbms->v_type = _STACK;
            dbms->data.stack = NULL;
            dbms = read_from_file(dbms, data, filename);

            if (strcmp(data.command, "SPUSH") == 0) {
                dbms->data.stack = push(dbms->data.stack, data.value);
                show(dbms->data.stack);
                dbms->data.stack = reverse_stack(dbms->data.stack);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "SPOP") == 0) {
                dbms->data.stack = pop(dbms->data.stack);
                show(dbms->data.stack);
                dbms->data.stack = reverse_stack(dbms->data.stack);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "SSHOW") == 0) {
                show(dbms->data.stack);
            }
            break;

        case 'L':
            dbms->v_type = _SINGLE_LINKED_LIST;
            dbms->data.list = create_list();
            dbms = read_from_file(dbms, data, filename);

            if (strcmp(data.command, "LPUSH_B") == 0) {
                push_back(dbms->data.list, data.value);
                print_list(dbms->data.list);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "LPUSH_F") == 0) {
                push_front(dbms->data.list, data.value);
                print_list(dbms->data.list);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "LDEL_B") == 0) {
                pop_back(dbms->data.list);
                print_list(dbms->data.list);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "LDEL_F") == 0) {
                pop_front(dbms->data.list);
                print_list(dbms->data.list);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "LDEL_V") == 0) {
                remove_value(dbms->data.list, data.value);
                print_list(dbms->data.list);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "LSEARCH") == 0) {
                Node* result = find_value(dbms->data.list, data.value);
                if (result != NULL) {
                    printf("Value found: %s\n", result->data);
                }
                else {
                    printf("Value not found\n");
                }
            }
            break;
        case 'M':
            dbms->v_type = _ARR;
            dbms->data.arr = create_string_array(10);
            dbms = read_from_file(dbms, data, filename);

            if (strcmp(data.command, "MPUSH") == 0) {
                append_string(dbms->data.arr, data.value);
                printStringArray(dbms->data.arr);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "MINSERT") == 0) {
                int index = atoi(data.key);
                insertStringAt(dbms->data.arr, index, data.value);
                printStringArray(dbms->data.arr);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "MREPLACE") == 0) {
                int index = atoi(data.key);
                replaceStringAt(dbms->data.arr, index, data.value);
                printStringArray(dbms->data.arr);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "MGET") == 0) {
                int index = atoi(data.value);
                char* value = getStringAt(dbms->data.arr, index);
                if (value != NULL) {
                    printf("Value at index %d: %s\n", index, value);
                }
            }

            else if (strcmp(data.command, "MDEL_I") == 0) {
                int index = atoi(data.key);
                deleteStringAt(dbms->data.arr, index);
                printStringArray(dbms->data.arr);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "MSIZE") == 0) {
                int size = getStringArraySize(dbms->data.arr);
                printf("Array size: %d\n", size);
            }

            else if (strcmp(data.command, "MREAD") == 0) {
                printStringArray(dbms->data.arr);
            }
            break;

        case 'H':
            dbms->v_type = _HASH_MAP;
            dbms->data.hash_map = hash_map_create(10);
            dbms = read_from_file(dbms, data, filename);

            if (strcmp(data.command, "HSET") == 0) {
                dbms->data.hash_map = hash_map_insert(dbms->data.hash_map, data.key, data.value);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "HGET") == 0) {
                char *value = hash_map_at(dbms->data.hash_map, data.key);
                if (value != NULL) {
                    printf("Value at key '%s': %s\n", data.key, value);
                } 
                
                else {
                    printf("Key '%s' not found in hash map.\n", data.key);
                }
            }

            else if (strcmp(data.command, "HDEL") == 0) {
                hash_map_remove(dbms->data.hash_map, data.key);
                write_to_file(dbms, data, filename);
            }
            break;
            
        case 'Q':
            dbms->v_type = _QUEUE;
            dbms->data.queue = (queue*)malloc(sizeof(queue));
            init_queue(dbms->data.queue);
            dbms = read_from_file(dbms, data, filename);

            if (strcmp(data.command, "QPUSH") == 0) {
                push_queue(dbms->data.queue, data.value);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "QPOP") == 0) {
                pop_queue(dbms->data.queue);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "QSHOW") == 0) {
                Node* current = dbms->data.queue->front;
                while (current != NULL) {
                    printf("%s ", current->data);
                    current = current->next;
                }
                printf("\n");
            }
            break;

        case 'D':
            dbms->v_type = _DOUBLE_LINKED_LIST;
            dbms->data.dlist =(DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
            initDoublyLinkedList(dbms->data.dlist);
            dbms = read_from_file(dbms, data, filename);
            
            if (strcmp(data.command, "DPUSH_B") == 0) {
                addToDoublyLinkedListTail(dbms->data.dlist, data.value);
                printDoublyLinkedList(dbms->data.dlist);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "DPUSH_F") == 0) {
                addToDoublyLinkedListHead(dbms->data.dlist, data.value);
                printDoublyLinkedList(dbms->data.dlist);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "DDEL_B") == 0) {
                removeFromDoublyLinkedListTail(dbms->data.dlist);
                printDoublyLinkedList(dbms->data.dlist);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "DDEL_F") == 0) {
                removeFromDoublyLinkedListHead(dbms->data.dlist);
                printDoublyLinkedList(dbms->data.dlist);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "DDEL_V") == 0) {
                removeDoublyLinkedListNodeByValue(dbms->data.dlist, data.value);
                printDoublyLinkedList(dbms->data.dlist);
                write_to_file(dbms, data, filename);
            }

            else if (strcmp(data.command, "DSEARCH") == 0) {
                Node *result = findDoublyLinkedListNodeByValue(dbms->data.dlist, data.value);
                if (result != NULL) {
                    printf("Value found: %s\n", result->data);
                }
                else {
                    printf("Value not found\n");
                }
            }

            else if (strcmp(data.command, "DSHOW") == 0) {
                printDoublyLinkedList(dbms->data.dlist);
            }
            break;
    }
}