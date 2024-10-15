//22520251
//Nguyen Huu Dinh

#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;
};

class Stack {
public:
    Stack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            cerr << "Error: Cannot pop from an empty stack." << endl;
            return -1;
        }
        int value = top->value;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    int topValue() {
        if (top == nullptr) {
            cerr << "Error: Stack is empty." << endl;
            return -1;
        }
        return top->value;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

private:
    Node* top;
};

void visiblePeople(int heights[], int n) {
    int* answer = new int[n];
    for (int i = 0; i < n; i++) {
        answer[i] = 0;  // Initialize answer
    }

    Stack stack;  // Initialize stack

    for (int i = n - 1; i >= 0; i--) {
        int visibleCount = 0; // Count of visible people for current person

        // Pop elements that cannot be seen
        while (!stack.isEmpty() && heights[i] > stack.topValue()) {
            stack.pop(); 
            visibleCount++; // Increment visible count for each person popped
        }

        // If the stack is not empty, it means there's at least one person visible
        if (!stack.isEmpty()) {
            visibleCount++; // Count the immediate person on top of the stack
        }

        answer[i] = visibleCount; // Store the count in the answer array

        // Push the current height onto the stack
        stack.push(heights[i]);
    }

    // Output the results
    for (int i = 0; i < n; i++) {
        cout << answer[i] << " ";
    }
    cout << endl;

    delete[] answer;  // Clean up
}

int main() {
    int n;
    cout << "Enter the number of people: ";
    cin >> n;

    int* heights = new int[n];
    cout << "Enter the heights: ";
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    visiblePeople(heights, n);

    delete[] heights; // Clean up
    return 0;
}

