#include <stdio.h>

//__global__ 
void sum(int a, int b){
    printf("%d \n", a + b);
}

int main(){
    int n = 10;
    int arr[n];

    int s = 0;
    for(int i = 0 ; i < n ;i++){
        scanf("%d", &arr[i]);
        s += arr[i];
    }

    
    for(int i = 0; i < n -1 ;i + 2 ){
        sum(arr[i],arr[i + 1]);
    }

    printf("\n\n\n %d", s);

    return 0;
}