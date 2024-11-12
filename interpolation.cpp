#include <iostream>
using namespace std;

int Interpolation(int arr[], int n, int x) {
    int lowEnd = 0;
    int highEnd = n - 1;
    int i = 1;

    cout << "lowEnd: " << lowEnd << endl;
    cout << "highEnd: " << highEnd << endl;

    while (lowEnd <= highEnd && x >= arr[lowEnd] && x <= arr[highEnd]) {
        if (lowEnd == highEnd) {
            if (arr[lowEnd] == x) return lowEnd;
            return -1;
        }

        int probe = lowEnd + ((highEnd - lowEnd) * (x - arr[lowEnd])) / (arr[highEnd] - arr[lowEnd]);
        cout << "probe " << i << " : " << probe << endl;

        if (arr[probe] == x) return probe;
        else if (x < arr[probe]) {
            highEnd = probe - 1;
            cout << "highEnd " << i << " : " << highEnd << endl;
        } else {
            lowEnd = probe + 1;
            cout << "lowEnd " << i << " : " << lowEnd << endl;
        }
        i++;
    }
    return -1;
}

int main() {
    // Mảng đã được sắp xếp
    int arr[6] = {1, 2, 5, 6, 7, 9};

    cout << "Nhap target muon tim index: ";
    int x;
    cin >> x;

    int result = Interpolation(arr, 6, x);
    if (result == -1)
        cout << "Khong co target trong mang!" << endl;
    else
        cout << x << " o vi tri: " << result << endl;

    return 0;
}
