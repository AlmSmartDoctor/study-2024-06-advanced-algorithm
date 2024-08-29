[882 Reachable Nodes In Subdivided Graph](https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/description/)<br/><br/>
![alt-text](images/882.png)
```python
class Solution:
    def reachableNodes(self, edges: List[List[int]], maxMoves: int, n: int) -> int:
        graph = { i:{} for i in range(n) }
        for u, v, w in edges:
            if v not in graph[u]:
                graph[u][v] = w + 1
            if u not in graph[v]:
                graph[v][u] = w + 1
        ans = 0
        distances = { i: float('inf') for i in range(n) }
        heap = [(0,0)]

        while heap:
            dist, node = heapq.heappop(heap)
            if distances[node] < float('inf'):
                continue
            distances[node] = dist
            for neighbor in graph[node]:
                w = graph[node][neighbor]
                if distances[neighbor] == float('inf'):
                    heapq.heappush(heap, (dist + w, neighbor))
        
        for i in range(n):
            if distances[i] <= maxMoves: 
                ans += 1
        
        for u, v, w in edges:
            temp = 0
            if distances[u] < maxMoves:
                temp += maxMoves - distances[u]
            if distances[v] < maxMoves:
                temp += maxMoves - distances[v] 
            ans += min(temp, w)
            
        return ans
```

[1334 Find the City WIth the Smallest number of Heighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)<br/><br/>
![alt-text](images/1334.png)
```python
class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        distance = [[float('inf')]*n for _ in range(n)]
        for i in range(n):
            distance[i][i] = 0
        for a, b, w in edges:
            distance[a][b] = distance[b][a] = w
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if distance[i][k] + distance[k][j] < distance[i][j]:
                        distance[i][j] = distance[i][k] + distance[k][j]
                        
        min_count = float('inf')
        city_index = -1
        
        for i in range(n):
            count = 0
            for j in range(n):
                if distance[i][j] <= distanceThreshold:
                    count += 1
            
            if count <= min_count:
                min_count = count
                city_index = i
        
        return city_index
```