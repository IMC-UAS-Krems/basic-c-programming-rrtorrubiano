#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void freeMatrix(int **matrix, int n) {
    int i = 0;
    for(i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}


int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE
    int nargs = argc - 1;
    if (nargs != 2) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", nargs);
        return 1;
    }

    int i = 0;
    for(i = 1; i < argc; i++) {
        int arg = atoi(argv[i]);
        if (arg <= 0) {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 1;
        }
    }
    
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int **matrix = (int **) malloc(n * sizeof(int*));
    if (!matrix) {
        printf("Not enough memory\n");
        return 1;
    }
    int j = 0;
    for(i = 0; i < n; i++) {
        matrix[i] = (int *) malloc(m * sizeof(int));
        if (!matrix[i]) {
            for(j = 0; j < i; j++) {
                free(matrix[j]);
                printf("Not enough memory\n");
                return 1;
            }
        }
        for(j = 0; j < m; j++) {
            int randn = minrand + rand() % (maxrand - minrand + 1);
            matrix[i][j] = randn;
        }
    }

    // write to output file
    FILE *f = fopen("matrix.txt", "w");
    if (!f) {
        freeMatrix(matrix, n);
        printf("Could not write output file\n");
        return 1;
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if (j == m-1) {
                fprintf(f, "%d\n", matrix[i][j]);
            }
            else {
                fprintf(f, "%d ", matrix[i][j]);
            }
        }
    }

    // success!
    fclose(f);

    return 0;
}
