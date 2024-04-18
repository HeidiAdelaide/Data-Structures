
#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new BST node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a node into BST from array
struct Node* insertBST(struct Node* root, int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    root = newNode(arr[mid]);

    root->left = insertBST(root->left, arr, start, mid - 1);
    root->right = insertBST(root->right, arr, mid + 1, end);

    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function to find the level of a node in BST
int findLevel(struct Node* root, int key, int level) {
    if (root == NULL)
        return -1;

    if (root->data == key)
        return level;

    int downLevel = findLevel(root->left, key, level + 1);
    if (downLevel != -1)
        return downLevel;

    downLevel = findLevel(root->right, key, level + 1);
    return downLevel;
}

// Function to print level and height of a node in BST
void printLevelAndHeight(struct Node* root, int key) {
    int level = findLevel(root, key, 0);
    int h = height(root);
    if (level == -1)
        printf("Node not found in BST\n");
    else
        printf("Level of %d: %d\nHeight of BST: %d\n", key, level, h);
}

// Function to print the inorder traversal of BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = insertBST(NULL, arr, 0, n - 1);

    printf("Inorder traversal of BST: ");
    inorderTraversal(root);
    printf("\n");

    int nodeToDelete = 25;
    root = deleteNode(root, nodeToDelete);
    printf("BST after deleting node %d: ", nodeToDelete);
    inorderTraversal(root);
    printf("\n");

    printf("Height of BST: %d\n", height(root));

    int nodeToFind = 20;
    printLevelAndHeight(root, nodeToFind);

    return 0;
}



