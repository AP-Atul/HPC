#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSort(vector<int> &arr, long n, int threads){
    if(n == 0)
        return;

    if(threads > 1){
	    #pragma omp parallel sections
	    {
	        #pragma omp section
	        {
	            for(long i = 0; i < n - 1; i++)
	                if(arr[i] > arr[i + 1])
	                    swap(arr[i], arr[i+ 1]);
	        }
	        #pragma omp section
	        {
	            bubbleSort(arr, n - 1, threads / 2);
	        }
	    }
	}else{
		for(long i = 0; i < n - 1; i++)
            if(arr[i] > arr[i + 1])
                swap(arr[i], arr[i+ 1]);
        bubbleSort(arr, n - 1, 1); 
	}

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
	int numThreads = 4;

    scanf("%ld", &arr_size);
    vector<int> arr (arr_size);

    for(long i = 0; i < arr_size; i++){
        scanf("%d", &arr[i]);
    }

	double time = omp_get_wtime();
    bubbleSort(arr, arr_size, numThreads);
  	time = omp_get_wtime() - time;

    printArray(arr, arr_size);
    printf("\nTime taken (parallel) :: %lf s \n", time);
    return 0;
}
