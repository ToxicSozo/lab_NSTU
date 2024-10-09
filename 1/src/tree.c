#include "../include/tree.h"

// Функция для создания нового узла
TreeNode* newNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для добавления элемента в полное бинарное дерево
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (root->left == NULL) {
        root->left = insert(root->left, data);
    } else if (root->right == NULL) {
        root->right = insert(root->right, data);
    } else {
        // Если у корня есть оба потомка, добавляем в левое поддерево
        root->left = insert(root->left, data);
    }
    return root;
}

// Функция для поиска элемента в дереве
bool search(TreeNode* root, int data) {
    if (root == NULL)
        return false;

    if (root->data == data)
        return true;

    return search(root->left, data) || search(root->right, data);
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFullBinaryTree(TreeNode* root) {
    if (root == NULL)
        return true;

    // Проверка, что узел либо лист, либо имеет два потомка
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        return false;

    return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
}

// Функция для вывода дерева (обход в прямом порядке)
void printTree(TreeNode* root, FILE* file) {
    if (root == NULL)
        return;

    fprintf(file, "%d ", root->data);
    printTree(root->left, file);
    printTree(root->right, file);
}

// Функция для создания нового дерева
BinaryTree* createBinaryTree() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

// Функция для добавления элемента в дерево
void insertElement(BinaryTree* tree, int data) {
    tree->root = insert(tree->root, data);
}

// Функция для поиска элемента в дереве
bool searchElement(BinaryTree* tree, int data) {
    return search(tree->root, data);
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFull(BinaryTree* tree) {
    return isFullBinaryTree(tree->root);
}

// Функция для вывода дерева
void print(BinaryTree* tree, FILE* file) {
    printTree(tree->root, file);
    fprintf(file, "\n");
}