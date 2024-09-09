https://leetcode.com/problems/min-cost-to-connect-all-points/
<img width="500" src="https://github.com/user-attachments/assets/90d0c106-d077-4dd9-a83f-d970c285b3b3">

```python
class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:        
        def find(i):
            if parents[i]!= i:
                parents[i] = find(parents[i])
            return parents[i]

        def union(i,j):
            rooti = find(i)
            rootj = find(j)
            if rooti != rootj:
                if ranks[rooti] <= ranks[rootj]:
                    parents[rooti] = rootj
                    ranks[rootj] += 1
                else:
                    parents[rootj] = rooti
                    ranks[rooti] += 1

        n = len(points)
        edges = []
        for i in range(n):
            for j in range(i + 1, n):
                distance  = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                edges.append((i, j, distance))
        edges.sort(key=lambda x:x[2])
        parents = list(range(n))
        ranks = [0] * n
        min_cost = 0

        for v, u, distance in edges:
            if find(u) != find(v):
                min_cost += distance
                union(u, v)
        return min_cost
```
</br>

https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
<img width="500" src="https://github.com/user-attachments/assets/b5c4be87-d96b-4e0e-a2e0-373ea1b0a647">

```python
class Solution:
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        for i in range(len(edges)):
            edges[i].append(i)
        
        edges.sort(key=lambda x: x[2])

        parent = list(range(n))
        rank = [0] * n
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if rank[rootX] > rank[rootY]:
                    parent[rootY] = rootX
                elif rank[rootX] < rank[rootY]:
                    parent[rootX] = rootY
                else:
                    parent[rootY] = rootX
                    rank[rootX] += 1

        def kruskal(edges, n, exclude_edge=None, include_edge=None):
            parent[:] = list(range(n))
            rank[:] = [0] * n
            weight = 0
            count = 0
            
            if include_edge is not None:
                u, v, w, idx = edges[include_edge]
                union(u, v)
                weight += w
                count += 1

            for i, (u, v, w, idx) in enumerate(edges):
                if i == exclude_edge:
                    continue
                if find(u) != find(v):
                    union(u, v)
                    weight += w
                    count += 1
                    if count == n - 1:
                        break

            if count < n - 1:
                return float('inf')
            return weight

        mst_weight = kruskal(edges, n)

        criticals, pseudo_criticals = [], []

        for i in range(len(edges)):
            new_weight = kruskal(edges, n, exclude_edge=i)
            if new_weight > mst_weight:
                criticals.append(edges[i][3])

        for i in range(len(edges)):
            if edges[i][3] not in criticals:
                new_weight = kruskal(edges, n, include_edge=i)
                if new_weight == mst_weight:
                    pseudo_criticals.append(edges[i][3])

        return [criticals, pseudo_criticals]

```
