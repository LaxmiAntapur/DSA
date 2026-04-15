#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* create(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

struct node* insert(struct node* root, int key) {
    if (root == NULL)
        return create(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(struct node* root) {
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n--- HOSPITAL MENU ---\n");
        printf("1.Insert Patient ID\n2.Search Patient\n3.Display Sorted\n4.Min ID\n5.Max ID\n6.Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter ID: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Patient Found\n");
                else
                    printf("Not Found\n");
                break;

            case 3:
                inorder(root);
                break;

            case 4:
                printf("Min ID: %d", findMin(root));
                break;

            case 5:
                printf("Max ID: %d", findMax(root));
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice");
        }
    }
}
