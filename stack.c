#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void insert_node(struct LinkedList* ll, struct Node* node);

void print_list(struct LinkedList* ll);

//push is simple insert into linked list
void push(struct LinkedList* ll, struct Node* node) {
    insert_node(ll, node);
}

//returns the tail of linked list
struct Node* pop(struct LinkedList* ll) {
    //if stack is empty or ll is empty
    if (ll->tail == NULL) {
        return NULL;
    }
    //set the tail ptr to previous element
    struct Node* result = ll->tail;
    ll->tail = ll->tail->previous;
    ll->size -= 1;

    if (ll->size == 0)
        ll->head = NULL; //set head to null when stack becomes empty
    else
        ll->tail->next = NULL; //else set next ptr of new tail to NULL

    return result;
}


int main() {

    struct LinkedList ll = {0, NULL, NULL};

    while (1) {

        printf("1. Push (at the end of Linked list)\n");
        printf("2. Pop (from the end of linked list)\n");
        printf("3. Print stack\n");
        printf("4. Exit\n");

        int user_input;
        printf("Select> ");
        scanf("%d", &user_input);

        if (user_input == 1) {
            int user_input_element;
            printf("Enter the element to push> ");
            scanf("%d", &user_input_element);

            struct Node* node = malloc(sizeof(struct Node));
            node->data = user_input_element;
            node->previous = ll.tail;
            node->next = NULL;

            push(&ll, node);
        }
        else if (user_input == 2) {
            struct Node* popped_item = pop(&ll);

            if (popped_item == NULL) {
                printf("stack is empty\n");
            }
            else {
                printf("Popped item: %d\n", popped_item->data);
                free(popped_item);
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