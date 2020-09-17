#include<bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int> &arr, long n){
    if(n == 1)
        return;

    for(long i = 0; i < n - 1; i++)
        if(arr[i] > arr[i + 1])
            swap(arr[i], arr[i+ 1]);

    bubbleSort(arr, n - 1);
}

void printArray(vector<int> arr, long n) 
{ 
    for (long i=0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
}

int main()
{
    long arr_size;

    scanf("%ld", &arr_size);
    vector<int> arr (arr_size);

    for(long i = 0; i < arr_size; i++){
        scanf("%d", &arr[i]);
    }
    
	clock_t start = clock();
    bubbleSort(arr, arr_size);
  	clock_t end = clock();

    printArray(arr, arr_size);
    printf("\nTime taken (serial) :: %lf s \n", (double) (end - start) / CLOCKS_PER_SEC);
    return 0;
}
