def mergeSort(arr): 
    if len(arr) >1: 
        mid = len(arr)//2  
        L = arr[:mid]   #dividing the array into 2 halves
        R = arr[mid:]  
  
        mergeSort(L)  
        mergeSort(R) 
  
        i = j = k = 0
        #Compare data between list L and list R
        while i < len(L) and j < len(R): 
            if L[i] < R[j]: 
                arr[k] = L[i] 
                i+=1
            else: 
                arr[k] = R[j] 
                j+=1
            k+=1
        #checking
        while i < len(L): 
            arr[k] = L[i] 
            i+=1
            k+=1
        while j < len(R): 
            arr[k] = R[j] 
            j+=1
            k+=1

        return arr

arr = [1,8,6,7,1,5,3]
arr = mergeSort(arr)
print(arr)


#Worst case performance: O(n log n)
#Best case performance: O(n log n)
#Average case performance: O(n log n)
