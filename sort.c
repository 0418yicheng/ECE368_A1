#include "a1.h"

void sortList(LinkedList*, int);
LinkedList*  mergeLists(LinkedList*, LinkedList*);
LinkedList* findTail(LinkedList*, int);
void insertHead(LinkedList*, LinkedList*);
void printList(LinkedList*);
LinkedList* add(LinkedList*, int);

int main(int argc, char** argv){
    //99 84 27 18 12 57 
    LinkedList* head = add(NULL, 99);

    add(add(add(add(add(head, 84), 27), 18), 12), 57);

    printf("List Created\n");
    printList(head);
    sortList(head, 6);
    printf("List sorted\n");
    printList(head);

    // LinkedList* left = add(NULL, 1);
    // add(add(left, 4), 5);
    // printList(left);

    // LinkedList* right = add(NULL, 2);
    // add(add(right, 3), 6);
    // printList(right);

    // printf("Lists created\n");

    // if(mergeLists(left, right) == NULL) printf("Fuck\n");
    // printList(left);
}

LinkedList* add(LinkedList* list, int x){
    if(list == NULL){
        list = malloc(sizeof(LinkedList));
        list->x = x;
        list->next = NULL;
        return list;
    }
    LinkedList* next = malloc(sizeof(LinkedList));
    next->x = x;
    next->next = NULL;

    list->next = next;
    return next;
}

//TODO: Need to finish
void sortList(LinkedList* head, int size){  //TODO: Try not to use size, and instead just create completely different lists. Unlink them.
    if(size <= 1){
        return;
    }

    LinkedList* pivot = head;
    LinkedList* small = head->next;
    LinkedList* curr = head->next;
    LinkedList* prev = NULL;

    LinkedList* tail = findTail(head, size);

    int lSize = 0;
    int i = 0;
    while(curr != NULL && i < size){    //TODO: Account for the size;
        if(curr->x > pivot->x){
            //Move the current node to the tail.
            LinkedList* next = curr->next;
            if(prev != NULL){
                prev->next = curr->next;
                prev = curr;
            }
            
            //Put curr to the tail
            curr->next = tail->next;
            tail->next = curr;
            tail = curr;

            curr = next;
        }
        else{
            small = small->next;
            lSize ++;
        }

        i++;
    }

    LinkedList* left = head->next;
    insertHead(head, small);
    LinkedList* right = head->next;
    sortList(left, lSize);
    sortList(right, size - lSize - 1);

    mergeLists(left, right);
}

LinkedList* findTail(LinkedList* list, int size){
    int i = 0;
    while(list->next != NULL  && i < size){
        list = list->next;
    }

    if(i != size-1) printf("Fuck\n");

    return list;
}

void insertHead(LinkedList* head, LinkedList* location){

}

// Merges 2 sorted linked lists together
LinkedList* mergeLists(LinkedList* left, LinkedList* right){
    LinkedList* head;
    LinkedList* origHead;
    if(left != NULL && (right == NULL || left->x < right->x)){
        head = left;
        left = left->next;
    }
    else if(right != NULL){
        head = right;
        right = right->next;
    }
    else return NULL;
    origHead = head;
    printf("Head established\n");

    while(left != NULL || right != NULL){
        if(left != NULL && (right == NULL || left->x < right->x)){
            head->next = left;
            head = head->next;
            left = left->next;
        }
        else if(right != NULL){
            head->next = right;
            head = head->next;
            right = right->next;
        }
        else return NULL;
    }

    return origHead;
}

void printList(LinkedList* head){
    while(head != NULL){
        printf("%d ", head->x);
        head = head->next;
    }

    printf("\n");
}