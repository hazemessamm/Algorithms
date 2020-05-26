#Knuth shuffle

from random import uniform

a = [1,2,3,4,5,6,7,8,9]

for i in range(len(a)):

    r = int(uniform(0, i+1))
    a[i], a[r] = a[r], a[i]

print(a)
