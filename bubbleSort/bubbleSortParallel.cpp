#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

// void swap(int *a, int *b){
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

void bubbleSort(int arr[], int n){
    if(n == 1)
        return;

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            // #pragma omp parallel for
            for(int i = 0; i < n - 1; i++)
                if(arr[i] > arr[i + 1])
                    swap(arr[i], arr[i+ 1]);
        }

        #pragma omp section
        {
            bubbleSort(arr, n - 1);
        }
    }

}

void printArray(int arr[], int n) 
{ 
    for (int i=0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

int main()
{
    int arr_size;

    scanf("%d", &arr_size);
    int arr[arr_size];

    for(int i = 0; i < arr_size; i++){
        scanf("%d", &arr[i]);
    }

    printf("Given array is \n");
    printArray(arr, arr_size);

    bubbleSort(arr, arr_size);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}