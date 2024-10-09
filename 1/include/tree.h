#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Определение типа для узла бинарного дерева
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Определение типа для дерева
typedef struct {
    TreeNode* root;
} BinaryTree;

// Функция для создания нового узла
TreeNode* newNode(int data);

// Функция для добавления элемента в полное бинарное дерево
TreeNode* insert(TreeNode* root, int data);

// Функция для поиска элемента в дереве
bool search(TreeNode* root, int data);

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFullBinaryTree(TreeNode* root);

// Функция для вывода дерева (обход в прямом порядке)
void printTree(TreeNode* root, FILE* file);

// Функция для создания нового дерева
BinaryTree* createBinaryTree();

// Функция для добавления элемента в дерево
void insertElement(BinaryTree* tree, int data);

// Функция для поиска элемента в дереве
bool searchElement(BinaryTree* tree, int data);

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFull(BinaryTree* tree);

// Функция для вывода дерева
void print(BinaryTree* tree, FILE* file);

#endif