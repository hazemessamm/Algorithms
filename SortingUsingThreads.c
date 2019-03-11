#include<stdio.h> 
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#define size 50000

int arr[size]; 
int n = sizeof(arr)/sizeof(arr[0]);

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
void *QuickSortAscending(void *args)
{
	quickSort(arr, 0, n-1);
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

void *QuickSortDescending(void *args)
{
	QuicksortD(arr, 0, n-1);
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
	else if(flag1 == 1 && flag2 == 0)
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
	pthread_create(&t1, NULL, QuickSortDescending, NULL);
	pthread_create(&t2, NULL, QuickSortAscending, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	/**
	for(i = 0; i < n; i++)
	{
		printf("%d \t", arr[i]);
	}
	**/
	Check(arr);
    	return 0; 
} 
