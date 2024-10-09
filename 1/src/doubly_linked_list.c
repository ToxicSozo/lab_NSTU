#include "../include/doubly_linked_list.h"

// Функция для создания нового узла
Node* createDoublyLinkedListNode(const char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Функция для инициализации двусвязного списка
void initDoublyLinkedList(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// Функция для добавления элемента в голову двусвязного списка
void addToDoublyLinkedListHead(DoublyLinkedList *list, const char *data) {
    Node *newNode = createDoublyLinkedListNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

// Функция для добавления элемента в хвост двусвязного списка
void addToDoublyLinkedListTail(DoublyLinkedList *list, const char *data) {
    Node *newNode = createDoublyLinkedListNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

// Функция для удаления элемента с головы двусвязного списка
void removeFromDoublyLinkedListHead(DoublyLinkedList *list) {
    if (list->head == NULL) {
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(temp->data);
    free(temp);
}

// Функция для удаления элемента с хвоста двусвязного списка
void removeFromDoublyLinkedListTail(DoublyLinkedList *list) {
    if (list->tail == NULL) {
        return;
    }
    Node *temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(temp->data);
    free(temp);
}

// Функция для удаления элемента по значению из двусвязного списка
void removeDoublyLinkedListNodeByValue(DoublyLinkedList *list, const char *data) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                list->head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev;
            }
            free(current->data);
            free(current);
            return;
        }
        current = current->next;
    }
}

// Функция для поиска элемента по значению в двусвязном списке
Node* findDoublyLinkedListNodeByValue(DoublyLinkedList *list, const char *data) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Функция для вывода двусвязного списка
void printDoublyLinkedList(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Функция для освобождения памяти, выделенной под двусвязный список
void freeDoublyLinkedList(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}