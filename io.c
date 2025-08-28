#include "a1.h"

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");

    // char parent;
    // char child;

    // while(fscanf(file, " %c %c", &parent, &child) == 2){
    //     printf("%c %c\n", parent, child);
    // }
    // if(file = NULL){
    //     printf("Error opening file\n");
    //     return 0;
    // }

    createTree(file, NULL);

    fclose(file);
}

TreeNode* createTree(FILE* file, LinkedList* visited){
    char parent;
    char child;

    while(fscanf(file, " %c %c", &parent, &child) == 2){
        printf("%c %c\n", parent, child);
    }

    return NULL;
}