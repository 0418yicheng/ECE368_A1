#include "a1.h"
#include "Queue.c"
#include "sort.c"

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
    if(nodes == NULL){
        printf("INVALID\n");

        fclose(file);
         
        return 0;
    }

    //Do cycle detection
    if(cycleDetection(nodes)){
        printf("INVALID\n");
        TreeNode* node = nodes->node;

        freeVisited(nodes);
        freeCycle(node, NULL);

        fclose(file);
        return 0;
    }

    // Find the heads of the trees so we can bfs
    LinkedList* heads = findHead2(nodes);
    freeVisited(nodes);
    LinkedList* h = heads;

    while(heads != NULL){
        LinkedList* next = heads->next;
        processOutput(heads->node);
        freeTree(heads->node);

        if(heads->next != NULL){
            printf("\n");
        }
        heads = next;
    }

    freeVisited(h);
    fclose(file);
    return 1;
}

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
                freeVisited(nodes);
                LinkedList* h = heads;
                while(heads != NULL){
                    LinkedList* next = heads->next;
                    freeTree(heads->node);
                    heads = next;
                }
                freeVisited(h);
                
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

    LinkedList* heads = NULL;
    curr = nodes;
    while(curr != NULL){
        if(!contains(visited, curr->node)){
            heads = addList(heads, curr->node);
        }

        curr = curr->next;
    }

    freeVisited(visited);

    return heads;
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
void processOutput(TreeNode* head){
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
                printf("%c", node->name);
                childrenInLayer--;

                LinkedList* children = node->children;
                LinkedList* minChild = findMin(children);
                sortList(children);
                children = minChild;
                node->children = children;

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
                printf("#");
                break;
            case SPACE:
                printf(" ");
                break;
            case NEWLINE:
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
    freeListUtil(head->children);
    free(head);
}

void freeListUtil(LinkedList* list){
    if(list == NULL){
        return;
    }

    while(list != NULL){
        freeTreeUtil(list->node);
        LinkedList* next = list->next;

        free(list);

        list = next;
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

    while(list != NULL){
        if(cycleDetectionUtil(list->node, NULL)){
            return true;
        }
        
        list = list->next;
    }

    return false;
}

//DFS through the tree while keeping track of a visited list
bool cycleDetectionUtil(TreeNode* node, LinkedList* visited){
    if(node == NULL){
        return false;
    }
    if(contains(visited, node)){
        return true;
    }

    visited = addList(visited, node);

    LinkedList* curr = node->children;
    while(curr != NULL){
        if(cycleDetectionUtil(curr->node, visited)){
            //Remove the node just added to the linkedlist
            LinkedList* l = visited;
            LinkedList* prev = NULL;
            while(l->next != NULL){
                l = l->next;
                if(prev != NULL) prev = prev->next;
                else prev = visited;
            }

            if(prev != NULL) prev->next = NULL;
            free(l);
            return true;
        } 
        
        curr = curr->next;
    }

    //Remove the added visited node from the list:
    LinkedList* l = visited;
    LinkedList* prev = NULL;
    while(l->next != NULL){
        l = l->next;
        if(prev != NULL) prev = prev->next;
        else prev = visited;
    }

    if(prev != NULL) prev->next = NULL;
    free(l);

    return false;
}

void freeCycle(TreeNode* node, LinkedList* visited){
    if(contains(visited, node)){
        freeVisited(visited);
        return;
    }

    visited = addList(visited, node);

    freeListCycle(node->children, visited);

    free(node);
}

void freeListCycle(LinkedList* list, LinkedList* visited){
    if(list == NULL){
        return;
    }

    while(list != NULL){
        LinkedList* next = list->next;
        freeCycle(list->node, visited);
        free(list);
        list = next;
    }
}