class UF(object):
    def __init__(self, N):
        self.n = N
        self.components = list(range(0, N))

    def is_connected(self, p, q):
            if self.components[p] == self.components[q]:
                return True
            else:
                return False
    def union(self, p, q):
        self.components[q] = self.components[p]

uf = UF(10)
uf.union(1,2)
print(uf.is_connected(1,2))

