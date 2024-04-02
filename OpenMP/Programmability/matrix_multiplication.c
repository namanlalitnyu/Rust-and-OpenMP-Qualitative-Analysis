#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
	int A[10][10], B[10][10], C[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            A[i][j] = rand()%100;
            B[i][j] = rand()%100;
        }
    }
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int sum = 0;
            for (int k = 0; k < 10; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    for (int i = 0; i < 10; i++) {
		for(int j=0; j < 10; j++) {
            printf("%d ", C[i][j]);
        }
	    printf("\n");
    }
    return 0;
}