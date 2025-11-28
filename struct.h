

struct Node {
    int data;
    struct Node* previous;
    struct Node* next;
};

struct LinkedList {
    int size;
    struct Node* head;
    struct Node* tail;
};

struct queue {
    int size;
    int start;
    int end;
    int* data;
};
typedef struct queue queue;