#!/bin/bash
echo "writing to file..."
./lab >> combined.txt
echo "done"


echo "Dividing"
grep producer combined.txt >> producer.txt
grep consumer1 combined.txt >> consumer1.txt
grep consumer2 combined.txt >> consumer2.txt
grep consumer3 combined.txt >> consumer3.txt
grep consumer4 combined.txt >> consumer4.txt




#include <stdio.h> 
#include <stdlib.h>  
#include <pthread.h> 
#include <semaphore.h> 
#include<unistd.h>

sem_t produce;
sem_t consume;
sem_t lb;


int i = 0;
int buffer[10] = {0,0,0,0,0,0,0,0,0,0};


int RandomNumber(){
		int num = rand() %100;
		return num;
}
void *producer(void *args){
	int num;
	int j = 0;
	do{
		sem_wait(&lb);
		sem_wait(&produce);
		num = getRandom();
		if(i > 9)
		{
			printf("Producer has reached max. index, Re-initializing...\n");
			i=0;
		}
		buffer[i] = num;
		printf("producer: %d\n",buffer[i]);
		i++;
		sem_post(&consume);
		sem_post(&produce);
		j = j + 1
		 
	}while(j < 10000);
}

void *consumer1(){
	int num;
	int j = 0;
	do{
		sem_wait(&consume);
		sem_wait(&produce); 
		if (i > 9)
		{
			printf("Consumer has reached max. index, Re-initializing...\n");
			i=0;		
		}
			
		num = buffer[i];
		printf("consumer1: %d\n",buffer[i]);
		i++;
		sem_post(&lb);
		sem_post(&produce); 
		j = j + 1
	}while(j < 10000);
}
void *consumer2(){
	int num;
	j = 0;
	do{
		sem_wait(&consume); 
		sem_wait(&produce); 
		if (i > 9)
		{
			printf("Consumer has reached max. index, Re-initializing...\n");
			i=0;	
		}
			
		num = buffer[i];
		
		printf("consumer2: %d\n",buffer[i]);
		i++;
		sem_post(&lb); 
		sem_post(&produce);
		j = j + 1
	}while(j < 10000);
}
void *consumer3(){
	int num;
	int j = 0;
	do{
		sem_wait(&consume); 
		sem_wait(&produce); 
		if (i > 9)
		{
			printf("Consumer has reached max. index, Re-initializing...\n");
			i=0;	
		}
		num = buffer[i];
		
		printf("consumer3: %d\n",buffer[i]);
		i++;
		sem_post(&lb);
		sem_post(&produce); 
	}while(j < 10000);
}



void *consumer4(){
	int num;
	int j = 0;
	do{
		sem_wait(&consume); 
		sem_wait(&produce); 
		if (i > 9)
		{
			printf("Consumer has reached max. index, Re-initializing...\n");
			i=0;	
		}
		num = buffer[i];
		printf("consumer4: %d\n",buffer[i]);
		i++;
		sem_post(&lb); 
		sem_post(&produce); 
	}while(j < 10000);
}
int main(){
	sem_init(&produce, 0, 1);
	sem_init(&consume,0,0);
	sem_init(&lb,0,10);
  pthread_t consumer1,consumer2,consumer3,consumer4,producer; 
  pthread_create(&consumer1, NULL, consumer1, NULL);
  pthread_create(&consumer2, NULL, consumer2, NULL);
  pthread_create(&consumer3, NULL, consumer3, NULL);
  pthread_create(&consumer4, NULL, consumer4, NULL);
  pthread_create(&producer, NULL, producer, NULL);
  pthread_join(consumer1, NULL); 
  pthread_join(consumer2, NULL); 
  pthread_join(consumer3, NULL); 
  pthread_join(consumer4, NULL);
  pthread_join(producer, NULL) 
  sem_destroy(&produce);
  sem_destroy(&consume);
  sem_destroy(&lb);

	return 0;
}
