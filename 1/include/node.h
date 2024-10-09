#ifndef NODE_H
#define NODE_H

typedef struct _Node {
    char *data;
    struct _Node *next;
    struct _Node *prev;
} Node;

#endif