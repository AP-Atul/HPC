%%cu
#include <bits/stdc++.h>
#include <cuda.h>
#define row1 200
#define col1 300
#define row2 300
#define col2 200
#define RANGE 1000

__global__ void matrixMulSharedMemory(int * deviceA, int * deviceB, int * deviceC)
{
    int x = blockIdx.x;
    int y = blockIdx.y;
    __shared__ int answer[col1];
    int tid = threadIdx.x;

    deviceC[col2 * y + x] = 0;
    answer[tid] = deviceA[col1 * y + tid] * deviceB[col2 * tid + x];

    __syncthreads();

    for(int i = 0;i < col1; i++) deviceC[col2 * y + x] += answer[i];
}

//# host multiplication
void mulCPU(int hostA[row1][col1], int hostB[row2][col2], int actual[row1][col2]){
    for(int i = 0; i < row1; ++i) 
      for(int j = 0; j < col2; ++j) 
        for(int k = 0; k < col1; ++k) 
          actual[i][j] += hostA[i][k] * hostB[k][j];
}

int main()
{
  int a[row1][col1];
  int b[row2][col2];
  int c[row1][col2];

  int * deviceA, * deviceB, * deviceC;

  for(int i = 0; i < row1; i++)
  {
      for(int j = 0; j < col1; j++)
          {
              a[i][j] = rand() % RANGE;
              b[i][j] = rand() % RANGE;
          }
  }

  //# ************* GPU MUL *******************// 
  cudaMalloc((void **)&deviceA, row1 * col1 * sizeof(int));
  cudaMalloc((void **)&deviceB, row2 * col2 * sizeof(int));
  cudaMalloc((void **)&deviceC, row1 * col2 * sizeof(int));

  cudaMemcpy(deviceA, a, row1 * col1 * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(deviceB, b, row2 * col2 * sizeof(int), cudaMemcpyHostToDevice);

  dim3 grid(col2,row1);
  clock_t start = clock();
  matrixMulSharedMemory<<<grid,col1>>>(deviceA, deviceB, deviceC);
  double time = clock() - start;

  cudaMemcpy(c, deviceC, row1 * col2 * sizeof(int), cudaMemcpyDeviceToHost);
  printf("Time taken (parallel) :: %lf", time / CLOCKS_PER_SEC);

  //# ***************** CPU MUL ****************//
  int actual[row1][col2];
  
  start = clock();
  mulCPU(a, b, actual);
  time = clock() - start;

  printf("\nTime taken (serial) :: %lf", time / CLOCKS_PER_SEC);

  cudaFree(deviceA);
  cudaFree(deviceB);
  cudaFree(deviceC);

  return 0;
}