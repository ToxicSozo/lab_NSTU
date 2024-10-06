#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_queue(queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void push_queue(queue* q, const char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(value);  // Копируем строку в узел
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } 
    
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Добавлено: %s\n", value);
}

char* pop_queue(queue* q) {
    if (q->front == NULL) {
        printf("Очередь пуста!\n");
        return NULL;
    }

    // Извлекаем данные из первого узла
    Node* temp = q->front;
    char* item = strdup(temp->data);  // Копируем строку, чтобы вернуть её

    // Перемещаем указатель front на следующий узел
    q->front = q->front->next;

    // Если очередь стала пустой после удаления
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Освобождаем память для удаленного узла и строки
    free(temp->data);
    free(temp);

    printf("Удалено: %s\n", item);
    return item;
}

int isEmpty(queue* q) {
    return (q->front == NULL);
}
