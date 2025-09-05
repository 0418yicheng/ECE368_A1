#include "a1.h"
#include "Queue.c"
#include "sort.c"

//TODO: valgrind to check memory leaks.
int main(int argc, char** argv){
    if(argc < 2){
        printf("Not enough arguments\n");
        return 0;
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL){
        printf("Error opening file\n");
        return 0;
    }

    //TODO: valgrind on test6 to check if this part works.
    LinkedList* nodes = NULL;
    nodes = createTree(file, nodes);
    if(nodes == NULL){
        printf("INVALID\n");

        return 0;
    }

    //Do cycle detection (Can make this more efficient, but I'm being lazy)
    // if(cycleDetection(nodes)){   //<--A lot of memory leaks here
    //     //How to deal with memory leaks here?
    //     printf("INVALID\n");
    //     return 0;
    // }

    // Find the heads of the trees so we can bfs
    LinkedList* heads = findHead2(nodes);
    LinkedList* h = heads;

    FILE* outputFile = fopen("output.txt", "w");
    while(heads != NULL){
        LinkedList* next = heads->next;
        processOutput(outputFile, heads->node);
        freeTree(heads->node);

        if(heads->next != NULL){
            printf("\n");
            fprintf(outputFile, "\n");
        }
        heads = next;
    }

    freeVisited(h);
    fclose(outputFile);
    fclose(file);
    return 1;
}

/*
    Given an input file, create a heirarchy similar to java inheritance
    Characters next to each other are [Parent][Child]

    1. Create a tree struct that can have any number of children
        - Children is a linked list

    Figure out invalid cases
    Output siblings in alphabetical order
    Figure out spacing for siblings in same layer but different parents
*/

// Given the input file, create the tree
/*
    For each input, check if it already exists
        If it does, add a child to the node
        If it doesn't, create a new node as a child of the previous node
*/
LinkedList* createTree(FILE* file, LinkedList* nodes){
    char parentName;
    char childName;

    while(fscanf(file, " %c %c", &parentName, &childName) != EOF){
        // Check if the parent and child exist already
        TreeNode* parent;
        TreeNode* child;
        bool parentFound = false;
        bool childFound = false;
        LinkedList* curr = nodes;
        while(curr != NULL && !(parentFound && childFound)){
            if(curr->node->name == parentName){
                parentFound = true;
                parent = curr->node;
            }

            if(curr->node->name == childName){
                childFound = true;
                child = curr->node;
            }

            curr = curr->next;
        }

        if(childFound){
            if(child->hasParent){
                LinkedList* heads = findHead2(nodes);
                while(heads != NULL){
                    LinkedList* next = heads->next;
                    freeTree(heads->node);
                    heads = next;
                }
                return NULL;
            }
        }
        else{   //Create a new node if the child doesn't exist
            child =  createNode(childName);
            nodes = addList(nodes, child);
        }

        // Create a new node if the parent doesn't exist
        if(!parentFound){
            parent = createNode(parentName);
            nodes = addList(nodes, parent);
        }

        // Make c a child of p
        if(!child->hasParent){  //If statement uneccessary
            parent->children = addList(parent->children, child);
            child->hasParent = true;
        }
    }

    return nodes;
}

TreeNode* createNode(char name){
    TreeNode* node = malloc(sizeof(TreeNode));
    node->name = name;
    node->hasParent = false;
    node->children = NULL;

    return node;
}

LinkedList* addList(LinkedList* list, TreeNode* node){
    if(list == NULL){
        list = malloc(sizeof(LinkedList));
        list->node = node;
        list->next = NULL;
        return list;
    }

    LinkedList* head = list;
    while(head->next != NULL){
        head = head->next;
    }

    head->next = malloc(sizeof(LinkedList));
    head->next->node = node;
    head->next->next = NULL;

    return list;
}

//Modify to instead of deleting, just creating a new linked list.
LinkedList* findHead2(LinkedList* nodes){
    LinkedList* visited = NULL;

    LinkedList* curr = nodes;
    while(curr != NULL){
        LinkedList* child = curr->node->children;

        while(child != NULL){
            visited = addList(visited, child->node);
            child = child->next;
        }

        curr = curr->next;
    }

    LinkedList* heads = nodes;
    curr = heads;
    while(curr != NULL){
        LinkedList* next = curr->next;
        if(contains(visited, curr->node)){
            heads = delete(heads, curr);
        }
        curr = next;
    }

    freeVisited(visited);

    return heads;
}

