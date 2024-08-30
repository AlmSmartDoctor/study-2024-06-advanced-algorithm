class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        class OptimizedDisjointSet:
            def __init__(self, n):
                self.parent = list(range(n))
                self.rank = [1] * n

            def find(self, u):
                if u != self.parent[u]:
                    self.parent[u] = self.find(self.parent[u])
                return self.parent[u]

            def merge(self, u, v):
                u = self.find(u)
                v = self.find(v)
                if u != v:
                    if self.rank[u] > self.rank[v]:
                        self.parent[v] = u
                    elif self.rank[u] < self.rank[v]:
                        self.parent[u] = v
                    else:
                        self.parent[v] = u
                        self.rank[u] += 1

        n = len(edges)
        disjointSet = OptimizedDisjointSet(n + 1)

        for u, v in edges:
            if disjointSet.find(u) == disjointSet.find(v):
                return [u, v]
            else:
                disjointSet.merge(u, v)

        return []