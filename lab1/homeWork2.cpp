#include<iostream>
#include<string>
using namespace std;
    class Node{
       public: 
        string url;
        Node *prev;
        Node *next;

        Node(string url) : url(url), prev(nullptr), next(nullptr) {}
    };

    class browserHistory{
        private:
            Node *head;
            Node *current;
            Node *tail;
        
        public:
            browserHistory(string homePage){    // khởi tạo homepage
                head = new Node(homePage);
                current = head;
                tail = head;
            }

            void visit(string newUrl){
                Node *newNode = new Node(newUrl);  // khởi tạo cho url mới
                current ->next = newNode;// hai dòng kế để tao double linklist
                newNode -> prev = current;
                current = newNode;   // cho url mới thành current
            }
                //tao function back
            string back(int number){
                if(current == head){
                    cout<< head ->url; // neu function dang ở vị trí browser thì in ra luôn
                }else{
                    while(current -> prev != nullptr && number > 0){ // điều kiện buoc nhay lớn hon 0 và trỏ tới browser thì in ra luon
                        current = current -> prev;       //chạy cho đến trước nó
                        number--;
                    }
                    return current -> url;    //trả về giá trị dang ở
                }
            }

            string forward(int number){
                if(current == tail){// neu function dang ở vị trí đuôi thì in ra luôn
                    cout<< tail ->url;
                }else{
                    while(current ->next != nullptr && number > 0){// điều kiện buoc nhay lớn hon 0 và trỏ tới cái đuôi hien tại thì in ra luon
                        current = current -> next;
                        number--;
                    }
                    return current -> url;
                }
            }

    };


int main(){
    string homePage;
    cout<<"nhap trang chu: " <<endl;
    getline(cin,homePage);

    browserHistory browser(homePage);

    string nhapLenh;
    while(1){
        cout<<"nhap cac lenh sau: visit, back, forward, exit."<<endl;;
        cin>>nhapLenh;
        
        if(nhapLenh == "visit"){
            string url;
            cout<<"nhap url: " << endl;
            cin.ignore();// bỏ qua dấu cách
            getline(cin,url); //lấy cả chuỗi
            browser.visit(url);  // gọi hàm browser
            cout<< "null"<<endl;
        }else if (nhapLenh == "back") {
            int number;
            cout<<"nhap so lan back: "<<endl;
            cin>> number;
            cout<<"dang o trang:"<<endl;
            cin.ignore();
            cout << browser.back(number)<<endl;
        }else if (nhapLenh == "forward") {
            int number;
            cout<<"nhap so lan forward: "<<endl;
            cin>> number;
            cout<<"dang o trang:"<<endl;
            cin.ignore();
            cout << browser.forward(number)<<endl;
        }else if (nhapLenh == "exit") {
            break; // Thoát khỏi vòng lặp
        } else {
            cout << "lenh khong hop le!" << endl;
        }

    }

    return 0;
}