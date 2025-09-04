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
    bool hasParent;
    struct LinkedList* children;

} TreeNode;

LinkedList* createTree(FILE*, LinkedList*);
TreeNode* createNode(char);
LinkedList* addList(LinkedList*, TreeNode*);
TreeNode* findHead(LinkedList*);
bool contains(LinkedList*, TreeNode*);
void processOutput(FILE*, TreeNode*);
void freeTree(TreeNode*);
void freeTreeUtil(TreeNode*);
void freeListUtil(LinkedList*);
LinkedList* findHead2(LinkedList*);
LinkedList* delete(LinkedList*, LinkedList*);
bool cycleDetection(LinkedList*);
bool cycleDetectionUtil(TreeNode*, LinkedList*);
void freeVisited(LinkedList*);

#endif