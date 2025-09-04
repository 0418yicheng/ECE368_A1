#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "a1.h"

typedef struct Queue{
    struct QueueList* list;
} Queue;

typedef enum Action{
    NODE,
    SPACE,
    NEWLINE,
    POUND
 } Action;

typedef struct QueueList{
    Action a;
    TreeNode* node;
    struct QueueList* next;
} QueueList;

Queue* initQueue();
Action pop(Queue*);
Action pull(Queue*);
QueueList* push(Queue*, Action, TreeNode*);
void freeQueue(Queue*);
void freeQueueUtil(QueueList*);

#endif