#include <iostream>
#include <algorithm> // để sử dụng hàm min
using namespace std;

int binarySearch(int arr[], int x, int left, int right) {
    while (left <= right) {
        int mid = (left + right) / 2;
        cout << "Kiem tra mid = " << mid << " voi gia tri arr[mid] = " << arr[mid] << endl;
        if (x == arr[mid]) return mid;
        if (x < arr[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int x) {
    if (arr[0] == x) return 0;

    int i = 1;
    while (i < n && arr[i] <= x) {
        cout << "i of index: " << i << endl;  // in chi so i truoc khi nhay
        i = i * 2;        
    }

    int right = min(i, n - 1);
    int left = i / 2;  // vi tri luc i chua nhay
    cout << "Target co the nam trong khoang index tu: " << left << " den " << right << endl;

    return binarySearch(arr, x, left, right);
}

int main() {
    // Mảng đã sắp xếp để thuật toán hoạt động chính xác
    int arr[6] = {1, 2, 3, 6, 7, 10};
    
    cout << "Nhap target muon tim index: ";
    int x;
    cin >> x;

    int result = exponentialSearch(arr, 6, x);
    if (result == -1)
        cout << "Khong co target trong mang!" << endl;
    else
        cout << "Target: " << x << " o vi tri: " << result + 1 << endl;

    return 0;
}
