#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Functions for Tree Traversals

// 1. Pre-order Traversal (Root → Left → Right)
void preorder(Node* node) {
    if (node) {
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

// 2. In-order Traversal (Left → Root → Right)
void inorder(Node* node) {
    if (node) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

// 3. Post-order Traversal (Left → Right → Root)
void postorder(Node* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }
}

// Helper function to calculate the height of the tree
int height(Node* node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// Print nodes at a given level
void printLevel(Node* node, int level) {
    if (!node) return;

    if (level == 1) {
        cout << node->key << " ";
    } else {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

// 4. Level-order Traversal (Without queue)
void levelOrder(Node* node) {
    int h = height(node);
    for (int i = 1; i <= h; i++) {
        printLevel(node, i);
    }
}

// Main Function
int main() {
    // Manually create a binary tree
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    root->right->right = new Node(70);

    cout << "Pre-order Traversal: ";
    preorder(root);
    cout << endl;

    cout << "In-order Traversal: ";
    inorder(root);
    cout << endl;

    cout << "Post-order Traversal: ";
    postorder(root);
    cout << endl;

    cout << "Level-order Traversal: ";
    levelOrder(root);
    cout << endl;

    return 0;
}
