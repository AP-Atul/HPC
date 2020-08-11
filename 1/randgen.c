#include<stdlib.h>
#include<stdio.h>

int main(){
    int RANGE = 10000;
    int NOE = 1000;

    printf("%d\n", NOE);
    for(int i = 0; i < NOE; i++){
        int r = rand() % RANGE;
        if(r == 0)
            r = rand() % RANGE;

        printf("%d ", r);
    }

    return 0;
}