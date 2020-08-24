%%cu
#include <bits/stdc++.h>
#include <cuda.h>
#include <time.h>
#include <math.h>
#define ROWS 128
#define COLS 128
#define RANGE 1000

using namespace std;

//# kernel for matrix mul
__global__ void matrixMul_device(int * a, int * b, int * c){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int sum = 0;
    if(row < ROWS && col < COLS){
        for(int i = 0; i < ROWS; i++){
            sum += a[row * ROWS + i] * b[i * COLS + col];
        }
        __syncthreads();
        c[row * ROWS + col] = sum;
    }
}

//# host helper function
void matrixMul_host(int * a, int * b, int * c){
    dim3 threadsPerBlock(ROWS, ROWS);
    dim3 blocksPerGrid(1, 1);

    if( ROWS * ROWS > 512 ){
        threadsPerBlock.x = 512;
        threadsPerBlock.y = 512;
       
        blocksPerGrid.x = ceil(double(ROWS) / double(threadsPerBlock.x));
        blocksPerGrid.y = ceil(double(COLS) / double(threadsPerBlock.y));
    }

    matrixMul_device<<<blocksPerGrid, threadsPerBlock>>>(a, b, c);
}

int main(){
    int * hostA = (int *) malloc(sizeof(int) * ROWS * COLS);
    int * hostB = (int *) malloc(sizeof(int) * ROWS * COLS);
    int * hostC = (int *) malloc(sizeof(int) * ROWS * COLS);

    int * deviceA , * deviceB, * deviceC;

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            hostA[i * COLS + j] = rand() % RANGE;
            hostB[i * COLS + j] = rand() % RANGE;
        }
    }

    //# *************** MUL OPERATION ********************#
    cudaMalloc(&deviceA, sizeof(int) * ROWS * COLS);
    cudaMalloc(&deviceB, sizeof(int) * ROWS * COLS);
    cudaMalloc(&deviceC, sizeof(int) * ROWS * COLS);

    cudaMemcpy(deviceA, hostA, sizeof(int) * ROWS * COLS, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, sizeof(int) * ROWS * COLS, cudaMemcpyHostToDevice);

    clock_t start = clock();
    matrixMul_host(deviceA, deviceB, deviceC);
    clock_t end = clock();

    cudaMemcpy(hostC, deviceC, sizeof(int) * ROWS * COLS, cudaMemcpyDeviceToHost);
    printf("Time taken (parallel) :: %lf", (double) (end - start) / CLOCKS_PER_SEC);

    //# ********************** CPU MUL *****************#
    int * actual = (int *) malloc(sizeof(int) * ROWS * COLS);
    int sum;

    start = clock();
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            sum = 0;
            for(int k = 0; k < COLS; k++){
                sum += hostA[i * ROWS + k] * hostB[k * ROWS + j];
            }
            actual[i * ROWS + j] = sum;
        }
    }
    end = clock();
    printf("\nTime taken (serial) :: %lf", (double) (end - start) / CLOCKS_PER_SEC);

    //# ******* ERROR CHECK ****************** #
    int error = 0;
    for(int i = 0; i < ROWS * COLS; i++){
        error += abs(actual[i] - hostC[i]);
    }

    printf("\n\nError :: %d", sqrt(error));


    cudaFree( deviceA );
    cudaFree( deviceB );
    cudaFree( deviceC );

    free( hostA );
    free( hostB );
    free( hostC );

    return 0;
} 
