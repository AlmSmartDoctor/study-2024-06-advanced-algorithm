- [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)

![](images/1584.png)

```python
class Solution(object):
    def calCost(self, u, v):
        x_1, y_1 = u
        x_2, y_2 = v

        return abs(x_1 - x_2) + abs(y_1 - y_2)

    def minCostConnectPoints(self, points):
        ret = 0
        n = len(points)

        edges = []
        for i in range(n):
            for j in range(i + 1, n):
                u, v = points[i], points[j]
                edges.append((self.calCost(u, v), (i, j)))

        edges.sort()

        ds = DisjointSet(n)

        for i in range(len(edges)):
            cost = edges[i][0]
            u, v = edges[i][1]

            if ds.find(u) == ds.find(v):
                continue

            ds.merge(u, v)
            ret += cost

        return ret

class DisjointSet(object):
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [1 for i in range(n)]

    def find(self, u):
        if u == self.parent[u]:
            return u
        self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def merge(self, u, v):
        u, v = self.find(u), self.find(v)

        if u == v:
            return
        if self.rank[u] > self.rank[v]:
            u, v = v, u
        if self.rank[u] == self.rank[v]:
            self.rank[v] += 1
        self.parent[u] = v
```

- [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)

![](images/1489.png)

```python
class Solution(object):
    def findCriticalAndPseudoCriticalEdges(self, n, edges):
        def calMinimumCost(include_idx, exclude_idx):
            ret = 0

            new_edges = [edges[i] for i in range(len(edges)) if i != include_idx and i != exclude_idx]
            new_edges.sort(key=lambda x: x[2])

            ds = DisjointSet(n)

            if include_idx is not None:
                u, v, cost = edges[include_idx]
                ds.merge(u, v)
                ret += cost

            for edge in new_edges:
                u, v, cost = edge

                if ds.find(u) == ds.find(v):
                    continue

                ds.merge(u, v)
                ret += cost

            if any(ds.find(0) != ds.find(i) for i in range(1, n)):
                return float("inf")

            return ret

        min_cost = calMinimumCost(None, None)

        critical_edges, pseudo_critical_edges = [], []

        for i in range(len(edges)):
            if calMinimumCost(None, i) > min_cost:
                critical_edges.append(i)
            elif calMinimumCost(i, None) == min_cost:
                pseudo_critical_edges.append(i)

        return [critical_edges, pseudo_critical_edges]

class DisjointSet(object):
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [1 for i in range(n)]

    def find(self, u):
        if u == self.parent[u]:
            return u
        self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def merge(self, u, v):
        u, v = self.find(u), self.find(v)

        if u == v:
            return
        if self.rank[u] > self.rank[v]:
            u, v = v, u
        if self.rank[u] == self.rank[v]:
            self.rank[v] += 1
        self.parent[u] = v
```
