- [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)

![alt](./1584.png)

```python
class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:

        n = len(points)

        min_heap = [(0, 0)]
        in_mst = [False] * n
        total_cost = 0
        edges_used = 0

        while edges_used < n:
            cost, point = heapq.heappop(min_heap)

            if in_mst[point]:
                continue

            in_mst[point] = True
            total_cost += cost
            edges_used += 1

            for next_point in range(n):
                if not in_mst[next_point]:
                    next_cost = abs(points[point][0] - points[next_point][0]) + abs(points[point][1] - points[next_point][1])
                    heapq.heappush(min_heap, (next_cost, next_point))

        return total_cost
```

- [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)

![alt](./1489.png)

```python
class Solution:
    class UnionFind:
        def __init__(self, size):
            self.parent = list(range(size))
            self.rank = [1] * size

        def find(self, x):
            if self.parent[x] != x:
                self.parent[x] = self.find(self.parent[x])
            return self.parent[x]

        def union(self, x, y):
            rootX = self.find(x)
            rootY = self.find(y)
            if rootX != rootY:
                if self.rank[rootX] > self.rank[rootY]:
                    self.parent[rootY] = rootX
                elif self.rank[rootX] < self.rank[rootY]:
                    self.parent[rootX] = rootY
                else:
                    self.parent[rootY] = rootX
                    self.rank[rootX] += 1
                return True
            return False

    def kruskal(self, n, edges, exclude_edge=-1, include_edge=-1):
        uf = self.UnionFind(n)
        mst_weight = 0
        edges_used = 0

        if include_edge != -1:
            u, v, w, _ = edges[include_edge]
            if uf.union(u, v):
                mst_weight += w
                edges_used += 1

        for i, (u, v, w, _) in enumerate(edges):
            if i == exclude_edge:
                continue
            if uf.union(u, v):
                mst_weight += w
                edges_used += 1
            if edges_used == n - 1:
                break

        return mst_weight if edges_used == n - 1 else float('inf')

    def findCriticalAndPseudoCriticalEdges(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        edges = [(u, v, w, i) for i, (u, v, w) in enumerate(edges)]
        edges.sort(key=lambda x: x[2])

        original_mst_weight = self.kruskal(n, edges)

        critical_edges = []
        pseudo_critical_edges = []

        for i in range(len(edges)):
            u, v, w, idx = edges[i]

            if self.kruskal(n, edges, exclude_edge=i) > original_mst_weight:
                critical_edges.append(idx)
            else:
                if self.kruskal(n, edges, include_edge=i) == original_mst_weight:
                    pseudo_critical_edges.append(idx)

        return [critical_edges, pseudo_critical_edges]

```
