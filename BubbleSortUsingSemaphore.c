#include<stdio.h> 
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<semaphore.h>
#define size 50000

int arr[50000]; 
int n = sizeof(arr)/sizeof(arr[0]);
sem_t mutex;
void swap(int *xp, int *yp)
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void *bubbleSortAscending(void *args) 
{ 
	sem_wait(&mutex);
   	int i, j; 
   	for (i = 0; i < n-1; i++)
	{    
       		for (j = 0; j < n-i-1; j++)
		{  
        	   	if (arr[j] > arr[j+1]) 
			{
        	      		swap(&arr[j], &arr[j+1]);
			}
		}
	}
	sem_post(&mutex);
}
void *bubbleSortDescending(void *args) 
{ 	
	sem_wait(&mutex);
   	int i, j; 
   	for (i = 0; i < n-1; i++)
	{    
       		for (j = 0; j < n-i-1; j++)
		{  
           		if (arr[j] < arr[j+1]) 
			{
              			swap(&arr[j], &arr[j+1]);
			}
		}
	} 
	sem_post(&mutex);
}

void Check(int arr[])
{
	int i = 0;
	int flag1 = 0, flag2 = 0;
	for(i = 0; i < n-1; i++)
	{
		if (arr[i] <= arr[i+1])
		{
			flag1 = 0;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}

	for(i = 0; i < n-1; i++)
	{
		if (arr[i] >= arr[i+1])
		{
			flag2 = 0;
		}
		else
		{
			flag2 = 1;
			break;
		}
	}

	if(flag1 == 1 && flag2 == 1)
	{
		printf("Not sorted\n");
	}
	else if(flag1 == 0 && flag2 == 1)
	{
		printf("Sort: Ascending\n");
	}
	else
	{
		printf("Sort: Descending\n");
	}

}
int main() 
{   	
	srand(time(NULL));
	int i = 0;
	for(i = 0; i < size; i++) 
   	{	
      		arr[i] = rand() % 9000 + 1000;
	}
	sem_init(&mutex, 0, 1);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, bubbleSortDescending, NULL);
	pthread_create(&t2, NULL, bubbleSortAscending, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	sem_destroy(&mutex);	
	for(i = 0; i < n; i++)
	{
		printf("%d \t", arr[i]);
	}
	printf("\n");
	Check(arr);
    	return 0; 
} 
