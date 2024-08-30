from collections import defaultdict
from typing import List

class Solution:
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        def dfs(node, adj, visited):
            visited[node] = True
            for neighbor in adj[node]:
                if not visited[neighbor]:
                    dfs(neighbor, adj, visited)
        
        adj = defaultdict(list)
        for u, v in prerequisites:
            adj[u].append(v)
        
        reachable = [[False] * numCourses for _ in range(numCourses)]
        
        for i in range(numCourses):
            visited = [False] * numCourses
            dfs(i, adj, visited)
            for j in range(numCourses):
                if visited[j]:
                    reachable[i][j] = True
        
        result = []
        for u, v in queries:
            result.append(reachable[u][v])
        
        return result
