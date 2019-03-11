def binarySearch(arr, head, tail, x):
    if tail >= head:
        mid = head + (tail - 1)//2

        if arr[mid] == x:
            return mid
        elif arr[mid] > x:
            return binarySearch(arr, head, mid-1, x)
        else:
            return binarySearch(arr, mid+1, tail, x)
    else:  
        return 0

arr = [ 2, 3, 4, 10, 40 ] 
x = 10
result = binarySearch(arr, 0, len(arr)-1, x)
if result != 0:
    print("Element found at index", result)
else:
    print("Element is not in the array")


#Worst-Case performance: O(log n)
#Average case performance: O(log n)
#Best case performance: O(1)
#Worst case space complexity: O(1)
