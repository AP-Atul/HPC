%%cu
#include <bits/stdc++.h>
#include <cuda.h>
#include <time.h>
#include <math.h>
#define N 32768
#define RANGE 1000

using namespace std;

//# summation kernel for two vectors
__global__ void add( int *a, int *b, int *c ) {
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if (tid < N)
        c[tid] = a[tid] + b[tid];
}

int main(){
    int *a, *b, *c;
    int *dev_a, *dev_b, *dev_c;

    a = (int*)malloc( N * sizeof(int) );
    b = (int*)malloc( N * sizeof(int) );
    c = (int*)malloc( N * sizeof(int) );

    for (int i=0; i<N; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    //# *************** SUMMATION *********************** #
    cudaMalloc( (void**)&dev_a, N * sizeof(int) );
    cudaMalloc( (void**)&dev_b, N * sizeof(int) );
    cudaMalloc( (void**)&dev_c, N * sizeof(int) );

    cudaMemcpy( dev_a, a, N * sizeof(int),cudaMemcpyHostToDevice );
    cudaMemcpy( dev_b, b, N * sizeof(int),cudaMemcpyHostToDevice );

    int numThread = 512;
    int numBlock = ceil( double(N) / double(numThread) );

    clock_t start = clock();
    add<<<numBlock,numThread>>>( dev_a, dev_b, dev_c );
    clock_t end = clock();

    cudaMemcpy( c, dev_c, N * sizeof(int),cudaMemcpyDeviceToHost );
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    //# *************** CPU CHECK *********************** #
    int error = 0;

    start = clock();
    for(int i = 0; i < N; i++){
        int diff = (a[i] + b[i]) - c[i];
        error += diff;
    }
    end = clock();
    printf("\nErrors :: %d", error);
    printf("\nTime taken (serial) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    free( a );
    free( b );
    free( c );

    cudaFree( dev_a );
    cudaFree( dev_b );
    cudaFree( dev_c );

    return 0;
}
