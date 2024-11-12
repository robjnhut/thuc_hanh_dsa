//22520251
//Nguyen Huu Dinh
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:	
    string url;
    Node* prev;
    Node* next;

    Node(string url) : url(url), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
public:
    Node* current; // Current node in the history
    Node* head;    // Head node for the homepage

    // Constructor initializes the head to nullptr
    BrowserHistory() {
        head = nullptr;
        current = nullptr;
    }

    // Visit a new URL and clear forward history
    void visit(string url) {
        Node* newNode = new Node(url);
        if (current) {
            current->next = newNode; // Link current to the new node
            newNode->prev = current;  // Link new node back to current
        } else {
            head = newNode; // If it's the first visit, set head to the new node
        }
        current = newNode; // Move current to the new node
    }

    // Move back in history
    string back() {
        if (current && current->prev) {
            current = current->prev; // Move to the previous node
        }
        return current ? current->url : "No previous URL"; // Return the current URL
    }

    // Move forward in history
    string forward() {
        if (current && current->next) {
            current = current->next; // Move to the next node
        }
        return current ? current->url : "No forward URL"; // Return the current URL
    }

    ~BrowserHistory() {
        Node* temp;
        while (head) { // Cleanup all nodes starting from head
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Function to process input and simulate the browser history
void processBrowserHistory() {
    BrowserHistory* browserHistory = new BrowserHistory(); // Create BrowserHistory instance

    string command;
    while (getline(cin, command)) { // Read full line for commands
        if (command.substr(0, 5) == "visit") {
            string urls = command.substr(6); // Get URLs part after "visit "
            stringstream ss(urls);
            string url;

            while (getline(ss, url, ',')) { // Split by comma
                browserHistory->visit(url);
            }
            cout << "Visited: " << urls << endl; // Output for visit
        } else if (command == "back") {
            cout << "Current URL: " << browserHistory->back() << endl; // Output current URL after back
        } else if (command == "forward") {
            cout << "Current URL: " << browserHistory->forward() << endl; // Output current URL after forward
        }else if(command =="exit"){
        	break;
		}
		 else {
            cout << "Unknown command." << endl; // Handle unknown commands
        }
    }

    delete browserHistory;  // Cleanup
}

int main() {
    processBrowserHistory();  // Process browser history commands
    return 0;
}

