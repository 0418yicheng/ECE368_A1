#include "a1.h"
#include "Queue.c"

//TODO: Implement multiple trees, create a sorting function
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

    LinkedList* nodes = NULL;
    nodes = createTree(file, nodes);
    printf("Created Tree\n");

    //TODO: 
    TreeNode* head = findHead(nodes);

    processOutput(head, "output.txt");

    freeTree(head);

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
        // printf("%c %c\n", parentName, childName);
        // Check if the parent and child exist already
        TreeNode* parent;
        TreeNode* child;
        bool parentFound = false;
        bool childFound = false;
        LinkedList* curr = nodes;
        while(curr != NULL && !(parentFound && childFound)){
            if(curr->node->name == parentName){
                // printf("Parent Found\n");
                parentFound = true;
                parent = curr->node;
            }

            if(curr->node->name == childName){
                // printf("Child found\n");
                childFound = true;
                child = curr->node;
            }

            curr = curr->next;
        }
        // Create a new node if the parent doesn't exist
        if(!parentFound){
            parent = createNode(parentName);
            nodes = addList(nodes, parent);
        }

        // Create a new node if the child doesn't exist
        if(!childFound){
            child =  createNode(childName);
            nodes = addList(nodes, child);
        }

        // Make c a child of p
        parent->children = addList(parent->children, child);
    }

    return nodes;
}

TreeNode* createNode(char name){
    TreeNode* node = malloc(sizeof(TreeNode));
    node->name = name;
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

// Assume that there is only one head: To confirm, check at the end if all of the visited array has been traversed
TreeNode* findHead(LinkedList* nodes){
    LinkedList* visited = NULL;
    TreeNode* head = nodes->node;

    while(nodes != NULL){
        // printf("Checking %c...\n", nodes->node->name);
        // Skip the current iteration if we've already seen it. It cannot be the head
        if(contains(visited, nodes->node)){
            // printf("Skipping %c\n", nodes->node->name);
            nodes = nodes->next;
            continue;
        } 

        //Traverse through the children of the current node
        LinkedList* children = nodes->node->children;
        while(children != NULL){
            if(contains(visited, children->node)){
                //TODO: I think that this means the tree is invalid because the node would have 2 parents
                printf("\tSHIT\n");
                return NULL;    //INVALID condition
            }

            if(children->node == head){
                head = nodes->node;
            }
            visited = addList(visited, children->node);
            children = children->next;
        }
        nodes = nodes->next;
    }
    return head;
}

bool contains(LinkedList* visited, TreeNode* node){
    while(visited != NULL){
        if(visited->node == node) return true;

        visited = visited->next;
    }

    return false;
}

void processOutput(TreeNode* head, char* filename){
    FILE* outputFile = fopen(filename, "w");
    Queue* q = initQueue();
    
    push(q, NODE, head);
    push(q, NEWLINE, NULL);
    int childrenInLayer = 1;
    int childrenInNextLayer = 0;
    while(q->list != NULL){
        TreeNode* node = q->list->node;
        Action a = pull(q);
        switch(a){
            case NODE:
                fprintf(outputFile, "%c", node->name);
                childrenInLayer--;

                LinkedList* children = node->children; //<-- TODO: Sort this linked list

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
                break;
            case SPACE:
                fprintf(outputFile, " ");
                break;
            case NEWLINE:
                fprintf(outputFile, "\n");
                break;
        }
    }
    freeQueue(q);
    fclose(outputFile);
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