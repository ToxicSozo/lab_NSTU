#ifndef LIST_H
#define LIST_H

#include "../include/node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Node *head;
} LinkedList;

Node *create_node(const char *value);
LinkedList *create_list();
void push_back(LinkedList *list, const char *value);
void push_front(LinkedList *list, const char *value);
void pop_front(LinkedList *list);
void pop_back(LinkedList *list);
Node* find_value(LinkedList *list, const char *value);
void remove_value(LinkedList *list, const char *value);
void print_list(LinkedList *list);
void free_list(LinkedList *list);

#endif