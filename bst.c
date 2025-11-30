//still yet to complete

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    char* name;
    struct Node* left;
    struct Node* right;
};

struct bst {
    int size;
    struct Node* root;
};
typedef struct bst bst;


void insert(bst* tree, struct Node* node) {
    //if root is null
    if (tree->root == NULL) {
        tree->root = node;
    }
    struct Node* current = tree->root;

    while (1) {
        if (node->id <= current->id) {
            //check if left is null to insert directly
            if (current->left == NULL) {
                current->left = node;
                tree->size += 1;
                break;
            }
            //else repeat same for current left child
            current = current->left;
        }
        else {
            if (current->right == NULL) {
                current->right = node;
                tree->size += 1;
                break;
            }
            current = current->right;
        }
    }
}


struct Node* search(bst* tree, int id) {

    struct Node* root = tree->root;

    while (root != NULL) {
        if (id == root->id)
            return root;
        if (id < root->id) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }

    return NULL;
}


void recursive_delete(struct Node* root, struct Node* parent, int id, int is_left_child) {

    if (root == NULL)
        return;

    if (root->id == id) {
        int childs = 0;
        if (root->left != NULL) childs++;
        if (root->right != NULL) childs++;

        if (childs == 0) {
            if (is_left_child)
                parent->left = NULL;
            else
                parent->right = NULL;

            free(root);
        }
        else if (childs == 1) {
            if (root->left != NULL) {
                if (is_left_child)
                    parent->left = root->left;
                else
                    parent->right = root->left;
            }
            else {
                if (is_left_child)
                    parent->left = root->right;
                else
                    parent->right = root->right;
            }
        }
        else if (childs == 2) {
            struct Node* temp = root->left;
            struct Node* temp_parent = temp;
            while (temp->right != NULL) {
                temp_parent = temp;
                temp = temp->right;
            }
            recursive_delete(temp, temp_parent, temp->id, 0);
            if (is_left_child) {
                parent->left = temp;
                temp->left = root->left;
                temp->right = root->right;
            }
            else {
                parent->right = temp;
                temp->left = root->left;
                temp->right = root->right;
            }
        }
    }
}


void delete(bst* tree, int id) {

    struct Node* current = tree->root;

    struct Node* parent = NULL;
    while (1) {
        if (current == NULL) {
            printf("element not found\n");
            return;
        }
        if (current->id == id) {
            int childs = 0;
            if (current->left != NULL) childs++;
            if (current->right != NULL) childs++;

            if (childs == 0) {

            }
        }
        else if (id < current->id) {
            parent = current;
            current = current->left;
            continue;
        }
        else {
            parent = current;
            current = current->right;
            continue;
        }

    }

}


int main() {
    return 0;
}