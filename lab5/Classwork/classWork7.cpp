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

// Recursive function to find the Lowest Common Ancestor (LCA)
Node* findLCA(Node* root, int n1, int n2) {
    if (!root) return nullptr; // Base case: empty tree

    // If the current node is one of the targets, return it
    if (root->key == n1 || root->key == n2) return root;

    // Recur for left and right subtrees
    Node* leftLCA = findLCA(root->left, n1, n2);
    Node* rightLCA = findLCA(root->right, n1, n2);

    // If both sides return non-null, the current node is the LCA
    if (leftLCA && rightLCA) return root;

    // Otherwise, return the non-null value (if any)
    return leftLCA ? leftLCA : rightLCA;
}

// Function to print the tree structure
void printTree(Node* node, int depth = 0) {
    if (!node) return;

    // Print right subtree
    printTree(node->right, depth + 1);

    // Print current node
    for (int i = 0; i < depth; ++i) {
        cout << "   ";
    }
    cout << node->key << endl;

    // Print left subtree
    printTree(node->left, depth + 1);
}

// Helper function to manually create a binary tree
Node* createTree() {
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    root->right->right = new Node(70);
    return root;
}

// Main Function
int main() {
    // Manually create the binary tree
    Node* root = createTree();

    // Print the binary tree structure
    cout << "Binary Tree Structure:\n";
    printTree(root);

    // Find the LCA of two nodes
    int n1 = 40, n2 = 50;
    Node* lca = findLCA(root, n1, n2);
    if (lca) {
        cout << "\nThe Lowest Common Ancestor of " << n1 << " and " << n2 << " is: " << lca->key << endl;
    } else {
        cout << "\nNodes " << n1 << " and " << n2 << " do not have an LCA in the tree.\n";
    }

    return 0;
}
