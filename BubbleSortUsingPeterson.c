#include<stdio.h> 
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define size 50000

int arr[50000]; 
int n = sizeof(arr)/sizeof(arr[0]);
int flag[2] = {0,0};
int turn = 0;
int endP1 = 0;
int endP2 = 0;
void swap(int *xp, int *yp)
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void *bubbleSortAscending(void *args) 
{ 
	do{
	flag[0] = 1;
	turn = 2;
	while(flag[1] && turn == 2);
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
endP1 = 1;
flag[0] = 0;
}
while(endP1 == 0);
}
void *bubbleSortDescending(void *args) 
{
	do
	{
	flag[1] = 1;
	turn = 1;
	while(flag[0] && turn == 1); 
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
endP2 = 1;
flag[1] = 0;
}
while(endP2 == 0);
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
	pthread_t t1, t2;
	pthread_create(&t1, NULL, bubbleSortDescending, NULL);
	pthread_create(&t2, NULL, bubbleSortAscending, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);	
	for(i = 0; i < n; i++)
	{
		printf("%d \t", arr[i]);
	}
	printf("\n");
	Check(arr);
    	return 0; 
} 
