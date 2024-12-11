#include <iostream>
#include <cmath>
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

// Binary Tree class (extended to implement BST operations)
class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    // Insert a value into the BST
    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }

        if (value < node->key) {
            node->left = insert(node->left, value);
        } else if (value > node->key) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Find the minimum value in the BST
    int findMin(Node* node) {
        if (!node) {
            cout << "Tree is empty.\n";
            return -1;
        }

        while (node->left) {
            node = node->left;
        }
        return node->key;
    }

    // Find the maximum value in the BST
    int findMax(Node* node) {
        if (!node) {
            cout << "Tree is empty.\n";
            return -1;
        }

        while (node->right) {
            node = node->right;
        }
        return node->key;
    }

    // Calculate the height of the tree
    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Check if the tree is balanced
    bool isBalanced(Node* node) {
        if (!node) return true;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return abs(leftHeight - rightHeight) <= 1 &&
               isBalanced(node->left) &&
               isBalanced(node->right);
    }

    // In-order traversal
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }
};

// Main Function
int main() {
    BinaryTree tree;

    // Manually create the BST
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 70);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 60);
    tree.root = tree.insert(tree.root, 80);

    cout << "In-order Traversal: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "Minimum value in the BST: " << tree.findMin(tree.root) << endl;
    cout << "Maximum value in the BST: " << tree.findMax(tree.root) << endl;
    cout << "Height of the tree: " << tree.height(tree.root) << endl;

    if (tree.isBalanced(tree.root)) {
        cout << "The tree is balanced.\n";
    } else {
        cout << "The tree is not balanced.\n";
    }

    return 0;
}
