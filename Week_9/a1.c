/*Write a multithreaded program for matrix multiplication.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

typedef struct {
    int row;
    int col;
} ThreadData;

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int n; // Size of matrices

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;
    for (int k = 0; k < n; k++)
        sum += A[data->row][k] * B[k][data->col];
    C[data->row][data->col] = sum;
    return NULL;
}

int main() {
    // Read the size of the matrices
    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    pthread_t threads[MAX][MAX];
    ThreadData thread_data[MAX][MAX];

    // Create threads for each element in the result matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            thread_data[i][j].row = i;
            thread_data[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, &thread_data[i][j]);
        }
    }

    // Join threads
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result matrix
    printf("Result matrix C (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

