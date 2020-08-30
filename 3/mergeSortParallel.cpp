#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>

void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[10000];   
    int i,j,k;
    i=i1;   
    j=i2;   
    k=0;
    
    while(i<=j1 && j<=j2)    
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)   
        temp[k++]=a[i++];
        
    while(j<=j2)    
        temp[k++]=a[j++];
        
   
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}


void mergeSortParallel(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections num_threads(2)
        {
        	#pragma omp section
        	{
		        mergeSortParallel(a,i,mid); 
        	}
        	
        	#pragma omp section
        	{
        		
			mergeSortParallel(a,mid+1,j);
			}
        }

		#pragma omp taskwait
        merge(a,i,mid,mid+1,j);
    }
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d \n", A[i]);
}

int main()
{
    int arr_size;

    scanf("%d", &arr_size);
    int arr[arr_size], tmp[arr_size];

    for(int i = 0; i < arr_size; i++){
        scanf("%d", &arr[i]);
    }

	/******** PARALLEL  OPERATION *************/
	clock_t start = clock();
    mergeSortParallel(arr, 0, arr_size - 1);
   	clock_t end = clock();
	printf("Time taken (parallel) :: %lf s\n", (double) (end - start) / CLOCKS_PER_SEC);
	
	printArray(arr, arr_size);
    return 0;
}
