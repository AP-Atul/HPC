#include <bits/stdc++.h>
#include <time.h>
#include <omp.h>
using namespace std;

void sort(vector<int> & arr, long N){
	for(long i = 0; i < N; i++){
		if(i % 2 == 0){
			#pragma omp for
			for(long j = 1; j < N; j += 2){
				if(arr[j - 1] > arr[j])
					swap(arr[j - 1], arr[j]);
			}
		}else{
			#pragma omp for
			for(long j = 1; j < N - 1; j += 2){
				if(arr[j] > arr[j + 1])
					swap(arr[j + 1], arr[j]);
			}
		}
	}
}

void printArray(vector<int> arr, long N){
	for(long i = 0; i < N; i++)
		cout << arr[i] << " ";
}

int main()
{
	long n;
	cin >> n;

	vector<int> arr (n);

	for(long i = 0; i < n; i++){
		cin >> arr[i];
	}

	double time = omp_get_wtime();
	sort(arr, n);
	time = omp_get_wtime() - time;

	cout << "Time taken (parallel) :: " << time << " s";
	printArray(arr, n);

	return 0;
}