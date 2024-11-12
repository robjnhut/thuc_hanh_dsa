#include <iostream>
#include<vector>
#include<unordered_map>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed rand()
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* random;

    Node(int value) : data(value), next(nullptr), random(nullptr) {}
};

void insert(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void print(Node* head){
        if(head == nullptr) return;
        else{
            Node* temp = head;
            cout<<"linkList: "<< endl ;
            while(temp != nullptr){
                cout << temp-> data <<" ";
                temp = temp->next;
            }
            cout << endl;
        }
    }


void addTwoNum(Node*& head, Node*& tail, int n1, int n2) {
    insert(head, tail, n1);
    insert(head, tail, n2);
}

Node* copyRandomList(Node* head) {
    if (head == nullptr) return nullptr;

    Node* copyHead = nullptr;
    Node* copyTail = nullptr;
    Node* current = head;

    while (current != nullptr) {
        insert(copyHead, copyTail, current->data);
        current = current->next;
    }

    current = head;
    Node* copyCurrent = copyHead;

    while (current != nullptr) {
        Node* randomNode = current->random;
        if (randomNode != nullptr) {
            Node* temp = head;
            Node* copyTemp = copyHead;
            while (temp != nullptr) {
                if (temp == randomNode) {
                    copyCurrent->random = copyTemp;
                    break;
                }
                temp = temp->next;
                copyTemp = copyTemp->next;
            }
        }
        current = current->next;
        copyCurrent = copyCurrent->next;
    }

    return copyHead;
}
    void printRandom(Node* head) {
        if (head == nullptr) return;
        Node* temp = head;
        cout << "LinkList: " << endl;
        while (temp != nullptr) {
            cout << "Data: " << temp->data;
            if (temp->random)
                cout << ", Random points to: " << temp->random->data;
            else
                cout << ", Random points to: nullptr";
            cout << endl;
            temp = temp->next;
        }
    }

    void swapNode(Node*& head, int n1, int n2) {
    if (head == nullptr || n1 == n2) return; // Nếu danh sách rỗng hoặc không cần hoán đổi

    Node* prev1 = nullptr, *curr1 = head;
    for (int i = 1; i < n1 && curr1 != nullptr; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    Node* prev2 = nullptr, *curr2 = head;
    for (int j = 1; j < n2 && curr2 != nullptr; j++) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    // Nếu một trong hai node không tồn tại
    if (curr1 == nullptr || curr2 == nullptr) return;

    // Nếu curr1 là node đầu
    if (prev1 == nullptr) {
        head = curr2; // Đặt curr2 làm đầu mới
    } else {
        prev1->next = curr2;
    }

    // Nếu curr2 là node đầu
    if (prev2 == nullptr) {
        head = curr1; // Đặt curr1 làm đầu mới
    } else {
        prev2->next = curr1;
    }

    // Hoán đổi next
    Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
}

Node* removeNthFromEnd(Node* head, int N) {
    // Tạo node giả (dummy node) để tránh lỗi khi xóa node đầu
    Node* dummy = new Node(0);
    dummy->next = head;

    Node* fast = dummy;
    Node* slow = dummy;

    // Di chuyển con trỏ fast trước N bước
    for (int i = 1; i <= N + 1; i++) {
        fast = fast->next;
    }

    // Di chuyển cả fast và slow đồng thời cho đến khi fast tới cuối
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    // Xóa node thứ N từ cuối
    Node* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;

    // Trả về head mới
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

void separateOddAndEven(Node*& head) {
    if (head == nullptr) return; // Nếu danh sách trống thì không làm gì

    Node *oddHead = nullptr, *oddTail = nullptr;
    Node *evenHead = nullptr, *evenTail = nullptr;
    Node* current = head;

    while (current != nullptr) {
        if (current->data % 2 == 0) {  // Node chẵn
            if (evenHead == nullptr) {
                evenHead = evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {  // Node lẻ
            if (oddHead == nullptr) {
                oddHead = oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }
        current = current->next;
    }

    // Nối danh sách lẻ vào cuối danh sách chẵn
    if (evenHead == nullptr) {
        head = oddHead; // check xem co list even khong
    } else {
        evenTail->next = oddHead;  // noi le vao chan
        head = evenHead;           // 
    }

    // noi duoi le vao null
    if (oddTail != nullptr) {
        oddTail->next = nullptr;
    }
}

 vector<Node*> divideListIntoParts(Node* head, int k) {
    vector<Node*> result(k, nullptr);  // Mảng kết quả với k phần
    int totalNodes = 0;
    Node* current = head;

    // Đếm tổng số node trong danh sách
    while (current != nullptr) {
        totalNodes++;
        current = current->next;
    }

    int baseSize = totalNodes / k;  // Kích thước cơ bản của mỗi phần
    int extraNodes = totalNodes % k; // Số phần cần thêm 1 node để cân bằng

    current = head;
    Node* prev = nullptr;

    // Chia danh sách thành k phần
    for (int i = 0; i < k; i++) {
        result[i] = current;
        int partSize = baseSize + (extraNodes > 0 ? 1 : 0); // Tính kích thước của phần hiện tại
        extraNodes--;

        // Duyệt qua danh sách và ngắt sau khi đạt đến kích thước của phần
        for (int j = 0; j < partSize; j++) {
            prev = current;
            current = current->next;
        }

        // Ngắt phần hiện tại khỏi phần tiếp theo
        if (prev != nullptr) {
            prev->next = nullptr;
        }
    }

    return result;
}


void menu() {
    cout << "Menu: " << endl;
    cout << "1. Add Two Numbers to Linked List" << endl;
    cout << "2. Copy Linked List with Random Pointers" << endl;
    cout << "3. Swap Linked List" << endl;
    cout <<"4.  Remove the N-th Node from the End of a List" <<endl;
    cout <<"5. Separate Odd and Even Nodes in a Linked List" <<endl;
    cout <<"6. Divide a Linked List into Parts" <<endl;
    cout <<"7. Remove Zero-Sum Consecutive Nodes from a Linked List" <<endl;
    cout <<"8. Insert at the end of the list" <<endl;
    
    cout << "0. Exit" << endl;
}

Node* removeZeroSumSublists(Node* head) {
    Node* dummy = new Node(0);  // Tạo node giả ở đầu danh sách để dễ xử lý
    dummy->next = head;
    unordered_map<int, Node*> prefixMap;  // Hash map lưu tổng dồn và node tương ứng

    Node* current = dummy;
    int prefixSum = 0;

    // Bước 1: Duyệt qua danh sách và lưu tổng dồn vào hash map
    while (current != nullptr) {
        prefixSum += current->data;

        if (prefixMap.find(prefixSum) != prefixMap.end()) {
            // Nếu tổng dồn đã tồn tại, tức là các node giữa đã tạo thành tổng bằng 0
            Node* node = prefixMap[prefixSum]->next;
            int tempSum = prefixSum;
            while (node != current) {
                tempSum += node->data;
                prefixMap.erase(tempSum);  
                node = node->next;
            }
            // bo qua node co tong =0
            prefixMap[prefixSum]->next = current->next;
        } else {
            prefixMap[prefixSum] = current;
        }
        current = current->next;
    }

    return dummy->next;
}

void autoInputList(Node*& head, Node*& tail) {
    // Generate a random number of entries between 39 and 59
    int numEntries = rand() % 21 + 39;  // 39 + (0 to 20)

    // Insert random values between -99 and 99 into the list
    for (int i = 0; i < numEntries; i++) {
        int randomValue = rand() % 199 - 99;  // -99 + (0 to 198)
        insert(head, tail, randomValue);
    }
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int n;
    cout<<"Nhap vao linkList: "<< endl;
    while(1){
        cin >>n;
        if(n == -101) break;
        insert(head,tail,n);
    }
    print(head);
    int choice;

    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n1, n2;
                cout << "Enter two numbers to add: ";
                cin >> n1 >> n2;
                addTwoNum(head, tail, n1, n2);
                print(head);
                break;
            }
            case 2: {
                // Thiết lập con trỏ random cho danh sách gốc
                if (head) head->random = head->next ? head->next->next : nullptr; // Node 1 -> Node 3
                if (head && head->next) head->next->random = head; // Node 2 -> Node 1
                if (tail) tail->random = tail; // Node cuối -> tự trỏ tới chính nó

                // Sao chép danh sách có con trỏ random
                Node* copiedList = copyRandomList(head);
                cout << "\nCopied list: " << endl;
                printRandom(copiedList);
                break;
            }
            case 3: {
                int n1, n2;
                cout<< "nhap 2 vi tri can hoan doi: "<< endl<<"vi tri thu nhat: ";
                cin >> n1;
                cout<<endl << "vi tri thu hai: ";
                cin >> n2;
                swapNode( head,n1,n2);
                print(head);
                break;
            }
            case 4: {
                int N;
                cout<<"nhap Nth can xoa tu cuoi: ";
                cin >>N;
                head = removeNthFromEnd(head,N);
                print(head);
                break;
            }
            case 5: {
                separateOddAndEven(head);
                cout <<"Sau khi tach: " <<endl;
                print(head);
                break;
            }
            case 6: {
                int k;
                cout<<"nhap so Parts: " << endl;
                cin>>k;
                vector<Node*> parts = divideListIntoParts(head, k);
                cout << "Danh sach da chia thanh cac phan: " << endl;
                for (int i = 0; i < parts.size(); i++) {
                cout << "Phan " << i+1 << ": ";
                print(parts[i]);
                }
                break;
            }
            case 7: {
                head = removeZeroSumSublists(head);
                cout << "Danh sach sau khi xoa: ";
                print(head);
                break;
            }
            case 8: {
                srand(time(0));
                // Automatically input values into the list
                autoInputList(head, tail);
                // Print the resulting linked list
                print(head);
                break;
            }
            case 0:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}