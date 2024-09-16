#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>
int buf[10],f,r;
sem_t mutex,full,empty;

void *produce(void *arg)
{
	int i;
	for(i=0;i<20;i++)  //this just means that the storage can have 20 items, but shelf can have only 10
	{
		printf("In producer::");
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("produced item is %d\n",i);
		buf[(++r)%10]=i;
		//sleep(0.1);
		sem_post(&mutex);
		sem_post(&full);
		int value;
		sem_getvalue(&full, &value);
		//printf("fullP %d\n",value);
	}
}

void *consume(void *arg)
{
	int item,i;
	for(i=0;i<20;i++)
	{
		printf("In consumer::");
		sem_wait(&full);
		int value;
		sem_getvalue(&full, &value);
		//printf("fullC %d\n",value);
		sem_wait(&mutex);
		item=buf[(++f)%10];
		printf("WHAT consumed item is %d\n",item);
		//sleep(0.1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main()
{
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,10);
	pthread_create(&tid1,NULL,produce,NULL);
	pthread_create(&tid2,NULL,consume,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}

/*OUTPUT
In producer::produced item is 0
In producer::produced item is 1
In producer::produced item is 2
In producer::produced item is 3
In producer::produced item is 4
In producer::produced item is 5
In producer::produced item is 6
In producer::produced item is 7
In consumer::WHAT consumed item is 0
In consumer::WHAT consumed item is 1
In consumer::WHAT consumed item is 2
In consumer::WHAT consumed item is 3
In consumer::WHAT consumed item is 4
In consumer::WHAT consumed item is 5
In consumer::WHAT consumed item is 6
In consumer::WHAT consumed item is 7
In consumer::In producer::produced item is 8
In producer::produced item is 9
In producer::produced item is 10
In producer::produced item is 11
In producer::produced item is 12
In producer::produced item is 13
In producer::produced item is 14
In producer::produced item is 15
WHAT consumed item is 8
In consumer::WHAT consumed item is 9
In producer::In consumer::produced item is 16
In producer::produced item is 17
In producer::produced item is 18
In producer::produced item is 19
WHAT consumed item is 10
In consumer::WHAT consumed item is 11
In consumer::WHAT consumed item is 12
In consumer::WHAT consumed item is 13
In consumer::WHAT consumed item is 14
In consumer::WHAT consumed item is 15
In consumer::WHAT consumed item is 16
In consumer::WHAT consumed item is 17
In consumer::WHAT consumed item is 18
In consumer::WHAT consumed item is 19

*/
