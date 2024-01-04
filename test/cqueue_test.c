#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "test.h"


// Example usage for a void* queue
DEFINE_QUEUE(void)

int queue_test() {
    struct Queue_void* myQueue;
    myQueue = (struct Queue_void*)malloc(sizeof(struct Queue_void));
    initQueue_void(myQueue);

    int a = 10;
    double b = 20.5;
    char c = 'X';

    enqueue_void(myQueue, &a);
    enqueue_void(myQueue, &b);
    enqueue_void(myQueue, &c);

    int* dequeued_a = (int*)dequeue_void(myQueue);
    double* dequeued_b = (double*)dequeue_void(myQueue);
    char* dequeued_c = (char*)dequeue_void(myQueue);

    printf("Dequeued element: %d\n", *dequeued_a);
    printf("Dequeued element: %lf\n", *dequeued_b);
    printf("Dequeued element: %c\n", *dequeued_c);

    free(myQueue);

    return 0;
}