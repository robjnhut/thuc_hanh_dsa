#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node* frontNode;  // phan tu dau hang
    Node* rearNode;  // phan tu cuoi hang
    int maxSize;     // Giới hạn của Queue
    int currentSize; // Đếm số lượng phần tử hiện tại

public:
    // Constructor khởi tạo Queue với kích thước tối đa
    Queue(int size) : frontNode(nullptr), rearNode(nullptr),maxSize(size), currentSize(0) {}

    // Kiểm tra Queue rỗng
    bool isEmpty() {
        return currentSize == 0;
    }

    // Kiểm tra Queue đầy
    bool isFull() {
        return currentSize == maxSize;
    }

    // Đẩy phần tử vào Queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full! Cannot push " << value << endl;
            return;
        }
        Node* newNode = new Node(value);
        if(isEmpty()){
            frontNode = rearNode = newNode;  // hàng đợi rỗng thì đầu với cuối = nhau
        }else{
            rearNode -> next = newNode;  //cho cuối ra sau
            rearNode = newNode;
        }
        currentSize ++; // đếm
        cout  << "value to enqueue: " << value<< endl;
        
    }

    // Lấy phần tử ra khỏi Queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }

        int value = frontNode->data; // Lưu giá trị phần tử đầu
        Node* temp = frontNode;      // Giữ lại phần tử đầu
        frontNode = frontNode->next; // Cập nhật phần tử đầu
        delete temp;                 // Xóa phần tử đã lấy ra
        currentSize--;               // Giảm số lượng phần tử
        return value;                // Trả về giá trị đã lấy
    }

    // Lấy phần tử trên đỉnh Queue
    int front() {
        if (!isEmpty()) {
            return frontNode->data;
        }
        cout << "Queue is empty." << endl;
        return -1;
    }

    int rear() {
        if (!isEmpty()) {
            return rearNode->data;
        }
        cout << "Queue is empty." << endl;
        return -1;
    }

    // In ra các phần tử trong Queue
    void queueOutput() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = frontNode;
        cout << "Queue contents: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


    int main() {
        int maxSize;
        cout << "Enter the size of the queue: ";
        cin >> maxSize;

        Queue queue(maxSize); // Khởi tạo hàng đợi với kích thước tối đa
        int choice, value;

        do {
            cout << "\nMenu:\n";
            cout << "1. Enqueue\n";
            cout << "2. Dequeue\n";
            cout << "3. Front\n";
            cout << "4. Rear\n";
            cout << "5. Check if empty\n";
            cout << "6. Check if full\n";
            cout << "7. Output queue\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                value = queue.dequeue();
                if (value != -1) {
                    cout << "Dequeued element: " << value << endl;
                }
                break;
            case 3:
                value = queue.front();
                if (value != -1) {
                    cout << "Front element: " << value << endl;
                }
                break;
            case 4:
                value = queue.rear();
                if (value != -1) {
                    cout << "Rear element: " << value << endl;
                }
                break;
            case 5:
                if (queue.isEmpty()) {
                    cout << "Queue is empty." << endl;
                } else {
                    cout << "Queue is not empty." << endl;
                }
                break;
            case 6:
                if (queue.isFull()) {
                    cout << "Queue is full." << endl;
                } else {
                    cout << "Queue is not full." << endl;
                }
                break;
            case 7:
                queue.queueOutput();
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 8);

        return 0;
    }