

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