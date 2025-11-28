#include <stdio.h>
#include <stdlib.h>


struct darray {
    int size;
    int occupied;
    int* head;
};
typedef struct darray darray;


darray* INIT_DARRAY(int size, int* array) {

    darray* obj = malloc(sizeof(darray));

    if (obj != NULL) {
        obj->size = size;
        obj->occupied = size;
        obj->head = array; //pointer to first array element
    }

    return obj;
}


void APPEND_DARRAY(darray* array, int element) {
    double load_factor = (double) array->occupied / array->size;

    //check if free locations are <25%
    if (load_factor > 0.75) {

        printf("Free locations: %.2f (resizing)\n", (1 - load_factor)*100);
        int* temp = array->head;
        array->head = realloc(array->head, array->size*2*sizeof(int)); //point to new array
        array->size = array->size*2; //update the new size
    }
    array->head[array->occupied] = element;
    array->occupied += 1;

}


int GET_ELEMENT(darray* array, int index) {
    if (index < array->size) {
        return array->head[index];
    }
    //out of bound error
    printf("array index out of range\n");
    exit(EXIT_FAILURE);
}

void DELETE_ELEMENT(darray* array, int index) {
    //if last just modifying occupied slot
    if (index + 1 == array->occupied) {
        array->occupied -= 1;
        return;
    }
    //checking out of bound index
    if (index >= array->occupied || index < 0) {
        printf("array index out of range\n");
        return;
    }
    //else shift next elements by 1 position to left
    for (int i = index+1; i < array->occupied; i++) {
        array->head[i-1] = array->head[i];
    }
    array->occupied -= 1;
}

void PRINT_DARRAY(darray* array) {

    for (int i = 0; i < array->occupied; i++) {
        printf("%d ", array->head[i]);
    }
    printf("\n");

}

int main () {

    int* array = malloc(sizeof(int));
    array[0] = 10;

    darray* num = INIT_DARRAY(1, array); // array should be malloced

    printf("Dynamic array is initialized with 1 element (10). You can perform following actions\n");

    while (1) {

        printf("1. Add element (int type)\n");
        printf("2. Remove element (by index)\n");
        printf("3. Print array\n");
        printf("4. Exit and clean\n");

        printf("Select> ");
        int user_input;
        scanf("%d", &user_input);

        if (user_input == 1) {
            printf("Enter (int) element to add: ");
            int user_input_element;
            scanf("%d", &user_input_element);

            APPEND_DARRAY(num, user_input_element);
        }
        else if (user_input == 2) {
            printf("Enter (int) index to delete: ");
            int user_input_index;
            scanf("%d", &user_input_index);

            DELETE_ELEMENT(num, user_input_index);
        }
        else if (user_input == 3) {
            PRINT_DARRAY(num);
        }
        else if (user_input == 4) {
            break;
        }
        else {
            printf("Invalid input\n");
        }
    }

    free(num->head);
    free(num);

    return 0;
}