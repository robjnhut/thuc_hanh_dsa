
#include <iostream>
#include <iomanip>

using namespace std;

class Node {
	public:
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
        return -1;  // Special value to indicate an error
    }
    int value = top->value;
    Node* temp = top;     // Store the current top
    top = top->next;      // Move the top pointer to the next node
    delete temp;          // Free memory of the popped node
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

 void display() {
    Node* current = top;
    cout << "STACK = < ";
    while (current != nullptr) {    // Traverse the stack
        cout << current->value << " ";
        current = current->next;
    }
    cout << ">" << endl;
}


public:
    Node* top;
};

void displayTowers(Stack& towerA, Stack& towerB, Stack& towerC) {
    cout << "A Tower\n";
    towerA.display();
    cout << "B Tower\n";
    towerB.display();
    cout << "C Tower\n";
    towerC.display();
    cout << "===================\n";
}

bool isValidMove(Stack& source, Stack& destination) {
    if (source.isEmpty()) {
        cerr << "Error: Cannot move from an empty source stack." << endl;
        return false;
    }

    if (destination.isEmpty()) {
        return true;
    }

    return source.topValue() < destination.topValue();
}


void moveDisk(Stack& source, Stack& destination) {
    if (isValidMove(source, destination)) {
        int disk = source.pop();
        if (disk != -1) { // Ensure the move is valid
            destination.push(disk);
        }
    } else {
        cerr << "Invalid move. Please try again." << endl;
    }
}


bool isGameWon(Stack& towerC, int numDisks) {
    // If towerC is empty, the game is not won
    if (towerC.isEmpty()) {
        return false;
    }

    // Temporary variable to pop values from towerC for verification
    Node* current = towerC.top;
    int expectedDisk = 1; // We expect the smallest disk at the top (1) and the largest at the bottom (numDisks)

    // Traverse through the stack
    while (current != nullptr) {
        if (current->value != expectedDisk) {
            return false; // If disks are not in expected ascending order, game isn't won
        }
        current = current->next;
        expectedDisk++; // Move to the next expected larger disk
    }

    // Check if we have exactly the number of disks
    return expectedDisk - 1 == numDisks;
}
int main() {
    const int numDisks = 3; // Adjust the number of disks as needed

    Stack towerA, towerB, towerC;

    // Initialize tower A with disks in descending order (3, 2, 1)
    for (int i = numDisks; i > 0; i--) {
        towerA.push(i);
    }

    cout << "=========== Demo Stack ===========\n";
    cout << "0. Creating Tower.\n";
    cout << "1. A -> B.\n";
    cout << "2. B -> A.\n";
    cout << "3. B -> C.\n";
    cout << "4. C -> B.\n";
    cout << "5. C -> A.\n";
    cout << "6. A -> C.\n";
    cout << "===================================\n";

    displayTowers(towerA, towerB, towerC);

    int move;
    while (!isGameWon(towerC, numDisks)) {
        cout << "Please input a move (1-6): ";
        cin >> move;

        switch (move) {
            case 1:
                moveDisk(towerA, towerB); // A -> B
                break;
            case 2:
                moveDisk(towerB, towerA); // B -> A
                break;
            case 3:
                moveDisk(towerB, towerC); // B -> C
                break;
            case 4:
                moveDisk(towerC, towerB); // C -> B
                break;
            case 5:
                moveDisk(towerC, towerA); // C -> A
                break;
            case 6:
                moveDisk(towerA, towerC); // A -> C
                break;
            default:
                cerr << "Invalid move. Please enter a number between 1 and 6." << endl;
                continue;
        }
        
        displayTowers(towerA, towerB, towerC);
    }

    cout << "Congratulations! You won the Tower of Hanoi puzzle." << endl;

    return 0;
}

