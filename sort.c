#include "sort.h"


// int main(int argc, char** argv){
//     //99 84 27 18 12 57 
//     LinkedList* head = add(NULL, 3);

//     add(add(add(add(add(add(head, 36), 39), 84), 15), 94), 25);
//     LinkedList* min = findMin(head);

//     printf("List Created\n");
//     printList(head);
//     sortList(head);
//     printf("List sorted\n");
//     printList(min);
// }

// Sorts a linkedlist using mergesort
void sortList(LinkedList* head){
    if(head == NULL || head->next == NULL){
        return;
    }

    LinkedList* pivot = head;
    LinkedList* small = head;
    LinkedList* curr = head->next;
    LinkedList* prev = head;

    while(curr != NULL){
        if(curr->node->name < pivot->node->name){
            //Insert curr after small, and continue iterating
            curr = insert(curr, prev, small);
            small = small->next;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    LinkedList* left, *right;
    if(head != small){
        left = head->next;
        right = small->next;

        //Unlink the lists
        small->next = NULL; 
        head->next = NULL;  
    }
    else{
        //Case where pivot is already in the correct position
        left = NULL;
        right = head->next;
    }

    // Keep track of where the new head of the linkedlist will be
    LinkedList* minLeft = findMin(left);
    LinkedList* minRight = findMin(right);

    sortList(left);
    sortList(right);

    mergeLists(minLeft, minRight, pivot);
}

LinkedList* findTail(LinkedList* list){
    while(list->next != NULL){
        list = list->next;
    }

    return list;
}

void insertHead(LinkedList* head, LinkedList* location){
    if(head == location) return;
    LinkedList* next = location->next;
    location->next = head;
    head->next = next;
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

// Assumes the lists are already sorted, where left contains values less than pivot, and right contains values greater than pivot
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
        printf("%c ", head->node->name);
        head = head->next;
    }

    printf("\n");
}

LinkedList* findMin(LinkedList* head){
    LinkedList* min = head;
    while(head != NULL){
        min = head->node->name < min->node->name ? head : min;
        head = head->next;
    }

    return min;
}