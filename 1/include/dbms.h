#ifndef DBMS_H
#define DBMS_H

#include "arr.h"
#include "hash_map.h"
#include "queue.h"
#include "single_linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "set.h"
#include "tree.h"

typedef enum {
    _SINGLE_LINKED_LIST,
    _DOUBLE_LINKED_LIST,
    _STACK,
    _ARR,
    _HASH_MAP,
    _QUEUE,
    _TREE,
    _SET
} vtype;

typedef struct {
    vtype v_type;
    union {
        stack *stack;
        LinkedList *list;
        DoublyLinkedList *dlist;
        StringArray *arr;
        Hash_Map *hash_map;
        queue *queue;
        BinaryTree *tree;
        Set *set;
    } data;
} DBMS;

typedef struct {
    char command[10];
    char variable[50];
    char key[50];
    char value[50];
} QueryData;

QueryData parse_query(const char* query);
DBMS *read_from_file(DBMS *dbms, QueryData q_data, const char* filename);
void write_to_file(DBMS *dbms, QueryData q_data, const char* filename);
void comand_handler(DBMS *dbms, QueryData data, const char* filename);

#endif