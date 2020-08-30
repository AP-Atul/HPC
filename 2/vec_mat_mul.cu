%%cu
#include <bits/stdc++.h>
#include <time.h>
#include <cuda.h>
using namespace std;

int MATRIX = 10000;
int VECTOR = 1000;
int RANGE = 1000;

// # kernel for multiplication
__global__ void multiplication(int * A, int * B, int * C, int MATRIX, int VECTOR){
    int N = MATRIX;
    int M = VECTOR;
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int sum = 0;

    if(index < N){
        for(int i = 0; i < M; i++)
          sum += A[i] * B[(index * M) + i];

        C[index] = sum;
    }
}

// # cpu multiplication
void mulCPU(int * A, int * B, int * C){
    for(int i = 0; i < MATRIX; i++){
	    int sum = 0;
	    for(int j = 0; j < VECTOR; j++){
		    sum += A[j] * B[i * VECTOR + j];
	    }
	    C[i] = sum;
	  }
}

int main(){
    int * hostA = (int *) malloc(VECTOR * sizeof(int));
    int * hostB = (int *) malloc(MATRIX * VECTOR * sizeof(int));
    int * hostC = (int *) malloc(VECTOR * sizeof(int));

    int * deviceA, * deviceB, * deviceC;

    for(int i = 0; i < VECTOR; i++) hostA[i] = rand() % RANGE;
    for(int i = 0; i < MATRIX; i++) for(int j = 0; j < VECTOR; j++) hostB[i * VECTOR + j] = rand() % RANGE;

    //# ******************** MUL OPERATION GPU ********************************
    cudaMalloc(&deviceA, VECTOR * sizeof(int));
    cudaMalloc(&deviceB, MATRIX * VECTOR * sizeof(int));
    cudaMalloc(&deviceC, VECTOR * sizeof(int));

    cudaMemcpy(deviceA, hostA, VECTOR * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, MATRIX * VECTOR * sizeof(int), cudaMemcpyHostToDevice);

    clock_t start = clock();
    multiplication<<<MATRIX, 1>>>(deviceA, deviceB, deviceC, MATRIX, VECTOR);
    clock_t end = clock();

    cudaMemcpy(hostC, deviceC, VECTOR * sizeof(int), cudaMemcpyDeviceToHost);
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    //# ******************** MUL OPERATION CPU ********************************
    int * answer = (int *) malloc(VECTOR * sizeof(int));

    start = clock();
    mulCPU(hostA, hostB, answer);
    end = clock();

    printf("\nTime taken (serial) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    //# ******************** ERROR CHECKING ********************************
    double error = 0;
    for(int i = 0; i < VECTOR; i++){
        if(i == 10) printf("\n%d %d", hostC[i], answer[i]);
        
        error += double(answer[i] - hostC[i]);
    }

    printf("\nError: %lf", error);

    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceC);

    free(hostA);
    free(hostB);
    free(hostC);

    return 0;
}
