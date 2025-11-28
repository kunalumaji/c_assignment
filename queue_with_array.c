#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


void enqueue(queue* q, int element) {
    //check if queue is full
    if ((q->end + 1) % q->size == q->start) {
        printf("queue is full\n");
        return;
    }
    //check if queue is empty (to set start and end ptr to 0)
    if (q->start == -1 && q->end == -1) {
        q->start = 0;
        q->end = 0;
        q->data[q->end] = element;
        return;
    }
    //if not full then add the data on end+1 index (mod size)
    q->data[(q->end + 1) % q->size] = element;
    q->end = (q->end + 1) % q->size;
}


int dequeue(queue* q) {
    //if only one element
    if (q->start == q->end) {
        //queue might be empty, return error
        if (q->start == -1) {
            printf("queue is empty\n");
            exit(1);
        }
        int result = q->data[q->start];
        q->start = -1;
        q->end = -1;
        return result;
    }

    int result = q->data[q->start];
    q->start = (q->start + 1) % q->size;

    return result;
}


void print_queue(queue* q) {
    if (q->start == q->end && q->start == -1) {
        printf("queue is empty\n");
        return;
    }
    for (int i = q->start; i != q->end; i = (i+1)%q->size) {
        printf("%d ", q->data[i]);
    }
    printf("%d\n", q->data[q->end]);
}


queue* init_queue(int size) {
    queue* q = malloc(sizeof(queue));
    q->size = size;
    q->start = -1;
    q->end = -1;
    q->data = malloc(sizeof(int) * size);
    return q;
}


int main() {

    queue* q = init_queue(10);

    printf("Following queue is implemented using array. Perform the following action on the queue.\n");

    while (1) {

        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print queue\n");
        printf("4. Exit\n");

        int user_input;
        printf("Select> ");
        scanf("%d", &user_input);

        if (user_input == 1) {
            int user_input_element;
            printf("Enter the element to enqueue> ");
            scanf("%d", &user_input_element);

            enqueue(q, user_input_element);
        }
        else if (user_input == 2) {
            int item = dequeue(q);
            printf("Dequeued item: %d\n", item);
        }
        else if (user_input == 3) {
            print_queue(q);
        }
        else {
            break;
        }

    }

    free(q->data);
    free(q);

    return 0;
}