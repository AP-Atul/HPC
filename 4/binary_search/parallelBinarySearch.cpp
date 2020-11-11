/* Parallel Binary Search using MPI */

#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

void binarySearch(int * arr,
				  long start,
				  long end, 
				  long key,
				  int rank)
{
	while(end >= start){
		long mid = (start + end) / 2;

		if(arr[mid] == key){
			cout << "Element found by processor rank :: " << rank << " at location :: " << mid << endl;
			return;
		}

		else if(arr[mid] < key)
			start = mid + 1;

		else
			end = mid - 1;
	}
}

void mpi_call(int * arr, long key, int rank, long blockSize){
	double start = MPI_Wtime();
	binarySearch(arr, rank * blockSize, (rank + 1) * blockSize - 1, key, rank);
	double end = MPI_Wtime();
	// cout << "Execution time of processor rank :: " << rank << " is :: " << (end - start) * 1000 << " s" << endl;
}

int main(int argc, char ** argv){
	long n = 1000000;
	int * array = new int[n];

	// initializing sorted array directly
	for(long i = 0; i < n; i++){
		array[i] = i + 1;
	}	

	long key = 50101;
	cout << "Item to search is :: " << key << endl;

	// MPI intialize 
	MPI_Init(& argc, & argv);

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, & rank);
	MPI_Comm_size(MPI_COMM_WORLD, & size);

	// cout << "[MPI] Processor rank :: " << rank << "\n [MPI] Size of Comm :: " << size << endl;

	int blocks = 2;
	long blockSize = n / blocks;

	mpi_call(array, key, rank, blockSize);

	MPI_Finalize();

	return 0;
}