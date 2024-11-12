#include <iostream>
#include <vector>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            // In mảng sau khi hoán đổi
            cout << "Hoan doi trong partition: ";
            for (int k = low; k <= high; k++) cout << arr[k] << " ";
            cout << " (i=" << i << ", j=" << j << ")" << endl;
        }
    }
    swap(arr[i + 1], arr[high]);
    cout << "Hoan doi pivot: ";
    for (int k = low; k <= high; k++) cout << arr[k] << " ";
    cout << " (pivot o vi tri " << (i + 1) << ")" << endl;

    return i + 1;
}

void QuickSort1(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        cout << "Mang sau partition voi pivot tai " << pi << ": ";
        for (int k = low; k <= high; k++) cout << arr[k] << " ";
        cout << endl;

        QuickSort1(arr, low, pi - 1);
        QuickSort1(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr);

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pivot = arr[low]; // chọn phần tử đầu làm pivot
    vector<int> left, right; // tạo hai mảng phụ

    cout << "\nPivot = " << pivot << " (Index: " << low << "), low = " << low << ", high = " << high << endl;

    // Chia mảng thành hai mảng con
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] < pivot) {
            left.push_back(arr[i]); // phần tử nhỏ hơn pivot
        } else {
            right.push_back(arr[i]); // phần tử lớn hơn hoặc bằng pivot
        }
    }

    // Đưa mảng đã sắp xếp vào mảng ban đầu
    int k = low;
    for (int val : left) {
        arr[k++] = val;
    }

    int pivotIndex = k;
    arr[pivotIndex] = pivot; // Đặt pivot vào vị trí giữa

    for (int val : right) {
        arr[++k] = val;
    }

    // In trạng thái của mảng và các chỉ số sau mỗi lần phân đoạn
    cout << "Mang sau khi phan doan voi pivot tai vi tri " << pivotIndex << ": ";
    for (int idx = 0; idx < arr.size(); idx++) {
        cout << arr[idx] << (idx == pivotIndex ? "(P) " : " ");
    }
    cout << endl;

    // Đệ quy sắp xếp từng phần
    quickSortHelper(arr, low, pivotIndex - 1); // Sắp xếp phần bên trái
    quickSortHelper(arr, pivotIndex + 1, high); // Sắp xếp phần bên phải
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    cout << "Mang tam L: ";
    for (int i = 0; i < n1; i++) cout << L[i] << " ";
    cout << endl;

    cout << "Mang tam R: ";
    for (int j = 0; j < n2; j++) cout << R[j] << " ";
    cout << endl;

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    cout << "Mang sau khi hop nhat: ";
    for (int x = left; x <= right; x++) cout << arr[x] << " ";
    cout << endl;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int arr1[] = {3, 6, 3, 10, 1, 2, 1};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Sap xep bang QuickSort1:" << endl;
    QuickSort1(arr1, 0, n - 1);
    
    cout << "Sap xep bang QuickSort2:" << endl;

    vector<int> arr = {3, 6, 3, 10, 1, 2, 1};
    cout << "Mang truoc khi sap xep: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    quickSort(arr);

    cout << "\nMang sau khi sap xep: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;


    int arr3[] = {3, 6, 3, 10, 1, 2, 1};
    cout << "\nSap xep bang mergeSort:" << endl;
    mergeSort(arr3, 0, n - 1);

    return 0;
}
