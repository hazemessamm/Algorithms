def partition(arr,low,high):
    i = low - 1
    pivot = arr[high]
    for j in range(low, high):
        if arr[j] <= pivot:
            i = i + 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1],arr[high] = arr[high],arr[i+1]
    return i+1

def quickSort(arr, low, high):
    if low < high:
        p = partition(arr, low, high)
        quickSort(arr,low, p-1)
        quickSort(arr, p+1, high)

arr = [6, 10, 7, 8, 9, 1, 3, 2, 4, 5] 
n = len(arr)
quickSort(arr,0,n-1) 
print ("Sorted array:") 
for i in range(n): 
    print (arr[i])
    
'''
Worst case performance	O(n2)
Best case performance	O(n log n)
Average case performance	O(n log n)
'''
