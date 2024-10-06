#ifndef QUEUE_H
#define QUEUE_H

#include "../include/node.h"

typedef struct queue {
    Node *front;
    Node *rear;
} queue;

void init_queue(queue *q);
void push_queue(queue *q, const char *value);
char *pop_queue(queue *q);
int isEmpty(queue* q);

#endif