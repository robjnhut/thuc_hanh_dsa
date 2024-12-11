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

// Function to merge two binary trees
Node* mergeTrees(Node* t1, Node* t2) {
    if (!t1) return t2; // If first tree is empty, return second tree
    if (!t2) return t1; // If second tree is empty, return first tree

    // Add the values of overlapping nodes
    t1->key += t2->key;

    // Recursively merge left and right subtrees
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);

    return t1;
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
Node* createTree1() {
    Node* root = new Node(1);
    root->left = new Node(3);
    root->right = new Node(2);
    root->left->left = new Node(5);
    return root;
}

Node* createTree2() {
    Node* root = new Node(2);
    root->left = new Node(1);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->right = new Node(7);
    return root;
}

// Main Function
int main() {
    // Manually create two binary trees
    Node* tree1 = createTree1();
    Node* tree2 = createTree2();

    // Print the first tree
    cout << "Tree 1 Structure:\n";
    printTree(tree1);

    // Print the second tree
    cout << "\nTree 2 Structure:\n";
    printTree(tree2);

    // Merge the two trees
    Node* mergedTree = mergeTrees(tree1, tree2);

    // Print the merged tree
    cout << "\nMerged Tree Structure:\n";
    printTree(mergedTree);

    return 0;
}
