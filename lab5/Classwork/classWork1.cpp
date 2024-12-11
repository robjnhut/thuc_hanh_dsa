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

// Binary Tree class
class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    // Insert a value into the binary tree
    void insert(Node*& node, int value) {
        if (!node) {
            node = new Node(value);
            return;
        }

        char direction;
        cout << "Insert left (L) or right (R) of " << node->key << ": ";
        cin >> direction;

        if (direction == 'L' || direction == 'l') {
            insert(node->left, value);
        } else if (direction == 'R' || direction == 'r') {
            insert(node->right, value);
        } else {
            cout << "Invalid direction! Skipping insertion.\n";
        }
    }

    // Search for a value in the binary tree
    bool search(Node* node, int value) {
        if (!node) return false;

        if (node->key == value) return true;

        return search(node->left, value) || search(node->right, value);
    }

    // Delete a node with a specific value
    Node* deleteNode(Node* node, int value) {
        if (!node) return nullptr;

        if (node->key == value) {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: find the inorder successor (minimum in the right subtree)
            Node* successor = node->right;
            while (successor->left)
                successor = successor->left;

            // Replace node's key with successor's key and delete successor
            node->key = successor->key;
            node->right = deleteNode(node->right, successor->key);
        } else if (value < node->key) {
            node->left = deleteNode(node->left, value);
        } else {
            node->right = deleteNode(node->right, value);
        }

        return node;
    }

    // In-order Traversal
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    // Display the binary tree
    void display() {
        cout << "Binary Tree (In-order Traversal): ";
        inorder(root);
        cout << endl;
    }
};

// Main Function
int main() {
    BinaryTree tree;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert a value\n";
        cout << "2. Search for a value\n";
        cout << "3. Delete a value\n";
        cout << "4. Display tree (In-order Traversal)\n";
        cout << "0. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                if (!tree.root) {
                    tree.root = new Node(value);
                } else {
                    tree.insert(tree.root, value);
                }
                break;
            }
            case 2: {
                int value;
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(tree.root, value))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found in the tree.\n";
                break;
            }
            case 3: {
                int value;
                cout << "Enter value to delete: ";
                cin >> value;
                tree.root = tree.deleteNode(tree.root, value);
                cout << "Value deleted.\n";
                break;
            }
            case 4:
                tree.display();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
