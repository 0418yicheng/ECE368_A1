#include "a1.h"

void sortList(LinkedList*);
LinkedList*  mergeLists(LinkedList*, LinkedList*, LinkedList*);
LinkedList*  mergeLists2(LinkedList*, LinkedList*, LinkedList*);
LinkedList* findTail(LinkedList*);
void insertHead(LinkedList*, LinkedList*);
void printList(LinkedList*);
LinkedList* add(LinkedList*, int);
LinkedList* findMin(LinkedList* head);

int main(int argc, char** argv){
    //99 84 27 18 12 57 
    LinkedList* head = add(NULL, 99);

    add(add(add(add(add(head, 84), 27), 18), 12), 57);
    LinkedList* min = findMin(head);

    printf("List Created\n");
    printList(head);
    sortList(head);
    printf("List sorted\n");
    printList(min);

    // LinkedList* head = add(NULL, 99);
    // LinkedList* small = add(head, 20);
    // LinkedList* big = add(add(small, 90), 10);

    // printList(head);

    // insertHead(head, big);

    // printList(small);
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
    LinkedList* small = head->next;
    LinkedList* curr = head->next;
    LinkedList* prev = NULL;

    LinkedList* tail = findTail(head);

    printf("Found tail\n");
    while(curr != NULL){
        if(curr->x > pivot->x){
            //Move the current node to the tail.
            LinkedList* next = curr->next;
            if(prev != NULL){
                prev->next = curr->next;
            }
            
            //Put curr to the tail
            curr->next = tail->next;
            tail->next = curr;
            tail = curr;

            curr = next;
        }
        else{
            if(small->next != NULL) small = small->next;
            prev = curr;
            curr = curr->next;
        }
    }

    printList(head);

    LinkedList* left = head->next;
    // insertHead(head, small);
    LinkedList* right = small->next;
    small->next = NULL; //Unlinks the lists
    head->next = NULL;  

    printList(left);
    printList(right);

    sortList(left);
    sortList(right);

    // mergeLists(left, right, head);
    mergeLists2(left, right, pivot);

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
    LinkedList* next = location->next;
    location->next = head;
    head->next = next;
    //A->B
}

// Merges 2 sorted linked lists together
// THe left and the right lists should already be sorted, so you should just be able to do left->pivot->right
LinkedList* mergeLists(LinkedList* left, LinkedList* right, LinkedList* pivot){
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

LinkedList* mergeLists2(LinkedList* left, LinkedList* right, LinkedList* pivot){
    LinkedList* curr = left;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = pivot;
    pivot->next = right;

    return left;
}

void printList(LinkedList* head){
    if(head == NULL) printf("Empty\n");
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