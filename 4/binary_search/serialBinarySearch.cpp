/* Serial Binary Search */

#include <bits/stdc++.h>

using namespace std;

void binarySearch(int * arr,
				  long start,
				  long end, 
				  long key)
{
	while(end >= start){
		long mid = (start + end) / 2;

		if(arr[mid] == key){
			cout << "Element found at location :: " << mid << endl;
			return;
		}

		else if(arr[mid] < key)
			start = mid + 1;

		else
			end = mid - 1;
	}
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

	binarySearch(array, 0, n - 1, key);

	return 0;
}