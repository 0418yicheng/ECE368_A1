#ifndef A1_H_
#define A1_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList{
    struct TreeNode* node;
    struct LinkedList* next;
} LinkedList;

typedef struct TreeNode {
    char name;
    struct LinkedList* children;

} TreeNode;

typedef struct Queue{

} Queue;

LinkedList* createTree(FILE*, LinkedList*);
TreeNode* createNode(char);
LinkedList* addList(LinkedList*, TreeNode*);
TreeNode* findHead(LinkedList*);
bool contains(LinkedList*, TreeNode*);
void processOutput(TreeNode*);
void freeTree(TreeNode*);

#endif