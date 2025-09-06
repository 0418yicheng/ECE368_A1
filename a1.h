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
void processOutput(TreeNode*);
LinkedList* findHead2(LinkedList*);

TreeNode* createNode(char);
LinkedList* addList(LinkedList*, TreeNode*);
bool contains(LinkedList*, TreeNode*);

bool cycleDetection(LinkedList*);
bool cycleDetectionUtil(TreeNode*, LinkedList*);

void freeTree(TreeNode*);
void freeTreeUtil(TreeNode*);
void freeListUtil(LinkedList*);
void freeVisited(LinkedList*);
void freeCycle(TreeNode*, LinkedList*);
void freeListCycle(LinkedList*, LinkedList*);



#endif