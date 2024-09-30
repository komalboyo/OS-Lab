/*Write a multithreaded program for finding row sum and column sum*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

int matrix[MAX][MAX];
int rowSum[MAX] = {0}; 
int colSum[MAX] = {0};
int n;

typedef struct {
    int index; // Row or column index
    int isRow; // 1 for row, 0 for column
} ThreadData;

void* calculateSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    if (data->isRow) { // If calculating row sum
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[data->index][j];
        }
        rowSum[data->index] = sum;
    } else { // If calculating column sum
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][data->index];
        }
        colSum[data->index] = sum;
    }

    return NULL;
}

int main() {
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    pthread_t rowThreads[MAX], colThreads[MAX];
    ThreadData rowData[MAX], colData[MAX];

    // Create threads for calculating row sums
    for (int i = 0; i < n; i++) {
        rowData[i].index = i;
        rowData[i].isRow = 1; // Row sum
        pthread_create(&rowThreads[i], NULL, calculateSum, &rowData[i]);
    }

    // Create threads for calculating column sums
    for (int j = 0; j < n; j++) {
        colData[j].index = j;
        colData[j].isRow = 0; // Column sum
        pthread_create(&colThreads[j], NULL, calculateSum, &colData[j]);
    }

    // Join row sum threads
    for (int i = 0; i < n; i++) {
        pthread_join(rowThreads[i], NULL);
    }

    // Join column sum threads
    for (int j = 0; j < n; j++) {
        pthread_join(colThreads[j], NULL);
    }

    // Print row sums
    printf("Row sums:\n");
    for (int i = 0; i < n; i++) {
        printf("Row %d: %d\n", i, rowSum[i]);
    }

    // Print column sums
    printf("Column sums:\n");
    for (int j = 0; j < n; j++) {
        printf("Column %d: %d\n", j, colSum[j]);
    }

    return 0;
}

