#include<stdio.h> 
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define size 50000
int arr[50000]; 
int n = sizeof(arr)/sizeof(arr[0]);
void *quick(void *args)
{
	quickSort(arr, 0, n-1);
}  
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; 
    int i = (low - 1);  
  
    for (int j = low; j <= high- 1; j++) 
    { 
         
        if (arr[j] <= pivot) 
        { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  

void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    }	
}
//--------------------------------------------
void *quickD(void *args)
{
	QuicksortD(arr, 0, n-1);
}


void swapD(int Array[], int one, int two) {
    int temp = Array[one];
    Array[one] = Array[two];
    Array[two] = temp;
}

int partitionD(int Array[], int left, int right) {
    int pivot = Array[right];
    int leftPointer = left - 1;
    int rightPointer = right;
    for (;;) {
        while (Array[++leftPointer] > pivot) {
        }
        while (rightPointer > 0 && Array[--rightPointer] < pivot) {
        }
        if (leftPointer >= rightPointer) {
            break;
        } else {
            swapD(Array, leftPointer, rightPointer);
        }
    }
    /* move pivot to partition point */
    swapD(Array, leftPointer, right);
    return leftPointer;
}

void QuicksortD(int Array[], int left, int right) {
    if (left < right) {
        int PartitionPoint = partitionD(Array, left, right);
        QuicksortD(Array, left, PartitionPoint - 1);
        QuicksortD(Array, PartitionPoint + 1, right);
    }
}

int CheckA(int arr[])
{
	int i = 0;
	int flag = 0;
	for(i = 0; i < size-1; i++)
	{
		if (arr[i] <= arr[i+1])
		{
			flag = 0;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int CheckD(int arr[])
{
	int i = 0;
	int flag = 0;
	for(i = 0; i < size-1; i++)
	{
		if (arr[i] >= arr[i+1])
		{
			flag = 0;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int main() 
{ 
    	//int n = sizeof(arr)/sizeof(arr[0]); 
    	//quickSort(arr, 0, n-1);
	srand(time(NULL));
	int i = 0;
	for( i = 0 ; i < 50000 ; i++ ) 
   	{
      		arr[i] = rand() % 10000+1;
	}
	pthread_t t1, t2;
	pthread_create(&t1, NULL, quickD, NULL);
	pthread_create(&t2, NULL, quick, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	int j = 0;
	int flag = 0; 
	int x = 0, y = 0;   	
	for(j = 0; j < 50000; j++)
	{
		printf("%d\n", arr[j]);
	}
	x = CheckA(arr);
	y = CheckD(arr);
	if(x == 1 && y == 1)
	{
		printf("Not sorted\n");
	}
	else if(x == 1 && y == 0)
	{
		printf("Sorted as descending\n");
	}
	else
	{
		printf("Sorted as ascending\n");
	}
    	return 0; 
} 
