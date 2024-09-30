/*Write a multithreaded program for generating prime numbers from a given starting number
to the given ending number.*/

#include <pthread.h>
#include <stdio.h>

int n, pr[100];

void* child_thread(void* param) {
    int x = (long)param;
    for (int i = 2; i < x; i++)
        if (x % i == 0) return 0;
    pr[n++] = x;
    return 0;
}

int main() {
    pthread_t thread[100];
    int l, u;
    printf("Enter lower limit: ");
    scanf("%d", &l);
    printf("Enter upper limit: ");
    scanf("%d", &u);

    for (int i = l; i <= u; i++) {
        pthread_create(&thread[i - l], 0, child_thread, (void*)(long)i);
        pthread_join(thread[i - l], 0);
    }

    printf("Prime Numbers in the range:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", pr[i]);
}
