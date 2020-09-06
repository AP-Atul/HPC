#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

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

	double time = omp_get_wtime();
    bubbleSort(arr, arr_size);
  	time = omp_get_wtime() - time;

    printArray(arr, arr_size);
    printf("\nTime taken (parallel) :: %lf s \n", time);
    return 0;
}
