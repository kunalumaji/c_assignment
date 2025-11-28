#include <stdio.h>
#include <stdlib.h>

struct stack {
    int top;
    int size;
    int* data;
};
typedef struct stack stack;


stack* init_stack(int size) {
    stack* s = malloc(sizeof(stack));
    s->top = -1;
    s->size = size;
    s->data = malloc(sizeof(int) * size);
    return s;
}


void push(stack* s, int element) {
    //if stack is not full
    if (s->top + 1 != s->size) {
        s->data[s->top + 1] = element;
        s->top += 1;
        return;
    }

    printf("stack is full\n");
}


int pop(stack* s) {
    //if stack is not empty
    if (s->top != -1) {
        return s->data[s->top--];
    }
    printf("stack is empty\n");
    exit(1);
}


void print_stack(stack* s) {
    //if stack is not empty
    if (s->top != -1) {
        for (int i = s->top; i >= 0; i--) {
            printf("%d ", s->data[i]);
        }
        printf("\n");
        return;
    }
    printf("stack is empty\n");
}


int main() {

    stack* s = init_stack(10);

    printf("Following stack is implemented using array. Perform the following action on the stack.\n");

    while (1) {

        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Print stack\n");
        printf("4. Exit\n");

        int user_input;
        printf("Select> ");
        scanf("%d", &user_input);

        if (user_input == 1) {
            int user_input_element;
            printf("Enter the element to push> ");
            scanf("%d", &user_input_element);

            push(s, user_input_element);
        }
        else if (user_input == 2) {
            int item = pop(s);
            printf("Popped item: %d\n", item);
        }
        else if (user_input == 3) {
            print_stack(s);
        }
        else {
            break;
        }

    }

    free(s->data);
    free(s);

    return 0;
}