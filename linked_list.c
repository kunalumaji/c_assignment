#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void insert_node(struct LinkedList* ll, struct Node* node) {
    struct Node* head = ll->head;
    if (head == NULL) {
        ll->head = node;
    }
    else {
        // while (head->next != NULL) {
        //     head = head->next;
        // }
        ll->tail->next = node;
        // head->next = node;
        node->previous = ll->tail;
    }
    ll->size += 1;
    ll->tail = node;
}

void print_list(struct LinkedList* ll) {
    struct Node* head = ll->head;

    if (head != NULL)
        printf("Head: %d\n", head->data);
    else
        printf("Head: (NULL)\n");
    if (ll->tail != NULL)
        printf("Tail: %d\n", ll->tail->data);
    else
        printf("Tail: (NULL)\n");

    while (head != NULL) {
        if (head->previous != NULL)
            printf("(%d)",head->previous->data);
        else
            printf("(NULL)");

        printf("<-%d->", head->data);

        if (head->next != NULL)
            printf("(%d)",head->next->data);
        else
            printf("(NULL)");

        printf(" <--> ");
        head = head->next;
    }
    printf(" NULL \n");
    printf("Total Size: %d\n", ll->size);
}

void delete_element(struct LinkedList* ll, int element) {
    struct Node* head = ll->head;

    if (head != NULL && head->data == element) {
        ll->head = head->next;
        ll->size -= 1;
        if (ll->size == 0)
            ll->tail = NULL;
        else
            ll->head->previous = NULL;
        return;
    }

    while (head != NULL) {
        if (head->data == element) {
            struct Node* temp = head;
            if (temp->previous != NULL)
                head->previous->next = temp->next;
            else
                ll->tail = NULL; // never execute i think
            if (temp->next != NULL)
                head->next->previous = temp->previous;
            else
                ll->tail = temp->previous;

            free(temp);
            ll->size -= 1;
            return;
        }

        head = head->next;
    }
}
//
// int main() {
//
//     struct LinkedList ll = { 0, NULL, NULL };
//
//     printf("Linked list created. Perform following operations.\n");
//
//     while (1) {
//
//         printf("1. Add element (at the end)\n");
//         printf("2. Delete element (first occurence if found)\n");
//         printf("3. Print list (with meta data)\n");
//         printf("4. Exit\n");
//
//         printf("Select > ");
//         int user_input;
//         scanf("%d", &user_input);
//
//         if (user_input == 1 || user_input == 2) {
//             printf("Enter element (int type): ");
//             int user_element;
//             scanf("%d", &user_element);
//
//             if (user_input == 1) {
//                 struct Node* node = (struct Node*) malloc(sizeof(struct Node));
//                 node->data = user_element;
//                 node->previous = ll.tail;
//                 node->next = NULL;
//
//                 insert_node(&ll, node);
//             }
//             else {
//                 delete_element(&ll, user_element);
//             }
//         }
//         else if (user_input == 3) {
//             print_list(&ll);
//         }
//         else if (user_input == 4) {
//             break;
//         }
//         else {
//             printf("Invalid input\n");
//             break;
//         }
//     }
//
//     return 0;
// }