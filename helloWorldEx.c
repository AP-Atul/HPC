#include <stdio.h>
#include <omp.h>

void main(){
    int x = 0;
    #pragma omp parallel num_threads(5)
    {
        for(int i = 0; i < 5; i++){
            printf("%d", omp_get_thread_num());
        }
    }

    printf("%d", omp_get_num_places());
    printf("%d", x);

    printf("\n");
}