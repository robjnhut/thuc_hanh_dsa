#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* topNode;
    int maxSize;     // Giới hạn của stack
    int currentSize; // Đếm số lượng phần tử hiện tại

public:
    // Constructor khởi tạo stack với kích thước tối đa
    Stack(int size) : topNode(nullptr), maxSize(size), currentSize(0) {}

    // Kiểm tra stack rỗng
    bool isEmpty() {
        return topNode == nullptr;
    }

    // Kiểm tra stack đầy
    bool isFull() {
        return currentSize == maxSize;
    }

    // Đẩy phần tử vào stack
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full! Cannot push " << value << endl;
            return;
        }
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        currentSize++; // Tăng số lượng phần tử
        cout << value << " pushed onto the stack." << endl;
    }

    // Lấy phần tử ra khỏi stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }

        int value = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        currentSize--; // Giảm số lượng phần tử
        return value;
    }

    // Lấy phần tử trên đỉnh stack
    int top() {
        if (!isEmpty()) {
            return topNode->data;
        }
        cout << "Stack is empty." << endl;
        return -1;
    }

    // In ra các phần tử trong stack
    void stackOutput() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node* temp = topNode;
        cout << "Stack contents: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    int maxSize;
    cout << "Enter the size of the stack: ";
    cin >> maxSize;

    Stack stack(maxSize); // Khởi tạo stack với kích thước tối đa
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Check full\n";
        cout << "5. Check empty\n";
        cout << "6. Display stack\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            stack.push(value);
            break;
        case 2:
            value = stack.pop();
            if (value != -1) {
                cout << "Popped element: " << value << endl;
            }
            break;
        case 3:
            value = stack.top();
            if (value != -1) {
                cout << "Top element: " << value << endl;
            }
            break;
        case 4:
            if (stack.isFull()) {
                cout << "Stack is full." << endl;
            } else {
                cout << "Stack is not full." << endl;
            }
            break;
        case 5:
            if (stack.isEmpty()) {
                cout << "Stack is empty." << endl;
            } else {
                cout << "Stack is not empty." << endl;
            }
            break;
        case 6:
            stack.stackOutput();
            break;
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
