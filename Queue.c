#include "Queue.h"

Queue* initQueue(){
    Queue* q = malloc(sizeof(Queue));

    q->list = NULL;

    return q;
}

Action pop(Queue* q){
    Action result = q->list->a;

    return result;
}

Action pull(Queue* q){
    Action result = q->list->a;

    QueueList* prev = q->list;
    q->list = q->list->next;

    free(prev);

    return result;
}

QueueList* push(Queue* q, Action a, TreeNode* n){
    if(q->list == NULL){
        q->list = malloc(sizeof(QueueList));

        q->list->a = a;
        q->list->node = n;
        q->list->next = NULL;
        return q->list;
    }

    QueueList* list = q->list;

    while(list->next != NULL){
        list = list->next;
    }

    list->next = malloc(sizeof(QueueList));
    list->next->a = a;
    list->next->node = n;
    list->next->next = NULL;

    return list->next;
}