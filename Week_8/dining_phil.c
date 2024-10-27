#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];  // One semaphore per fork

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);  // Simulate thinking

        // Take the forks
        printf("Philosopher %d is hungry and trying to pick up forks.\n", id);
        
        // Philosophers pick up the lower numbered fork first to avoid deadlock
        sem_wait(&forks[id]);                     // Pick up left fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        printf("Philosopher %d is eating.\n", id);
        sleep(1);  // Simulate eating

        // Put down the forks
        sem_post(&forks[id]);                    // Put down left fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork

        printf("Philosopher %d finished eating and put down forks.\n", id);
        sleep(1);  // Simulate back to thinking
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join threads (in this example, the philosophers run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
