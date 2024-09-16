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
