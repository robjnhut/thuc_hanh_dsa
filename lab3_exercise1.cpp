#include <iostream>
#include<vector>

using namespace std;

    int findFirst(const vector<int>&arr, int target){
        int left = 0, right = arr.size() -1 , firstOccurr = -1;

        while(left <= right){
            int mid = left + (right - left) / 2;
            if(arr[mid] == target){
                firstOccurr = mid;    // tìm lần đầu tiên nó xuất hiện tại vị trí nào
                right = mid -1; 
            }
            else if(arr[mid] < target){
                left = mid + 1; 
            }
            else{
                right = mid -1;
            }
        }
        return firstOccurr;
    }

    int findLast(const vector<int>&arr, int target){
        int left = 0, right = arr.size() -1 , lastOccur = -1;

        while(left <= right){
            int mid = left + (right - left) / 2;
            if(arr[mid] == target){
                lastOccur = mid;    // tìm lần cuối cùng nó xuất hiện tại vị trí nào
                left = mid + 1; 
            }
            else if(arr[mid] < target){
                left = mid + 1; 
            }
            else{
                right = mid -1;
            }
        }
        return lastOccur;
    }

   int countOccurrences(const vector<int>& arr, int target) {
    int firstOccurrence = findFirst(arr, target);
    if (firstOccurrence == -1) {
        return 0;  // Không tìm thấy target
    }
    int lastOccurrence = findLast(arr, target);
    return lastOccurrence - firstOccurrence + 1;
}


int main(){


    return 0;
}