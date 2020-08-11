#include<stdio.h>
int main(){
    int n;

    scanf("%d", &n);

    int a[n][n];
    int b[n][n];
    int ans[n][n];

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &b[i][j]);
        }
    }

    printf("Multiplying...");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ans[i][j] += a[i][j] * b[j][i];
        }
    }

    printf("Final array");
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}