#include<stdio.h>
#include<stdlib.h>

int main(){
    printf("1000 \n");
    for (int i = 0; i < 1000; i++)
    {
        int n = rand() % 100;
        printf("%d ", n);
    }
}