#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <thread>

using namespace std;

// Function Prototypes
// Sort functions for different data types
void bubbleSort(vector<int>& arr, bool visualize = false);
void selectionSort(vector<int>& arr, bool visualize = false);
void insertionSort(vector<int>& arr, bool visualize = false);
void binaryInsertionSort(vector<int>& arr, bool visualize = false);
void quickSort(vector<int>& arr, int low, int high, bool visualize = false);
int partition(vector<int>& arr, int low, int high, bool visualize = false);
void mergeSort(vector<int>& arr, int l, int r, bool visualize = false);
void merge(vector<int>& arr, int l, int m, int r, bool visualize = false);
void heapSort(vector<int>& arr, bool visualize = false);
void heapify(vector<int>& arr, int n, int i, bool visualize = false);
int heapMaxValue(vector<int>& arr);

// Hybrid sorting algorithms
void hybridMergeSort(vector<int>& arr, int l, int r, bool visualize = false);
void hybridQuickSort(vector<int>& arr, int low, int high, bool visualize = false);

// Sorting linked list, queue, and stack
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};
void bubbleSortLinkedList(ListNode* head, bool visualize = false);

// Sorting multi-dimensional data (2D points)
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
void bubbleSortPoints(vector<Point>& points, bool visualize = false);
float calculateDistanceFromOrigin(const Point& p);

// Visualization Function
void visualizeArray(const vector<int>& arr);
void visualizePoints(const vector<Point>& points);

// Helper Functions
int binarySearchInsertionPosition(const vector<int>& arr, int item, int low, int high);
float calculateDistance(int x, int y);

int main() {
    int choice;
    vector<int> arr;
    bool visualize = false;
    int size;

    cout << "Sorting Visualization Tool" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Insertion Sort" << endl;
    cout << "4. Binary Insertion Sort" << endl;
    cout << "5. Quick Sort" << endl;
    cout << "6. Merge Sort" << endl;
    cout << "7. Heap Sort" << endl;
    cout << "8. Hybrid Merge Sort (Merge + Insertion)" << endl;
    cout << "9. Hybrid Quick Sort (Quick + Insertion)" << endl;
    cout << "10. Bubble Sort 2D Points" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 10) {
        // Sorting 2D points
        int numPoints;
        cout << "Enter the number of points: ";
        cin >> numPoints;
        vector<Point> points;
        for (int i = 0; i < numPoints; ++i) {
            int x = rand() % 100;
            int y = rand() % 100;
            points.emplace_back(x, y);
        }

        cout << "Do you want to visualize the sorting? (1 for Yes, 0 for No): ";
        cin >> visualize;

        auto start = chrono::high_resolution_clock::now();
        bubbleSortPoints(points, visualize);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        
        cout << "Sorted Points based on distance from origin: " << endl;
        visualizePoints(points);
        cout << "Sorting took " << duration.count() << " seconds." << endl;
    } else {
        cout << "Enter the size of the array: ";
        cin >> size;
        arr.resize(size);
        generate(arr.begin(), arr.end(), []() { return rand() % 100; });

        cout << "Do you want to visualize the sorting? (1 for Yes, 0 for No): ";
        cin >> visualize;

        auto start = chrono::high_resolution_clock::now();

        switch (choice) {
            case 1:
                bubbleSort(arr, visualize);
                break;
            case 2:
                selectionSort(arr, visualize);
                break;
            case 3:
                insertionSort(arr, visualize);
                break;
            case 4:
                binaryInsertionSort(arr, visualize);
                break;
            case 5:
                quickSort(arr, 0, arr.size() - 1, visualize);
                break;
            case 6:
                mergeSort(arr, 0, arr.size() - 1, visualize);
                break;
            case 7:
                heapSort(arr, visualize);
                break;
            case 8:
                hybridMergeSort(arr, 0, arr.size() - 1, visualize);
                break;
            case 9:
                hybridQuickSort(arr, 0, arr.size() - 1, visualize);
                break;
            default:
                cout << "Invalid choice" << endl;
                return 0;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        
        cout << "Sorted Array: ";
        visualizeArray(arr);
        cout << "Sorting took " << duration.count() << " seconds." << endl;
    }
    
    return 0;
}

