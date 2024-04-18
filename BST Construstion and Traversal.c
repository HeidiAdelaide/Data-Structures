#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new binary tree node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

// Recursive function to construct a binary search tree from in-order and post-order traversals
struct TreeNode* buildTree(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    // Create a new node with the current value from post-order traversal
    struct TreeNode* node = newNode(post[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd)
        return node;

    // Find the index of this node in in-order traversal
    int inIndex = findIndex(in, inStart, inEnd, node->data);

    // Construct right and left subtrees recursively
    node->right = buildTree(in, post, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(in, post, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to construct binary search tree from in-order and post-order traversals
struct TreeNode* bstconstruct(int in[], int post[], int n) {
    int postIndex = n - 1;
    return buildTree(in, post, 0, n - 1, &postIndex);
}

// Function to print nodes of binary search tree in BFS order
void printBFS(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Create a queue for BFS
    struct TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct TreeNode* current = queue[++front];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[++rear] = current->left;
        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

// Main function
int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    // Construct the binary search tree
    struct TreeNode* root = bstconstruct(inOrder, postOrder, n);

    // Print the binary search tree in BFS order
    printf("BFS traversal of the constructed BST is: ");
    printBFS(root);

}
