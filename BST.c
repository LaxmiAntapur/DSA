#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

typedef struct tree TREE;

// Function declarations
TREE* insert_into_bst(TREE*, int);
void inorder(TREE*);
void preorder(TREE*);
void postorder(TREE*);
TREE* delete_from_bst(TREE*, int);
TREE* find_min(TREE*);

// Insert into BST
TREE* insert_into_bst(TREE *root, int data) {
    TREE *newnode, *currnode, *parent;

    newnode = (TREE*)malloc(sizeof(TREE));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return root;
    }

    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    if (root == NULL) {
        printf("Root node inserted\n");
        return newnode;
    }

    currnode = root;
    parent = NULL;

    while (currnode != NULL) {
        parent = currnode;
        if (data < currnode->data)
            currnode = currnode->left;
        else
            currnode = currnode->right;
    }

    if (data < parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;

    printf("Node inserted successfully\n");
    return root;
}

// Inorder Traversal
void inorder(TREE *troot) {
    if (troot != NULL) {
        inorder(troot->left);
        printf("%d ", troot->data);
        inorder(troot->right);
    }
}

// Preorder Traversal
void preorder(TREE *troot) {
    if (troot == NULL)
        return;

    printf("%d ", troot->data);
    preorder(troot->left);
    preorder(troot->right);
}

// Postorder Traversal
void postorder(TREE *troot) {
    if (troot != NULL) {
        postorder(troot->left);
        postorder(troot->right);
        printf("%d ", troot->data);
    }
}

// Find minimum node (used in delete)
TREE* find_min(TREE *root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete from BST (CORRECT VERSION)
TREE* delete_from_bst(TREE *root, int data) {
    if (root == NULL) {
        printf("Item not found\n");
        return root;
    }

    if (data < root->data) {
        root->left = delete_from_bst(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete_from_bst(root->right, data);
    }
    else {
        // Node found

        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            TREE *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TREE *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        else {
            TREE *temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete_from_bst(root->right, temp->data);
        }
    }

    return root;
}

// Main function
int main() {
    TREE *root = NULL;
    int choice, data;

    while (1) {
        printf("\n***** MENU *****\n");
        printf("1. Insert\n");
        printf("2. Inorder\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. Delete\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = insert_into_bst(root, data);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                root = delete_from_bst(root, data);
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
