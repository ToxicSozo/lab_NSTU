#include"../include/single_linked_list.h"

Node *create_node(const char *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = (char*)malloc(strlen(value) + 1);

    strcpy(new_node->data, value);  // Копируем строку в новый узел
    new_node->next = NULL;

    return new_node;
}

// Функция для создания нового списка
LinkedList *create_list() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

// Функция добавления элемента в конец списка
void push_back(LinkedList *list, const char *value) {
    Node *new_node = create_node(value);

    if (list->head == NULL) {
        list->head = new_node;
    } 
    
    else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void push_front(LinkedList *list, const char *value) {
    Node *new_node = create_node(value);
    new_node->next = list->head;
    list->head = new_node;
}

// Функция удаления элемента с начала списка
void pop_front(LinkedList *list) {
    if (list->head == NULL) return;

    Node *tmp = list->head;
    list->head = list->head->next;
    free(tmp->data);
    free(tmp);
}

// Функция удаления элемента с конца списка
void pop_back(LinkedList *list) {
    if (list->head == NULL) return;  // Если список пуст, ничего не делаем

    if (list->head->next == NULL) {  // Если в списке один элемент
        free(list->head->data);
        free(list->head);
        list->head = NULL;
    } 
    
    else {
        Node *current = list->head;
        while (current->next->next != NULL) {
            current = current->next;  // Идем к предпоследнему узлу
        }
        free(current->next->data);
        free(current->next);
        current->next = NULL;  // Предпоследний узел становится последним
    }
}

// Функция поиска элемента по значению
Node* find_value(LinkedList *list, const char *value) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            return current;  // Возвращаем узел, если значение найдено
        }
        current = current->next;
    }
    return NULL;  // Если элемент не найден, возвращаем NULL
}

// Функция удаления элемента по значению
void remove_value(LinkedList *list, const char *value) {
    if (list->head == NULL) return;  // Если список пуст, ничего не делаем

    // Если удаляемый элемент — первый
    if (strcmp(list->head->data, value) == 0) {
        Node *tmp = list->head;
        list->head = list->head->next;
        free(tmp->data);
        free(tmp);
        return;
    }

    Node *current = list->head;
    while (current->next != NULL && strcmp(current->next->data, value) != 0) {
        current = current->next;  // Ищем элемент для удаления
    }

    if (current->next == NULL) {
        printf("Элемент с значением '%s' не найден.\n", value);
        return;
    }

    Node *tmp = current->next;
    current->next = current->next->next;
    free(tmp->data);
    free(tmp);
}

// Функция вывода списка на экран
void print_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Функция освобождения памяти списка
void free_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *tmp = current;
        current = current->next;
        free(tmp->data);
        free(tmp);
    }
    free(list);  // Освобождаем память структуры списка
}