class QU:
    def __init__(self, N):
        self.n = N
        self.components = list(range(0, N))
        
    def union(self, p, q):
        i = self.__root(p)
        j = self.__root(q)
        self.components[i] = j
        
    def is_connected(self, p, q):
        return self.components[p] == self.components[q]
    
    def __root(self, p):
        while p != self.components[p]:
            p = self.components[p]
        return p
            


qu = QU(10)


qu.union(4,3)
qu.union(3,8)
qu.union(6,5)
qu.union(9,4)
qu.union(2,1)
qu.union(5,0)
qu.union(7,2)
qu.union(6,1)
qu.union(7,3)


print(qu.components)
