#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

FILE *producerFile;
FILE *ConsumerFile;
sem_t producer, consumer, lockbuffer;
int buffer[10] = {0,0,0,0,0,0,0,0,0,0};

void ConsumerWriter(int Number)
{
	ConsumerFile = fopen("Consumer.txt", "a");
	fprintf(ConsumerFile, "%d\n", Number);
	fclose(ConsumerFile);
}
void ProducerWriter(int Number)
{
	producerFile = fopen("Producer.txt", "a");
	fprintf(producerFile, "%d\n", Number);
	fclose(producerFile);
}
int RandomNumber()
{
	int Number = 0;
	Number = rand()%1000;
	return Number;
}
void *Producer(void *args)
{
	int Number;
	int i = 0;
	long int j = 0;
	while(j <= 1000)
	{
		sem_wait(&lockbuffer);
		sem_wait(&producer);
		Number = RandomNumber();
		if (i == 10)
		{
			printf("Producer has reached max. index, Re-initializing...\n");
			//sleep(1);
			i = 0;
		}
		buffer[i] = Number;
		printf("Producer has produced %d\n", buffer[i]);	
		ProducerWriter(Number);
		//sleep(1);
		i += 1;
		sem_post(&consumer);
		sem_post(&producer);
		j += 1;
		
	}
}
void *Consumer(void *args)
{
	int Number;
	int i = 0;
	long int j;
	while(j <= 1000)
	{
		sem_wait(&consumer);
		sem_wait(&producer);
		if(i == 10)
		{
			printf("Consumer has reached max. index, Re-initializing...\n");
			//sleep(1);
			i = 0;
		}
		Number = buffer[i];
		printf("Consumer has read %d\n", Number);
		ConsumerWriter(Number);
		//sleep(1);
		i += 1;
		sem_post(&lockbuffer);
		sem_post(&producer);
		j+=1;
	}
}

int main(void)
{
	sem_init(&producer, 0,1);
	sem_init(&consumer,0,0);
	sem_init(&lockbuffer,0,10);
	pthread_t ConsumerThread, ProducerThread;
	pthread_create(&ConsumerThread, NULL, Consumer, NULL);
	pthread_create(&ProducerThread, NULL, Producer, NULL);
	pthread_join(ProducerThread,NULL);
	pthread_join(ConsumerThread,NULL);
	sem_destroy(&producer);
	sem_destroy(&consumer);
	return 0;
}
