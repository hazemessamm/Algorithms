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
        pid = self.components[p]
        qid = self.components[q]
        for i in range(self.n):
            if self.components[i] == pid:
                self.components[i] = qid

uf = UF(10)
uf.union(1,2)
print(uf.is_connected(1,2))

