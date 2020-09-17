#include <bits/stdc++.h>
#include <time.h>
#include <omp.h>

using namespace std;

// merge the two halves
vector<long> merge(vector<long> & left, vector<long> & right){
	vector<long> result;
	unsigned left_it = 0, right_it = 0;
	
	while(left_it < left.size() && right_it < right.size()){
		if(left[left_it] < right[right_it]){
			result.push_back(left[left_it]);
			left_it++;
		}
		else{
			result.push_back(right[right_it]);
			right_it++;
		}
	}
	
	while(left_it < left.size()){
		result.push_back(left[left_it]);
		left_it++;
	}
	
	while(right_it < right.size()){
		result.push_back(right[right_it]);
		right_it++;
	}
	
	return result;
}

// recursive merge sort
vector<long> mergeSort(vector<long> & vec, int threads){
	if(vec.size() == 1){
		return vec;
	}

	// device the vector in left and right
	vector<long>::iterator middle = vec.begin() + (vec.size() / 2);
	vector<long> left (vec.begin(), middle);
	vector<long> right (middle, vec.end());
	
	// if threads are greater than one do it parallely
	if(threads > 1){
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				left = mergeSort(left, threads / 2);
			}
			#pragma omp section
			{
				right = mergeSort(right, threads - threads / 2);
			}
		}
	}else {
		left = mergeSort(left, 1);
		right = mergeSort(right, 1);
	}
	
	return merge(left, right);
}

void printVector(vector<long> & vec){
	for(long i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
	}
}

int main(){
	long n;
	int numThreads = 4;
	cin >> n;
	vector<long> v (n);

	for(long i = 0; i < n; i++){
		cin >> v[i];
	}
	
	double time = omp_get_wtime();
	v = mergeSort(v, numThreads);
	time = omp_get_wtime() - time;
	
	cout << "Time taken (parallel) :: " << time << " s" << endl;
	printVector(v);

	return 0;
}
