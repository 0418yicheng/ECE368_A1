#include "a1.h"

void sortList(LinkedList*);
LinkedList*  mergeLists(LinkedList*, LinkedList*, LinkedList*);
LinkedList* findTail(LinkedList*);
void insertHead(LinkedList*, LinkedList*);
LinkedList* insert(LinkedList*, LinkedList*, LinkedList*);
void printList(LinkedList*);
LinkedList* add(LinkedList*, int);
LinkedList* findMin(LinkedList* head);

int main(int argc, char** argv){
    //99 84 27 18 12 57 
    LinkedList* head = add(NULL, 1);

    add(add(add(add(add(head, 2), 4), 3), 8), 7);
    LinkedList* min = findMin(head);

    printf("List Created\n");
    printList(head);
    sortList(head);
    printf("List sorted\n");
    printList(min);
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

//TODO: Remove the pivot from the two lists, and adjust the merge function
void sortList(LinkedList* head){
    if(head == NULL || head->next == NULL){
        return;
    }

    LinkedList* pivot = head;
    LinkedList* small = head;
    LinkedList* curr = head->next;
    LinkedList* prev = head;

    LinkedList* tail = findTail(head);

    while(curr != NULL){
        printf("Curr %d\n", curr->x);
        if(curr->x > pivot->x){
            //Move the current node after small (Moving to tail acreates an infinite loop)
            // LinkedList* next = curr->next;
            // if(prev != NULL){
            //     prev->next = curr->next;
            // }
            
            //Put curr to the tail

            curr = insert(curr, prev, small);
        }
        else{
            if(small->next != NULL) small = small->next;
            prev = curr;
            curr = curr->next;
        }
    }

    printList(head);

    LinkedList* left, *right;

    if(head != small){
        left = head->next;
        // insertHead(head, small);
        right = small->next;
        small->next = NULL; //Unlinks the lists
        head->next = NULL;  
    }
    else{
        //Case where pivot is already in the correct position
        left = NULL;
        right = head->next;
    }
    
    printList(left);
    printList(right);
    printf("\n");

    LinkedList* minLeft = findMin(left);
    LinkedList* minRight = findMin(right);

    sortList(left);
    sortList(right);

    printf("Sorted Lists\n");
    printList(minLeft);
    printList(minRight);
    mergeLists(minLeft, minRight, pivot);
    printf("merged\n");

    printList(left);
    
}

LinkedList* findTail(LinkedList* list){
    while(list->next != NULL){
        list = list->next;
    }

    // if(i != size-1) printf("Fuck\n");

    return list;
}

void insertHead(LinkedList* head, LinkedList* location){
    if(head == location) return;
    LinkedList* next = location->next;
    location->next = head;
    head->next = next;
    //A->B
}

// Prev is the node before curr, and we want to insert curr after location
LinkedList* insert(LinkedList* curr, LinkedList* prev, LinkedList* location){
    if(prev == location){
        return curr->next;
    }

    LinkedList* next = curr->next;
    curr->next = location->next;

    location->next = curr;
    prev->next = next;

    return next;
}

LinkedList* mergeLists(LinkedList* left, LinkedList* right, LinkedList* pivot){
    if(left == NULL){
        pivot->next = right;
        return pivot;
    }
    LinkedList* leftTail = findTail(left);
    leftTail->next = pivot;
    pivot->next = right;

    return left;
}

void printList(LinkedList* head){
    if(head == NULL) printf("Empty");
    while(head != NULL){
        printf("%d ", head->x);
        head = head->next;
    }

    printf("\n");
}

LinkedList* findMin(LinkedList* head){
    LinkedList* min = head;
    while(head != NULL){
        min = head->x < min->x ? head : min;
        head = head->next;
    }

    return min;
}