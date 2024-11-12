#include <iostream>
#include <string>
#include <cctype>
#include <sstream>  // Thư viện để xử lý chuỗi
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    bool isEmpty() {
        return topNode == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        int value = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    int top() {
        if (!isEmpty()) {
            return topNode->data;
        }
        return 0;  // Trả về 0 nếu stack rỗng
    }
};

// Kiểm tra ký tự có phải là toán hạng không (chữ cái hoặc số)
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Hàm trả về độ ưu tiên của toán tử
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// Hàm chuyển đổi từ infix sang postfix
string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";
    int length = infix.length();

    for (int i = 0; i < length; i++) {
        char c = infix[i];

        // Nếu là toán hạng (chữ hoặc số), thêm vào kết quả
        if (isOperand(c)) {
            // Nếu là số, kiểm tra xem số đó có nhiều hơn một chữ số hay không
            while (i < length && isOperand(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += " "; // Thêm khoảng trắng sau mỗi toán hạng để phân biệt các số nhiều chữ số
            i--; // Điều chỉnh lại chỉ số vì vòng lặp ngoài sẽ tăng thêm 1
        }
        // Nếu là dấu ngoặc mở, đẩy vào stack
        else if (c == '(') {
            s.push(c);
        }
        // Nếu là dấu ngoặc đóng, pop từ stack cho đến khi gặp dấu ngoặc mở
        else if (c == ')') {
            while (!s.isEmpty() && s.top() != '(') {
                postfix += s.top();
                postfix += " ";  // Thêm khoảng trắng giữa các toán tử
                s.pop();
            }
            s.pop();  // Bỏ dấu ngoặc mở '('
        }
        // Nếu là toán tử
        else {
            while (!s.isEmpty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                postfix += " ";  // Thêm khoảng trắng giữa các toán tử
                s.pop();
            }
            s.push(c);
        }
    }

    // Pop tất cả các toán tử còn lại trong stack
    while (!s.isEmpty()) {
        postfix += s.top();
        postfix += " ";  // Thêm khoảng trắng giữa các toán tử
        s.pop();
    }

    return postfix;
}

// Hàm tính toán
int evaluatePostfix(const string& postfix) {
    Stack s;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {  // Duyệt qua từng phần tử trong chuỗi hậu tố
        if (isdigit(token[0])) {  // Nếu phần tử là số
            s.push(stoi(token));  // Chuyển đổi chuỗi sang số nguyên
        } else {  // Nếu phần tử là toán tử
            int operand2 = s.pop();  // Lấy toán hạng thứ hai
            int operand1 = s.pop();  // Lấy toán hạng thứ nhất

            switch (token[0]) {
                case '+':
                    s.push(operand1 + operand2);
                    break;
                case '-':
                    s.push(operand1 - operand2);
                    break;
                case '*':
                    s.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        throw runtime_error("Division by zero!");
                    }
                    s.push(operand1 / operand2);
                    break;
            }
        }
    }

    return s.pop();  // Kết quả cuối cùng
}

int main() {
    string infix;
    cout << "Nhap bieu thuc infix: ";
    getline(cin, infix);  // Sử dụng getline để nhập nhiều ký tự

    string postfix = infixToPostfix(infix);
    cout << "Bieu thuc postfix: " << postfix << endl;

    // Tính toán kết quả
    try {
        int result = evaluatePostfix(postfix);
        cout << "Ket qua: " << result << endl;  // In kết quả
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