// Bubble Sort for Points
void bubbleSortPoints(vector<Point>& points, bool visualize) {
    int n = points.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (calculateDistanceFromOrigin(points[j]) > calculateDistanceFromOrigin(points[j + 1])) {
                swap(points[j], points[j + 1]);
                if (visualize) {
                    visualizePoints(points);
                }
            }
        }
    }
}

// Calculate Distance from Origin
float calculateDistanceFromOrigin(const Point& p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Visualization Function for Points
void visualizePoints(const vector<Point>& points) {
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ") Distance: " << calculateDistanceFromOrigin(point) << endl;
    }
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(100));
}

// Bubble Sort
void bubbleSort(vector<int>& arr, bool visualize) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                if (visualize) {
                    visualizeArray(arr);
                }
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr, bool visualize) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
        if (visualize) {
            visualizeArray(arr);
        }
    }
}

// Standard Insertion Sort
void insertionSort(vector<int>& arr, bool visualize) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
        if (visualize) {
            visualizeArray(arr);
        }
    }
}

// Binary Insertion Sort
void binaryInsertionSort(vector<int>& arr, bool visualize) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int pos = binarySearchInsertionPosition(arr, key, 0, i - 1);
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
        if (visualize) {
            visualizeArray(arr);
        }
    }
}

int binarySearchInsertionPosition(const vector<int>& arr, int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == item) {
            return mid + 1;
        } else if (arr[mid] < item) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// Quick Sort
void quickSort(vector<int>& arr, int low, int high, bool visualize) {
    if (low < high) {
        int pi = partition(arr, low, high, visualize);
        quickSort(arr, low, pi - 1, visualize);
        quickSort(arr, pi + 1, high, visualize);
    }
}

int partition(vector<int>& arr, int low, int high, bool visualize) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
            if (visualize) {
                visualizeArray(arr);
            }
        }
    }
    swap(arr[i + 1], arr[high]);
    if (visualize) {
        visualizeArray(arr);
    }
    return i + 1;
}

// Merge Sort
void mergeSort(vector<int>& arr, int l, int r, bool visualize) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, visualize);
        mergeSort(arr, m + 1, r, visualize);
        merge(arr, l, m, r, visualize);
    }
}

void merge(vector<int>& arr, int l, int m, int r, bool visualize) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
        if (visualize) {
            visualizeArray(arr);
        }
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
        if (visualize) {
            visualizeArray(arr);
        }
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
        if (visualize) {
            visualizeArray(arr);
        }
    }
}

// Hybrid Merge Sort
void hybridMergeSort(vector<int>& arr, int l, int r, bool visualize) {
    if (r - l + 1 <= 10) {
        insertionSort(arr, visualize);
    } else if (l < r) {
        int m = l + (r - l) / 2;
        hybridMergeSort(arr, l, m, visualize);
        hybridMergeSort(arr, m + 1, r, visualize);
        merge(arr, l, m, r, visualize);
    }
}

// Hybrid Quick Sort
void hybridQuickSort(vector<int>& arr, int low, int high, bool visualize) {
    if (high - low + 1 <= 10) {
        insertionSort(arr, visualize);
    } else if (low < high) {
        int pi = partition(arr, low, high, visualize);
        hybridQuickSort(arr, low, pi - 1, visualize);
        hybridQuickSort(arr, pi + 1, high, visualize);
    }
}

// Heap Sort
void heapSort(vector<int>& arr, bool visualize) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, visualize);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, visualize);
    }
}

void heapify(vector<int>& arr, int n, int i, bool visualize) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        if (visualize) {
            visualizeArray(arr);
        }
        heapify(arr, n, largest, visualize);
    }
}

// Visualization Function
void visualizeArray(const vector<int>& arr) {
    for (int val : arr) {
        for (int i = 0; i < val; ++i) {
            cout << "=";
        }
        cout << "\n";
    }
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(100));
}