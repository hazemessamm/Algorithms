#Selection Sort

a = [7, 10, 5, 3, 8, 4, 2, 9, 6]


for i in range(len(a)):
    minimum = i
    for j in range(i+1, len(a)):
        if a[j] < a[i]:
            a[j], a[i] = a[i], a[j]

print(a)
