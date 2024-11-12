#include<iostream>
#include <cmath>
#include<vector>
using namespace std;

    int dynamicJump(vector<int> &arr, int target){
        int n = arr.size();
        int step = sqrt(n);
        int prev  = 0;

        // tim khoi61 chua target

        while(arr[min(step,n)-1] < target){
            prev = step;
            step += sqrt(n);   // tang buoc nhay
            if(prev >= n ){ return -1;}  // vuot ra khoi so cuoi cung
        }

        while(arr[prev] < target){
            prev ++;  // tang range ben trai neu chua cham toi target
            if(prev == min(step,n)) return -1;
        }

        if(arr[prev == target]){
            return prev;  // return vị trí tìm thấy 
        }

        return -1;  // khong tim thay



    }
