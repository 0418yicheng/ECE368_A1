#include "Queue.c"

int main(int argc, char** argv){
    Queue* q = initQueue();

    push(q, NODE, NULL);

    printf("Hello");
    printf("%d", pop(q));
}
