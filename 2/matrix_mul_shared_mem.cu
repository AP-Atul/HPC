%%cu
#include <bits/stdc++.h>
#include <cuda.h>
#define row1 5
#define col1 4
#define row2 4
#define col2 5
#define RANGE 10
using namespace std;

__global__ void matrixMulSharedMemory(long * deviceA, long * deviceB, long * deviceC)
{
    int x = blockIdx.x;
    int y = blockIdx.y;
    __shared__ long answer[col1];
    int tid = threadIdx.x;

    deviceC[col2 * y + x] = 0;
    answer[tid] = deviceA[col1 * y + tid] * deviceB[col2 * tid + x];

    __syncthreads();

    for(int i = 0; i < col1; i++) deviceC[col2 * y + x] += answer[i];
}

void printMatrix(long a[row1][col2]){
  for(int i = 0;  i < row1; i++){
    for(int j = 0 ; j < col2; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}

//# host multiplication
void mulCPU(long hostA[row1][col1], long hostB[row2][col2], long actual[row1][col2]){
    for(int i = 0; i < row1; ++i) 
      for(int j = 0; j < col2; ++j) {
        actual[i][j] = 0;
        for(int k = 0; k < col1; ++k)
          actual[i][j] += hostA[i][k] * hostB[k][j];
      }
}


int main()
{
  long a[row1][col1];
  long b[row2][col2];
  long c[row1][col2];
  bool print = 1;

  long * deviceA, * deviceB, * deviceC;

  for(int i = 0; i < row1; i++)
  {
      for(int j = 0; j < col1; j++)
          {
              a[i][j] = rand() % RANGE;
              b[i][j] = rand() % RANGE;
          }
  }

  //# ************* GPU MUL *******************// 
  cudaMalloc((void **)&deviceA, row1 * col1 * sizeof(long));
  cudaMalloc((void **)&deviceB, row2 * col2 * sizeof(long));
  cudaMalloc((void **)&deviceC, row1 * col2 * sizeof(long));

  cudaMemcpy(deviceA, a, row1 * col1 * sizeof(long), cudaMemcpyHostToDevice);
  cudaMemcpy(deviceB, b, row2 * col2 * sizeof(long), cudaMemcpyHostToDevice);

  dim3 grid(col2,row1);
  clock_t start = clock();
  matrixMulSharedMemory<<<grid,col1>>>(deviceA, deviceB, deviceC);
  double time = clock() - start;

  cudaMemcpy(c, deviceC, row1 * col2 * sizeof(long), cudaMemcpyDeviceToHost);
  printf("Time taken (parallel) :: %lf", time / CLOCKS_PER_SEC);

  //# ***************** CPU MUL ****************//
  long actual[row1][col2];
  
  start = clock();
  mulCPU(a, b, actual);
  time = clock() - start;

  printf("\nTime taken (serial) :: %lf", time / CLOCKS_PER_SEC);

  if(print){
    printf("\n\nCPU matrix :: \n");
    printMatrix(actual);
  
    printf("\n\nGPU matrix :: \n");
    printMatrix(c);
  }
 
  cudaFree(deviceA);
  cudaFree(deviceB);
  cudaFree(deviceC);

  return 0;
}