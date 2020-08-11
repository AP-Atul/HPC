%%cu
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>

using namespace std;

//# minimum from an array
__global__ void minimum(int *array)
{
  int tid = threadIdx.x;
  int step = 1;
  int noOfThreads = blockDim.x;

  while (noOfThreads > 0)
  {
    if (tid < noOfThreads)
    {
      int first = tid * step * 2;
      int second = first + step;

      if (array[first] > array[second])
        array[first] = array[second];
    }

    step *= 2;
    noOfThreads /= 2;
  }
}

//# maximum from an array
__global__ void maximum(int *array)
{
  int tid = threadIdx.x;
  int step = 1;
  int noOfThreads = blockDim.x;

  while (noOfThreads > 0)
  {
    if (tid < noOfThreads)
    {
      int first = tid * step * 2;
      int second = first + step;

      if (array[first] < array[second])
        array[first] = array[second];
    }

    step *= 2;
    noOfThreads /= 2;
  }
}

//# summation of the array
__global__ void summation(int *array)
{
  int tid = threadIdx.x;
  int step = 1;
  int noOfThreads = blockDim.x;

  while (noOfThreads > 0)
  {
    if (tid < noOfThreads)
    {
      int first = tid * step * 2;
      int second = first + step;

      array[first] += array[second];
    }

    step *= 2;
    noOfThreads /= 2;
  }
}

//# average of the array
__global__ void average(int *array)
{
  int tid = threadIdx.x;
  int step = 1;
  int noOfThreads = blockDim.x;
  int totalElements = noOfThreads * 2;

  while (noOfThreads > 0)
  {
    if (tid < noOfThreads)
    {
      int first = tid * step * 2;
      int second = first + step;

      array[first] += array[second];
    }

    step *= 2;
    noOfThreads /= 2;
  }

  array[0] = array[0] / totalElements;
}

__global__ void standardDeviation(int *array, int xBar)
{
  int tid = threadIdx.x;
  int step = 1;
  int noOfThreads = blockDim.x;
  while (noOfThreads > 0)
  {
    if (tid < noOfThreads)
    {
      int first = tid * step * 2;
      int second = first + step;
      array[first] = pow(array[second] - xBar, 2);
    }
    step *= 2;
    noOfThreads /= 2;
  }
}

int main()
{

  int n = 12;
  int RANG = 100;
  int minCPU = 1001;
  int maxCPU = 0;
  int sumCPU = 0;

  int array[n];

  for (int i = 0; i < n; i++)
  {
    int r = rand() % RANG;
    if (r == 0)
      r = rand() % RANG;

    array[i] = r;

    if (array[i] > maxCPU)
      maxCPU = array[i];

    if (array[i] < minCPU)
      minCPU = array[i];

    sumCPU += array[i];

    printf("%d ", array[i]);
  }

  clock_t start = clock();

  //#*************** Summation operation ********************/
  int sumResult;
  int *arrSum;

  cudaMalloc(&arrSum, sizeof(int) * n);
  cudaMemcpy(arrSum, array, sizeof(int) * n, cudaMemcpyHostToDevice);

  summation<<<1, n / 2>>>(arrSum);

  cudaMemcpy(&sumResult, arrSum, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\n\nThe summation of the array CPU :: %d", sumCPU);
  printf("\nThe summation of the array GPU :: %d \n", sumResult);

  //#*************** Minimum operation ********************/
  int minResult;
  int *arrMin;

  cudaMalloc(&arrMin, sizeof(int) * n);
  cudaMemcpy(arrMin, array, sizeof(int) * n, cudaMemcpyHostToDevice);

  minimum<<<1, n / 2>>>(arrMin);

  cudaMemcpy(&minResult, arrMin, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\n\nThe minimum of the array CPU :: %d", minCPU);
  printf("\nThe minimum of the array GPU :: %d \n", minResult);

  //#*************** Maximum operation ********************/
  int maxResult;
  int *arrMax;

  cudaMalloc(&arrMax, sizeof(int) * n);
  cudaMemcpy(arrMax, array, sizeof(int) * n, cudaMemcpyHostToDevice);

  maximum<<<1, n / 2>>>(arrMax);

  cudaMemcpy(&maxResult, arrMax, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\n\nThe maximum of the array CPU :: %d", maxCPU);
  printf("\nThe maximum of the array GPU :: %d \n", maxResult);

  //#*************** Average operation ********************/
  int avgResult;
  int *arrAvg;

  cudaMalloc(&arrAvg, sizeof(int) * n);
  cudaMemcpy(arrAvg, array, sizeof(int) * n, cudaMemcpyHostToDevice);

  average<<<1, n / 2>>>(arrAvg);

  cudaMemcpy(&avgResult, arrAvg, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\n\nThe average of the array CPU :: %d", sumCPU / n);
  printf("\nThe average of the array GPU :: %d \n", avgResult);

  //#*************** Standard Deviation operation ********************/
  int sdResult;
  int xBar = avgResult;
  int *arrSd;

  cudaMalloc(&arrSd, sizeof(int) * n);
  cudaMemcpy(arrSd, array, sizeof(int) * n, cudaMemcpyHostToDevice);

  standardDeviation<<<1, n / 2>>>(arrSd, xBar);

  cudaMemcpy(&sdResult, arrSd, sizeof(int), cudaMemcpyDeviceToHost);

  printf("\nThe standard deviation of the array GPU :: %lf \n", sqrt(sdResult / n));

  clock_t end = clock();
  printf("\n\nThe time taken :: %lf s \n", (double)(end - start) / CLOCKS_PER_SEC);

  cudaFree(arrSum);
  cudaFree(arrMin);
  cudaFree(arrMax);
  cudaFree(arrAvg);
  cudaFree(arrSd);

  return 0;
}