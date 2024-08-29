class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        graph = [[float('inf')] * n for _ in range(n)]
        
        for edge in edges:
            u, v, w = edge
            graph[u][v] = w
            graph[v][u] = w
        
        for i in range(n):
            graph[i][i] = 0
        
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if graph[i][j] > graph[i][k] + graph[k][j]:
                        graph[i][j] = graph[i][k] + graph[k][j]
        
        minReachable = n
        maxCity = -1
        
        for i in range(n):
            count = 0
            for j in range(n):
                if graph[i][j] <= distanceThreshold:
                    count += 1
            if count <= minReachable:
                minReachable = count
                maxCity = i
        
        return maxCity
