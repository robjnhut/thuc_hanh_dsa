#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

// Node structure for stack
struct Node {
    int index; // Index of the fruit in prices
    Node* next; // Pointer to the next node

    Node(int i) : index(i), next(nullptr) {}
};

// Stack implementation using a linked list
class Stack {
private:
    Node* topNode; // Pointer to the top node of the stack

public:
    Stack() : topNode(nullptr) {}

    // Push an index onto the stack
    void push(int index) {
        Node* newNode = new Node(index);
        newNode->next = topNode;
        topNode = newNode;
    }

    // Pop an index from the stack
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    // Get the index of the top element
    int top() {
        if (topNode) {
            return topNode->index;
        }
        return -1; // Error value
    }

    // Check if the stack is empty
    bool isEmpty() {
        return topNode == nullptr;
    }

    // Destructor to clean up the stack
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Function to calculate the minimum coins needed to buy all fruits
int minimumCoins(int prices[], int n) {
    // Start from the second last element and work backwards
    for (int i = (n - 1) / 2; i >= 0; --i) {
        // Calculate the range of the child nodes
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        // Find the minimum between left and right child if they exist
        if (leftChild < n && rightChild < n) {
            prices[i] += min(prices[leftChild], prices[rightChild]);
        } else if (leftChild < n) {
            prices[i] += prices[leftChild]; // Only left child exists
        }
    }

    return prices[0]; // Return the total coins needed
}

int main() {
    int prices[] = {3, 1, 2}; // Example 1 prices
    int prices2[] = {1, 10, 1, 1}; // Example 2 prices
    int prices3[] = {26, 18, 6, 12, 49, 7, 45, 45}; // Example 3 prices

    int n = sizeof(prices) / sizeof(prices[0]); // Number of fruits in example 1
    int k = sizeof(prices2) / sizeof(prices2[0]); // Number of fruits in example 2
    int l = sizeof(prices3) / sizeof(prices3[0]); // Number of fruits in example 3

    int result = minimumCoins(prices, n); // Calculate the minimum coins needed for example 1
    int result2 = minimumCoins(prices2, k); // Calculate the minimum coins needed for example 2
    int result3 = minimumCoins(prices3, l); // Calculate the minimum coins needed for example 3

    cout << "Minimum coins needed for example 1: " << result << endl; // Output the result for example 1
    cout << "Minimum coins needed for example 2: " << result2 << endl; // Output the result for example 2
    cout << "Minimum coins needed for example 3: " << result3 << endl; // Output the result for example 3

    return 0;
}
