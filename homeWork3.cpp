#include<iostream>
#include <string>

using namespace std;
    struct Node{
        int exPireTime;
        string tokenId;
        Node *next;

        Node(string id,int time) : exPireTime(time), tokenId(id), next(nullptr) {}
    };

   

    class AuthenticationManager{
        private:
            int timeTolive;
            Node *head;
                // xóa token hết hạn
            void removeExpireTime(int currentTime){
                while(head != nullptr && head -> exPireTime < currentTime){ //expireTime là khoảng thời gian sống của token = time to live+currentTime
                                                                            //check nếu expireTime bé hơn current time thì coi như nó die ròi thì xóa đi
                    Node *temp = head;
                    head = head -> next;
                    delete temp;
                }
            }
        public:
        //constructor
            AuthenticationManager(int timeToLive) : timeTolive(timeToLive), head(nullptr) {}

        void generate(string tokenId, int currentTime){
            removeExpireTime(currentTime); // làm sạch list nếu chứa các token hết hạn
            // tạo token mới với token id và expireTime của nó
            Node *newNode = new Node(tokenId, currentTime + timeTolive); //tính expireTime = cách cộng currentTime với timeToLive
            if(head == nullptr) head = newNode;  //nếu list chưa có gì thì gán head = newToken
            else
            {
                Node *temp = head;
                while(temp -> next != nullptr){  // nếu trong list có sẵn rồi thì dịch temp đến cuối list
                    temp =temp->next ;
                }
                temp -> next= newNode;   // gán node tiếp của node cuối là newToken
            }
        }
            //reNew Token Id
        void renewToken(string tokenId, int currentTime){   
            removeExpireTime(currentTime);    // loại bỏ các token die
            Node *temp = head;

            while(temp){
                if(temp -> tokenId == tokenId && temp ->exPireTime > currentTime){   // gán token đầu tiên gặp nếu còn time thì reNew nó
                    temp -> exPireTime = timeTolive + currentTime;      // gia hạn lại expireTime cho cái vừa renew
                    return;
                }
                temp = temp->next;  // chuyển sang token tiép 
            }
        }
        // đếm các token còn sống
        int countUnexpiredTokens (int currentTime){
            removeExpireTime(currentTime);  // vẫn là remove cái die trong list
            Node *temp = head;
            int count = 0;    // tạo count ban đầu
            while(temp){
                if(temp -> exPireTime > currentTime) count++;   // check qua xem cái nào còn sống thì cộng lên
                temp = temp ->next;
            }
                return count;   // trả về số lượng token còn sống tại current time
        }

    };


int main(){
    int time;
    cout<<"enter thoi gian live cho token: " << endl;
    cin >> time;
    AuthenticationManager auth(time);
    cout<<"null"<<endl;

    cout<<"Enter generate de tao new token." << endl;
    cout<<"Enter renew de tao renew token." << endl;
    cout<<"Enter counttoken de dem token con song." << endl;
    cout<<"Enter exit de thoat khoi loop!" << endl;
    cout<<"Nhap sai ki tu, vui long nhap lai!" << endl;
    string enter;
    cin.ignore();
    while(true){
        cout<<"nhap lenh: " ;
        getline(cin,enter);    
        
        if(enter == "generate"){
            string tokenId;
            cout<<"nhap tokenId: " << endl;
            cin.ignore();
            getline(cin,tokenId);
            int currentTime;
            cout<<"nhap currentTime: " << endl;
            cin>> currentTime;
            cin.ignore();

            auth.generate(tokenId,currentTime);
            cout<<"null" << endl;
        }
        else if(enter == "renew"){
            string tokenId;
            cout<<"nhap tokenId: " << endl; 
            getline(cin,tokenId);
            
            int currentTime;
            cout<<"nhap currentTime: " << endl;
            cin>> currentTime;
            cin.ignore();
            auth.renewToken(tokenId,currentTime);
            cout<<"null"<<endl;
        }
        else if(enter == "counttoken"){
           int currentTime;
           cout<<"Nhap currentTime: " ;
           cin>> currentTime;
           cin.ignore();
            int count = auth.countUnexpiredTokens(currentTime);
            cout<<"so token con song la: "<<count <<endl;
        }else if (enter == "exit") break;
        else cout<<"vui long nhap lai!" << endl;
    }

    return 0;
}