#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
//---------------------------------------------------------
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



int main(int argc, char **argv) {
    int i, n;
    int Array[SIZE];

    if (argc > 1) {
        for (n = 0; n < SIZE && n < argc - 1; n++) {
            Array[n] = strtol(argv[n + 1], NULL, 0);
        }
    } else {
        printf("Give values: ");
        for (n = 0; n < SIZE; n++) {
            if (scanf("%d", &Array[n]) != 1)
                break;
        }
    }

    QuicksortD(Array, 0, n - 1);
    printf("\nOutput: ");
    for (i = 0; i < n; i++) {
        printf("%d  ", Array[i]);
    }
    printf("\n");
    return 0;
}
