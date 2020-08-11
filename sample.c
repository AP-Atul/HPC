#include<bits/stdc++.h>
using namespace std;

int main(){
    int n = 3;
    int arr[3] = {2, 3, 1};
    sort(arr, arr + n);
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}