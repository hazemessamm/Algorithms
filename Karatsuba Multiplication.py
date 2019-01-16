def convert(list): 
      
    # Converting integer list to string list 
    s = [str(i) for i in list] 
      
    # Join list items using join() 
    res = int("".join(s)) 
      
    return(res)

print("Enter the first number")
x = list(input())
print("Enter the second number")
y = list(input())
if len(list(x)) == 1 or len(list(y)) == 1:
    print(convert(x) * convert(y))

else:
    #function convert: converts list of multiple numbers into a single integer
    a = convert(list(map(int,x[0:int(len(x)/2)]))) #first half of the X list
    b = convert(list(map(int,x[int(len(x)/2):]))) #second half of the X list
    c = convert(list(map(int,y[0:int(len(y)/2)]))) #first half of the Y list
    d = convert(list(map(int,y[int(len(y)/2):]))) #second half of the Y list
    #karatsuba multiplication
    equ1 = (10**int(len(x)/2)) * a+b
    equ2 = (10**int(len(y)/2)) * c+d
    equation = 10**int(len(x)) * a*c + 10**int(len(x)/2)*(a*d+b*c) + b*d
    print(equation)
