import heapq
from typing import List

class Solution:
    def reachableNodes(self, edges: List[List[int]], maxMoves: int, n: int) -> int:
        graph = [[] for _ in range(n)]
        for u, v, count in edges:
            graph[u].append((v, count))
            graph[v].append((u, count))
        
        def dijkstra(graph, start):
            distances = [float('inf')] * len(graph)
            distances[start] = 0
            queue = []
            heapq.heappush(queue, (0, start))

            totalCount = 0

            while queue:
                current_distance, current_destination = heapq.heappop(queue) 

                if distances[current_destination] < current_distance:
                    continue

                totalCount += 1

                for new_destination, count in graph[current_destination]:
                    distance = current_distance + count + 1
                    if distance > maxMoves:
                        continue
                    if distance < distances[new_destination]:
                        distances[new_destination] = distance
                        heapq.heappush(queue, (distance, new_destination))

            for u, v, count in edges:
                uv = (maxMoves - distances[u]) if distances[u] != float('inf') else 0
                vu = (maxMoves - distances[v]) if distances[v] != float('inf') else 0
                totalCount += min(count, uv + vu)

            return totalCount
        
        return dijkstra(graph, 0)
