#include <bits/stdc++.h>
using namespace std;

int main(){
	long N = 10000000;
	int RANG = 1000;
	
	printf("%ld\n", N);
	for(long i = 0; i < N; i++){
		int r = rand() % RANG;
		if(r == 0) r = rand() % RANG;
		printf("%d ", r);
	}
	
	return 0;
}
	 
