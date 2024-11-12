#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* pNext;

    Node(int value) : data(value), pNext(nullptr) {}
};

// Function prototypes for linked list operations
void findMiddleNode(Node* head);
bool detectCycle(Node* head);
Node* combineTwoSortedLists(Node* list1, Node* list2);
Node* findIntersection(Node* head1, Node* head2);
Node* reverseList(Node* head);
Node* eliminateDuplicates(Node* head);
bool isPalindrome(Node* head);
void searchValue(Node* head, int x);

//==================================================================================================================================================            
void insertLinkList(int value, Node*& head) {

    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp-> pNext != nullptr) {
            temp = temp-> pNext;
        }
        temp->pNext = newNode;
    }
}
//==================================================================================================================================================            
void printList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->pNext;
    }
    cout << endl;
}
//==================================================================================================================================================            
void findMiddleNode(Node *head, int &n){
        if(head == nullptr || n  < 1) return ; //check whether there are anything in linklist
        Node *temp = head;
        // check 2 case ood and even Node
            if(n%2 != 0){ // odd
            for(int i = 0; i < n/2; i++ ){
                temp = temp -> pNext;
            }
            cout << "Middle node: " << temp -> data;
        }
            else{ //even
                for(int i = 0; i< (n/2 - 1); i++){
                    temp = temp -> pNext;
                }
               cout<< "Middle node: " ; 
                cout << temp -> data << " and " << temp->pNext->data<<endl;        
            }
        }
//==================================================================================================================================================            
    bool  detectCycle(Node *head){
        if(head == nullptr || head -> pNext == nullptr) return false;
        Node *step1 = head; //create step1 to jump 1 Node in one time
        Node *step2 = head; //create step2 to jump 2 Node in one time
        while(step2 != nullptr && step2 -> pNext != nullptr){
            step1 = step1 ->pNext;
            step2 = step2 -> pNext -> pNext;

            if(step1 == step2) return true;
        }

        return false;

    }
//==================================================================================================================================================            
    Node *combineTwoSortedLists(Node* list1, Node* list2){
       if(list1 == nullptr) return list2;
       if(list2 == nullptr) return list1;

        Node *newNode = new Node(0);
        Node *tail=newNode;

        while(list1 != nullptr && list2 != nullptr){
            if (list1->data <= list2->data) {
            tail->pNext= list1;
            list1 = list1->pNext;
        } else {
            tail->pNext = list2;
            list2 = list2->pNext;
        }

        tail = tail -> pNext;
        }

        if (list1 != nullptr) {
        tail->pNext = list1;
    } else {
        tail->pNext = list2;
    }
    Node* list3 = newNode->pNext;
    delete newNode; // Delete the dummy node to avoid memory leak
    return list3;
    
    }
//==================================================================================================================================================            
    Node* findIntersection(Node* list1, Node* list2){
        // check xem 1 trong 2 có null khong nếu null thì out luon
        if(list1 == nullptr || list2 == nullptr){
         cout <<"not intersecttion between 2 list!";
        return nullptr;
        }
        //tao ra temp 1 và 2
       Node *temp1 = list1;
        Node *temp2 = list2;

        //tao ra head moi ten tamthoi chưa gia tri 0
        Node *tamthoi = new Node(0);
        Node *list3 = tamthoi;  // list3 nhu la temp

    while(temp2 != nullptr){    // xet  tung phan tu cua list 1 voi list 2
        while(temp1 != nullptr ){
            if(temp1 ->data == temp2 -> data){
                Node *newNode = new Node(temp2->data); // input data intersec vao list3
                list3->pNext = newNode; 
                list3 = list3 -> pNext; // dich foward
            }
            temp1 = temp1 -> pNext;
        }
            temp1 = list1; // gan lai tu dau 
            temp2 = temp2 -> pNext;
    }

    Node *intersectionList = tamthoi ->pNext;
    delete tamthoi;

    return intersectionList;

}
//==================================================================================================================================================            
    Node* reverseList(Node* head){
        if(head == nullptr) return nullptr; // check neu list khong co gi thi out luon
        
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;

        while (current != nullptr) {
        next = current->pNext;   // Lưu node next
        current->pNext = prev;   // Đảo chiều liên kết
        prev = current;          // Di chuyển prev lên current
        current = next;          // Di chuyển current lên node tiếp theo
    }

    return prev; 

}
//==================================================================================================================================================            
    Node* eliminateDuplicates(Node* head){
        if(head == nullptr) return nullptr; // check xem linklist có rỗng không

        Node *holdd = new Node(0);  //tạo 1 node mới chứa list tang dần ko có duplicate
        Node *newList = holdd;
        Node *temp = head;
        
        while(temp != nullptr){
            if(temp->pNext == nullptr || temp-> data != temp->pNext->data){  // check nếu số đó không dup thì nhét vào node mới
                Node *newNode = new Node(temp -> data);
                newList -> pNext = newNode;
                newList = newList -> pNext;
            }
            
                temp = temp->pNext;
        }

        Node *eliminateNode = holdd -> pNext;  // delete Node
        delete holdd;
        return eliminateNode;       // return Node mới 
    }
//==================================================================================================================================================            
bool isPalindrome(Node* head){
    Node *temp = head;
    head = reverseList(head); // use reverse to check palindrome
    Node *curr = head;

    while(temp != nullptr && curr != nullptr){
        if(temp ->data == curr -> data){  // if first node and reverse node equal then cotinue loop
            temp = temp -> pNext;
            curr = curr -> pNext;
        }
        else return false;  // return false
    }
    return true;

}
//==================================================================================================================================================            
void searchValue(Node* head, int x){
    Node *temp = head;
    bool found = false;
    while(temp != nullptr){
        if(temp -> data == x){
            cout<<"the address of value " <<x <<" is: " <<endl << &temp << endl;
            found = true;
            break;
        }
            temp = temp -> pNext;
    }
        if(!found){
            cout << "The value "<< x << " not found! ";
            cout << endl << " NULL";
        }
}

