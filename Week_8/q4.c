/*The Sleeping Barber Problem is a classic synchronization problem that illustrates how to manage a limited resource (a barber) shared among multiple customers. 
Problem Statement:
     - The barber has a barber shop with a limited number of chairs for waiting customers.
     - If there are no customers, the barber goes to sleep.
     - If a customer arrives and the barber is asleep, the customer wakes the barber.
     - If there are no available chairs when a customer arrives, the customer leaves.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t customer, barber;
pthread_mutex_t seat;
int free1 = 2;

void *barb(void *args) {
	while (1) {
		sem_wait(&customer);
		pthread_mutex_lock(&seat);

		if (free1 < 2)
			free1++;
		else if (free1 == 2) printf("Barber sleeping....\n");
		sleep(1);

		printf("Cutting Completed! Free Seats: %d\n", free1);
		sem_post(&barber);

		pthread_mutex_unlock(&seat);
	}
}

void *cust(void *args) {
	while (1) {
		pthread_mutex_lock(&seat);

		if (free1 > 0) {
			free1--;
			printf("Customer Waiting! Free Seats: %d\n", free1);
			sem_post(&customer);
			pthread_mutex_unlock(&seat);
			sem_wait(&barber);
		}
		else{
			printf("Customer left\n");
			pthread_mutex_unlock(&seat);
		}
		//sleep(0.1);
	}
}

int main() {
	pthread_t threads[2];
	sem_init(&barber, 0, 1);
	sem_init(&customer, 0, 1);
	pthread_mutex_init(&seat, 0);
	pthread_create(&threads[0], NULL, &barb, NULL);
	pthread_create(&threads[1], NULL, &cust, NULL);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	sem_destroy(&barber);
	sem_destroy(&customer);
	pthread_mutex_destroy(&seat);
}

/*OUTPUT
Barber sleeping....
Cutting Completed! Free Seats: 2
Customer Waiting! Free Seats: 1
Customer Waiting! Free Seats: 0
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Cutting Completed! Free Seats: 1
Cutting Completed! Free Seats: 2
Customer Waiting! Free Seats: 1
Customer Waiting! Free Seats: 0
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Customer left
Cutting Completed! Free Seats: 1
Cutting Completed! Free Seats: 2

*/
