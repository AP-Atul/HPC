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
vector<long> mergeSort(vector<long> & vec){
	if(vec.size() == 1){
		return vec;
	}

	vector<long>::iterator middle = vec.begin() + (vec.size() / 2);
	vector<long> left (vec.begin(), middle);
	vector<long> right (middle, vec.end());
	
	left = mergeSort(left);
	right = mergeSort(right);
	
	return merge(left, right);
}

void printVector(vector<long> & vec){
	for(long i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
	}
}

int main(){
	long n;
	cin >> n;
	vector<long> v (n);
	
	for(long i = 0; i < n; i++){
		cin >> v[i];
	}
	
	
	clock_t start = clock();
	v = mergeSort(v);
	double time = (double) (clock() - start) / CLOCKS_PER_SEC;
	
	cout << "Time taken (serial) :: " << time << " s" << endl;
	printVector(v);

	return 0;
}
