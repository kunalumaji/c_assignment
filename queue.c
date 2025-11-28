#include <stdio.h>
#include <stdlib.h>

#include "struct.h"


void insert_node(struct LinkedList* ll, struct Node* node);

void print_list(struct LinkedList* ll);

void enqueue(struct LinkedList* ll, struct Node* node) {
    insert_node(ll, node);
}

struct Node* dequeue(struct LinkedList* ll) {

    struct Node* result = ll->head;

    if (result == NULL) {
        return ll->head;
    }

    ll->head = result->next;
    ll->size -= 1;

    if (ll->head == NULL)
        ll->tail = NULL;
    else
        ll->head->previous = NULL;

    return result;
}

int main() {

    struct LinkedList ll = {0, NULL, NULL};

    while (1) {

        printf("1. Enqueue (at the end of Linked list)\n");
        printf("2. Dequeue (from the head of linked list)\n");
        printf("3. Print queue\n");
        printf("4. Exit\n");

        int user_input;
        printf("Select> ");
        scanf("%d", &user_input);

        if (user_input == 1) {
            int user_input_element;
            printf("Enter the element to enqueue> ");
            scanf("%d", &user_input_element);

            struct Node* node = malloc(sizeof(struct Node));
            node->data = user_input_element;
            node->previous = ll.tail;
            node->next = NULL;

            enqueue(&ll, node);
        }
        else if (user_input == 2) {
            struct Node* item = dequeue(&ll);

            if (item == NULL) {
                printf("queue is empty\n");
            }
            else {
                printf("Dequeued item: %d\n", item->data);
                free(item);
            }
        }
        else if (user_input == 3) {
            print_list(&ll);
        }
        else {
            break;
        }
    }

    return 0;
}