
#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to find index of value in inOrder array
int findIndex(int inOrder[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (inOrder[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to construct BST from inOrder and postOrder arrays
struct TreeNode* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    // Create a new node with the value at postIndex
    struct TreeNode* node = newNode(postOrder[*postIndex]);
    (*postIndex)--;

    // If the node has no children, return it
    if (inStart == inEnd) {
        return node;
    }

    // Find index of node value in inOrder array
    int inIndex = findIndex(inOrder, inStart, inEnd, node->data);

    // Construct right and left subtrees
    node->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    node->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to traverse the binary tree in breadth-first-search order
void bfsTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS
    struct TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* tempNode = queue[front++];
        printf("%d ", tempNode->data);

        if (tempNode->left != NULL) {
            queue[rear++] = tempNode->left;
        }
        if (tempNode->right != NULL) {
            queue[rear++] = tempNode->right;
        }
    }
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    int postIndex = n - 1; // Start from the last index of post-order array

    // Construct the BST
    struct TreeNode* root = bst_construct(inOrder, postOrder, 0, n - 1, &postIndex);

    // Traverse the BST in BFS order and print each element
    printf("BFS Traversal: ");
    bfsTraversal(root);

    return 0;
}

