#include "../include/node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Node *head;
    Node *tail;
} DoublyLinkedList;

Node* createDoublyLinkedListNode(const char *data);
void initDoublyLinkedList(DoublyLinkedList *list);
void addToDoublyLinkedListHead(DoublyLinkedList *list, const char *data);
void addToDoublyLinkedListTail(DoublyLinkedList *list, const char *data);
void removeFromDoublyLinkedListHead(DoublyLinkedList *list);
void removeFromDoublyLinkedListTail(DoublyLinkedList *list);
void removeDoublyLinkedListNodeByValue(DoublyLinkedList *list, const char *data);
Node* findDoublyLinkedListNodeByValue(DoublyLinkedList *list, const char *data);
void printDoublyLinkedList(DoublyLinkedList *list);
void freeDoublyLinkedList(DoublyLinkedList *list);