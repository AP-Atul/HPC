%%cu
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda.h>
#include <bits/stdc++.h>
#include <iterator>
using namespace std;

__global__
void minimum(int *array, int size)
{
  int tid = threadIdx.x;
  int first = tid * 2;
  int second = first + 1;
  
  if (second == size - 2)
    if (array[0] > array[second + 1]){
      array[0] = array[second + 1];
      return;
    }

  if (array[first] > array[second]){
    if (array[second] < array[0])  array[0] = array[second];
  }else{
    if (array[first] < array[0])  array[0] = array[first];
  }
}


int main()
{
  int n;
  int RANG = 50;
  int minCPU = 1001;
  int maxCPU = 0;
  int sumCPU = 0;

  n = 10;
  int array[n];

  for (int i = 0; i < n; i++)
  {
    int r = rand() % RANG;
    if(r == 0)
      r = rand() % RANG;
   
    array[i] = r;

    if (array[i] > maxCPU)
      maxCPU = array[i];

    if (array[i] < minCPU)
      minCPU = array[i];

    sumCPU += array[i];

    printf("%d ", array[i]);
  }

  int arraySize = n * sizeof(int);

  clock_t start = clock();

  //*************** Store array in pointer ****************/
  int *arrPointer;

  //*************** Minimum operation ********************/
  int minArr[n];
  copy(array, array + n, minArr);
  int minResult;
 
  //allocate memory
  cudaMalloc(&arrPointer, arraySize);
  cudaMemcpy(arrPointer, &minArr, arraySize, cudaMemcpyHostToDevice);

  minimum<<<1, n / 2>>>(arrPointer, n);
 
  cudaMemcpy(&minResult, arrPointer, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\nThe minimum of the array CPU :: %d", minCPU);
  printf("\nThe minimum of the array GPU :: %d \n", minResult);
 
  cudaFree(arrPointer);

  clock_t end = clock();
  printf("\n\nThe time taken :: %lf s \n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
