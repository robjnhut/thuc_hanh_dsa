#include <cctype>
#include <iostream>
#include <string>
using namespace std;

    void toUpper(string& str) {
        for (char& c : str) {
            c = toupper(c); // Chuyển đổi từng ký tự thành chữ hoa
        }
    }

struct Song {
    string name;
    Song* prev;
    Song* next;
    
    Song(string name) : name(name), prev(nullptr), next(nullptr) {}
};

class musicPlayer {
    Song* head;
    Song* tail;
    Song* current;
    
public:
    musicPlayer() : head(nullptr), tail(nullptr), current(nullptr) {}
    

    // sử dụng hàm thêm bài hát
    void addSong(const string& songName) {  // dòng này để nhập và không thay đổi được bài hát với const 
        Song* newSong = new Song(songName);
        if (!head) {
            head = tail = current = newSong;  
            head->next = head;
            head->prev = head; // nồi thành một vòng tròn
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            newSong->next = head; // nối thành một vòng tròn
            head->prev = newSong;
            tail = newSong;
        }        
    }

    void playNext() {
        if (current) {
            current = current->next; // Nếu current không null, di chuyển đến bài tiếp theo
        } else {
            current = head; // Nếu current là null, khởi động lại từ đầu
        }
    }

    void playPrev() {
        if (current) {
            current = current->prev; // Nếu current không null, di chuyển đến bài trước
        } else {
            current = tail; // Nếu current là null, khởi động lại từ cuối
        }
    }


    void removeSong(const string& songName){
        if(!head) return;  // check xem trong list có bài hat nào không
        else{
            Song* temp = head; // gán temp = head
            do{
                if(temp -> name == songName){
                    if (temp == head && temp == tail) {
                        delete temp;
                        head = tail = current = nullptr;
                    }
                    //nếu song cần xóa là head
                    else if(temp == head){
                        head = head ->next;// phải chuyển head ra song kế
                        head ->prev = tail;// link nó với tail để tạo circle
                        tail ->next = head;// link tail với head để tạo circle
                    }
                    //nếu song cần xóa là tail
                    else if (temp == tail) { 
                        tail = tail -> prev; // phải chuyển tail lên trước nó
                        tail -> next = head; // link tail với head để tạo circle
                        head ->prev = tail;   // link head với tail để tạo circle
                    }
                    //truong hợp là song bất kì
                    else{
                        temp->prev->next=temp -> next; // trỏ song truoc nó link tới song sau nó
                        temp->next->prev = temp -> prev; // ngược lại cái trên
                    }
                    if(temp == current) current = current ->next;
                        delete temp;  //xóa song
                        return;  //kết thúc hàm
                }
                 temp = temp->next;  //tiếp tuc duyệt
            }while(temp != head );
           
        }
    }

    void disPlayPlayList(){
        if(!head){
            cout<<"List empty!";
            return;
        }else {
            Song *temp = head;
            do{
                cout<<temp ->name <<" ";
                temp = temp->next;
            } while (temp != tail ->next);
            cout<<endl;
        }
    }
};

int main(){
    int n;
    cout<<"nhap n: ";
    cin >>n;
    musicPlayer m;
    string luaChon;

        cout <<" nhap cac lua chon sau: "<<endl;
        cout <<" ADD de them song vao list"<<endl;
        cout <<" NEXT de chuyen qua bai tiep theo "<<endl;
        cout <<" NEXT de chuyen qua bai truoc "<<endl;
        cout <<" REMOVE de xoa song vao list"<<endl;
        cout <<" DISPLAY de hien danh sach song trong list"<<endl;
    cin.ignore();
    while(n--){
        getline(cin,luaChon);
        toUpper(luaChon);

        if(luaChon == "ADD"){
            string song;
            cout<<"nhap bai hat: "<<endl;
            getline(cin,song);
            m.addSong(song);
        }else if (luaChon == "NEXT") {
            m.playNext();
        }else if (luaChon == "PREV") {
            m.playPrev();
        }else if (luaChon == "REMOVE") {
            string songName;
            cout<<"nhap ten bai can xoa: ";
            getline(cin,songName);
            m.removeSong(songName);
        }else {
            cout<<"danh sach bai hat trong list: " <<endl;
            m.disPlayPlayList();
        }
    }

    return 0;
}
