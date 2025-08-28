#include "Queue.h"

// int main(int argc, char** argv){
//     printf("Hello");
//     Queue* q = initQueue();

//     push(q, NODE, NULL);
//     push(q, NEWLINE, NULL);

//     printf("%d", pop(q));
//     printf("%d", pull(q));
//     printf("%d", pull(q));

//     return 1;
// }

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

    q->list = q->list->next;    //Check if this actually does what I want or if it's limited to the function

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