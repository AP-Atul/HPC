#include <bits/stdc++.h>
using namespace std;

int main(){
	int N = 1000;
	int RANG = 1000;
	
	printf("%d\n", N);
	for(int i = 0; i < N; i++){
		int r = rand() % RANG;
		if(r == 0) r = rand() % RANG;
		printf("%d ", r);
	}
	
	return 0;
}
	 
