#Insertion Sort

a = [7, 10, 5, 3, 8, 4, 2, 9, 6]


for i in range(len(a)):
    for j in range(i, 0, -1):
        if a[j] < a[j-1]:
            a[j], a[j-1] = a[j-1], a[j]
        else:
            break

print(a)
