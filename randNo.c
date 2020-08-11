#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    int RANG = 1000;
    n = 1000;
    printf("%d\n", n);
    
    for(int i = 0; i < n; i++){
        int r = rand() % RANG;
        printf("%d ", r);
    }

}