#include <bits/stdc++.h>
#include <time.h>
using namespace std;

void sort(vector<int> & arr, long N){
	for(long i = 0; i < N; i++){
		if(i % 2 == 0){
			for(long j = 1; j < N; j += 2){
				if(arr[j - 1] > arr[j])
					swap(arr[j - 1], arr[j]);
			}
		}else{
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

	clock_t start = clock();
	sort(arr, n);
	clock_t end = clock();

	printf("Time taken (serial) :: %lf s \n", (double) (end - start) / CLOCKS_PER_SEC);
	printArray(arr, n);

	return 0;
}