//Delete node from nodes, and return the new head (in case the deleted one is the head)
LinkedList* delete(LinkedList* nodes, LinkedList* node){
    LinkedList* prev = NULL;
    LinkedList* curr = nodes;

    while(curr != NULL){
        if(curr == node){
            if(prev != NULL){
                prev->next = curr->next;
                free(curr);

                return nodes;
            }
            else{   //Deleting from the head of the linked list
                LinkedList* next = curr->next;
                free(curr);
                return next;
            }
        }

        prev = curr;
        curr = curr->next;
    }

    return nodes;
}

// Check if the linkedlsit contains a specified node
bool contains(LinkedList* visited, TreeNode* node){
    while(visited != NULL){
        if(visited->node == node) return true;

        visited = visited->next;
    }

    return false;
}

// Prints out the tree, formatted in teh required way into the output file
void processOutput(FILE* outputFile, TreeNode* head){
    Queue* q = initQueue();
    
    push(q, NODE, head);
    push(q, NEWLINE, NULL);
    int childrenInLayer = 1;    //Keep track of number of children in layer to know when to print space vs newline
    int childrenInNextLayer = 0;

    // BFS to formatted output correctly
    while(q->list != NULL){
        TreeNode* node = q->list->node;
        Action a = pull(q);
        switch(a){
            case NODE:
                fprintf(outputFile, "%c", node->name);
                printf("%c", node->name);
                childrenInLayer--;

                LinkedList* children = node->children;
                LinkedList* minChild = findMin(children);
                sortList(children);
                children = minChild;

                if(children == NULL){
                    push(q, POUND, NULL);

                    if(childrenInLayer == 0){
                        childrenInLayer = childrenInNextLayer;
                        childrenInNextLayer = 0;
                        push(q, NEWLINE, NULL);
                    }
                    else push(q, SPACE, NULL);
                    break;
                }

                while(children != NULL){
                    push(q, NODE, children->node);
                    children = children->next;
                    childrenInNextLayer++;
                }

                if(childrenInLayer == 0){
                    childrenInLayer = childrenInNextLayer;
                    childrenInNextLayer = 0;
                    push(q, NEWLINE, NULL);
                } 
                else push(q, SPACE, NULL);
                break;
            case POUND:
                fprintf(outputFile, "#");
                printf("#");
                break;
            case SPACE:
                fprintf(outputFile, " ");
                printf(" ");
                break;
            case NEWLINE:
                fprintf(outputFile, "\n");
                printf("\n");
                break;
        }
    }
    freeQueue(q);
}

void freeTree(TreeNode* head){
    freeTreeUtil(head);
}

void freeTreeUtil(TreeNode* head){
    if(head->children == NULL){
        free(head);
        return;
    }

    freeListUtil(head->children);
    free(head);
}

void freeListUtil(LinkedList* list){
    if(list == NULL){
        return;
    }

    LinkedList* prev = NULL;
    while(list != NULL){
        freeTreeUtil(list->node);
        prev = list;
        list = list->next;

        free(prev);
    }
}

// When keeping track of visited nodes, we don't want to delete the nodes, but we do want to free the rest of the linkedlist
void freeVisited(LinkedList* visited){
    if(visited == NULL) return;

    freeVisited(visited->next);

    free(visited);
}

//Iterate through the list of nodes, and apply cycle detection to each
bool cycleDetection(LinkedList* list){
    int i = 0;

    while(list != NULL){
        LinkedList* visited = NULL;

        if(cycleDetectionUtil(list->node, visited)){
            //Free the list
            // freeVisited(visited);   //<-- The list isn't global, so visited should be null here.
            return true;
        }

        //TODO: free the list
        freeVisited(visited);
        
        i++;
        list = list->next;
    }

    return false;
}

//DFS through the tree
bool cycleDetectionUtil(TreeNode* node, LinkedList* visited){
    if(node == NULL){
        return false;
    }
    if(contains(visited, node)){
        return true;
    }

    visited = addList(visited, node);   //memory management of this?

    LinkedList* curr = node->children;
    while(curr != NULL){
        if(cycleDetectionUtil(curr->node, visited)) return true;
        
        curr = curr->next;
    }

    // freeVisited(visited);

    return false;
}