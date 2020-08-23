%%cu
#include<iostream>
#include<math.h>
#include<time.h>
#define n 1024

using namespace std;

//# minimum kernel
__global__ void minimum(int *input) {
    int tid = threadIdx.x;
    int step_size = 1;
    int number_of_threads = blockDim.x;
    
    while(number_of_threads>0) {
        if(tid < number_of_threads) {
            int first = tid*step_size*2;
            int second = first + step_size;
            if(input[second] < input[first])
              input[first] = input[second];
        }
        step_size <<= 1;
        number_of_threads >>= 1;
    }
}

//# maximum kernel
__global__ void maximum(int *input) {
    int tid = threadIdx.x;
    int step_size = 1;
    int number_of_threads = blockDim.x;
    
    while(number_of_threads>0) {
        if(tid < number_of_threads) {
            int first = tid*step_size*2;
            int second = first + step_size;
            if(input[second] > input[first])
              input[first] = input[second];
        }
        step_size <<= 1;
        number_of_threads >>= 1;
    }
}

//# summation kernel
__global__ void sum(int *input) {
    const int tid = threadIdx.x;
    int step_size = 1;
    int number_of_threads = blockDim.x;
    
    while(number_of_threads > 0) {
        if(tid < number_of_threads) {
            int first = tid * step_size * 2;
            int second = first + step_size;
            
            input[first] += input[second];
        }
        step_size <<= 1;
        number_of_threads >>= 1;
       
    }
}

//# mean diff kernel
__global__ void mean_diff_sq(float *input, float mean) {
    input[threadIdx.x] -= mean;
    input[threadIdx.x] *= input[threadIdx.x];
}

//# sum of all mean diff kernel
__global__ void sum_floats(float *input) {
    int tid = threadIdx.x;
    int step_size = 1;
    int number_of_threads = blockDim.x;
    
    while(number_of_threads > 0) {
        if(tid < number_of_threads) {
            int first = tid * step_size * 2;
            int second = first + step_size;
            
            input[first] += input[second];
        }
        step_size <<= 1;
        number_of_threads >>= 1;
       
    }
}

//# copy array as float
void copy_int_to_float(float *dest, int *src, int size){
    for(int i=0; i<size; i++)
        dest[i] = float(src[i]);
}


//# driver code
int main() {
    int size = n*sizeof(int); 
    int *arr;
    int *arr_d, result;
    int minCPU = 10001, maxCPU = 0, sumCPU = 0;
   
    arr = (int *)malloc(size);
    for(int i=0; i<n; i++)  {
        int r = rand()%1000;
        if(r == 0)
          r = rand()%1000;
        arr[i] = r;
    }
    
    cudaMalloc((void **)&arr_d, size);
    
    //#*************** Minimum operation ****************#
    cudaMemcpy(arr_d, arr, size, cudaMemcpyHostToDevice);

    clock_t start = clock();
    minimum<<<1,n/2>>>(arr_d);
    clock_t end = clock();

    cudaMemcpy(&result, arr_d, sizeof(int), cudaMemcpyDeviceToHost);
    
    cout<<"The minimum element is (GPU) :: " << result << endl;
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < n; i++){
         if(arr[i] < minCPU) 
          minCPU = arr[i];
    }
    end = clock();

    cout<<"\n\nThe minimum element is (CPU) "<< minCPU << endl;
    printf("Time taken (serial) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);
    
       
    //#*************** Maximum operation ****************#
    cudaMemcpy(arr_d, arr, size, cudaMemcpyHostToDevice);
    
    start = clock();
    maximum<<<1,n/2>>>(arr_d);
    end = clock();
    
    cudaMemcpy(&result, arr_d, sizeof(int), cudaMemcpyDeviceToHost);
    
    cout << "\n\n\n\nThe maximum element is (GPU) :: " << result << endl;
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < n; i++){
         if(arr[i] > maxCPU) 
          maxCPU = arr[i];
    }
    end = clock();

    cout<<"\n\nThe maximum element is (CPU) "<< maxCPU << endl;
    printf("Time taken (serial) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);
    
    //#*************** Summation operation ****************#
    cudaMemcpy(arr_d, arr, size, cudaMemcpyHostToDevice);
    
    start = clock();
    sum<<<1,n/2>>>(arr_d);
    end = clock();
    
    cudaMemcpy(&result, arr_d, sizeof(int), cudaMemcpyDeviceToHost);
    
    cout << "\n\n\n\nThe summation of elements is (GPU) :: " << result << endl;
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < n; i++){
         sumCPU += arr[i];
    }
    end = clock();

    cout<<"\n\nThe summation of element is (CPU) "<< sumCPU << endl;
    printf("Time taken (serial) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);
    
    
    //#*************** Average operation ****************#    
    float mean = float(result)/n;
    cout << "\n\n\n\nThe mean/average is " << mean << endl;
    
    
    //#*************** Standard deviation operation ****************#
    float *arr_float;
    float *arr_std, stdValue;
    
    arr_float = (float *)malloc(n*sizeof(float));
    cudaMalloc((void **)&arr_std, n*sizeof(float));
    copy_int_to_float(arr_float, arr, n);
    cudaMemcpy(arr_std, arr_float, n*sizeof(float), cudaMemcpyHostToDevice);
    
    start = clock();
    mean_diff_sq <<<1,n>>>(arr_std, mean);
    sum_floats<<<1,n/2>>>(arr_std);
    end = clock();

    cudaMemcpy(&stdValue, arr_std, sizeof(float), cudaMemcpyDeviceToHost);
    
    stdValue = stdValue / n;
    stdValue = sqrt(stdValue);

    cout << "\n\nThe standard deviation of element is (GPU) :: " << stdValue << endl;
    printf("Time taken (parallel) :: %lf s", (double) (end - start) / CLOCKS_PER_SEC);

    cudaFree(arr_d);
           
    return 0;
}
