#ifndef A1_H_
#define A1_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList{
    int x;
    struct TreeNode* node;
    struct LinkedList* next;
} LinkedList;

typedef struct TreeNode {
    char name;
    struct LinkedList* children;

} TreeNode;

LinkedList* createTree(FILE*, LinkedList*);
TreeNode* createNode(char);
LinkedList* addList(LinkedList*, TreeNode*);
TreeNode* findHead(LinkedList*);
bool contains(LinkedList*, TreeNode*);
void processOutput(TreeNode*, char*);
void freeTree(TreeNode*);
void freeTreeUtil(TreeNode*);
void freeListUtil(LinkedList*);
LinkedList* findHead2(LinkedList*);
LinkedList* delete(LinkedList*, LinkedList*);
// void sortList(LinkedList*);

#endif