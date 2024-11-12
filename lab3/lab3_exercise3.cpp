#include <iostream>
#include<vector>
#include<string>
using namespace std;

int interpolation(const vector<string> &arr,const string& target ){
    int left = 0;
    int right = arr.size()-1;

    while(left <= right && target[0] >= arr[left][0] && target[0] <= arr[right][0]){
        if(left == right){
            return arr[left] == target ? left : -1;
        }

        int probe = left + (static_cast<int>((left - right) *(target[0] - arr[left][0]) / (arr[right][0] - arr[left][0])));
        if(arr[probe] == target){
            return probe;
        }
        
        if(arr[probe] < target){
            left = probe + 1;
        }
        else{
            right = probe - 1;
        }
    }
    return -1; 
}



int main(){


    return 0;
}