int main() {
    Node* head = nullptr; // Initialize the linked list head
    int choice, value;


    do {
        cout << "\nMenu:\n";
        cout << "1. Find the Middle Node of a Linked List\n";
        cout << "2. Detect a Cycle in a Linked List\n";
        cout << "3. Combine Two Sorted Linked Lists\n";
        cout << "4. Find the Intersection of Two Linked Lists\n";
        cout << "5. Reverse a Linked List\n";
        cout << "6. Eliminate Duplicates from a Sorted Linked List\n";
        cout << "7. Check if a Linked List is a Palindrome\n";
        cout << "8. Search for a value in the Linked List\n";
        cout << "9. Insert a value into the Linked List\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:{
        Node* head = nullptr;
    int count = 0;
    int i;

   while(true){
        cin>> i;
        if(i == -1) break; // if the user input -1 will stop
        count++;
        insertLinkList(i,head);
    }
    cout << "the linklist: ";
    printList(head);
    cout <<endl;
    findMiddleNode(head, count);
    break;
        }
//==================================================================================================================================================            
        case 2:{
            Node* head = nullptr;
            int i;

        while(true){
                cin>> i;
                if(i == -1) break; // if the user input -1 will stop
   
                insertLinkList(i,head);
            }
            cout << "the linklist: ";
            printList(head);
            cout <<endl;

        // tạo cycle để test thử  
            if (head != nullptr && head->pNext != nullptr) {
                Node* temp = head;
                while (temp->pNext != nullptr) {
                    temp = temp->pNext;
                }
                temp->pNext = head->pNext; // trỏ node cuoooi tới node thứ 2
            }

            // Detecting if the linked list has a cycle
            
            if (detectCycle(head)) {
                cout << "Cycle detected in the list." << endl;
            } else {
                cout << "No cycle detected." << endl;
            }
            break;
        }
//==================================================================================================================================================            
        case 3: {
            Node* list1 = nullptr;
            Node* list2 = nullptr;
            int i;

        while(true){
                cin>> i;
                if(i == -1) break; // if the user input -1 will stop
   
                insertLinkList(i,list1);
            }
         while(true){
                cin>> i;
                if(i == -1) break; // if the user input -1 will stop
   
                insertLinkList(i,list2);
            }
            cout << "list1 is: ";
            printList(list1);
            cout << endl;
            cout << "list2 is: ";
            printList(list2);
            cout <<endl;
            // Assuming the user provides another list (list2), you can combine them.
            Node* combinedList = combineTwoSortedLists(list1, list2);
            printList(combinedList);
            break;
        }
//==================================================================================================================================================            
        case 4: {
            Node* list1 = nullptr;
            Node* list2 = nullptr;
            int i;

        while(true){
                cin>> i;
                if(i == -1) break; // if the user input -1 will stop
   
                insertLinkList(i,list1);
            }
         while(true){
                cin>> i;
                if(i == -1) break; // if the user input -1 will stop
   
                insertLinkList(i,list2);
            }
            cout << "list1 is: ";
            printList(list1);
            cout << endl;
            cout << "list2 is: ";
            printList(list2);
            cout <<endl;
            // Assuming we have two lists, find the intersection.
            Node* intersection = findIntersection(list1, list2);
            if (intersection != nullptr) {
                cout << "Intersection node found with value: " << intersection->data << endl;
            } else {
                cout << "No intersection found." << endl;
            }
            break;
        }
//==================================================================================================================================================            
        case 5:{
        Node *head = nullptr;
        int i;
        while(true){
            cin >> i;
            if(i == -1) break;
            insertLinkList(i,head);
        }     
            cout <<"The linklist is: " ;
            printList(head);

            head = reverseList(head);
            cout << "Reversed Linked List: ";
            printList(head);
            break;
        }
//==================================================================================================================================================            
        case 6:{
        Node *head = nullptr;
        int i;

        while(true){
            cin >> i;
            if(i == -1) break;
            insertLinkList(i,head);
            }     
            cout <<"The linklist is: " ;
            printList(head);
        
            head = eliminateDuplicates(head);
            cout << "Duplicates eliminated: ";
            printList(head);
            break;
        }
//==================================================================================================================================================            
        case 7:{
            Node *head = nullptr;
        int i;
        while(true){
            cin >> i;
            if(i == -1) break;
            insertLinkList(i,head);
        }     
            cout <<"The linklist is: " ;
            printList(head);

            if (isPalindrome(head)) {
                cout << "The list is a palindrome." << endl;
            } else {
                cout << "The list is not a palindrome." << endl;
            }
            break;
        }
//==================================================================================================================================================            
        case 8:{
            Node *head = nullptr;
            int i;
            while(true){
            cin >> i;
            if(i == -1) break;
            insertLinkList(i,head);
        }     
            cout <<"The linklist is: " ;
            printList(head);
            int value;
            cout << "Enter value to search: ";
            cin >> value;
            searchValue(head, value);
            break;
        }
//==================================================================================================================================================            
        case 9:{
            cout << "Enter value to insert: ";
            cin >> value;
            insertLinkList(value, head);
            printList(head);
            break;
        }
//==================================================================================================================================================            
        case 0:{
            cout << "Exiting program..." << endl;
            break;
        }
//==================================================================================================================================================            
        
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    } while (choice != 0);
    
    return 0;
}

// Implement the required linked list functions (findMiddleNode, detectCycle, etc.)
// You need to add the code for these functions based on your requirement
