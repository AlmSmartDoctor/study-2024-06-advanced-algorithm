[2045. Second Minimum Time To Reach Destination](https://leetcode.com/problems/second-minimum-time-to-reach-destination/description/)

![](images/2045.png)

```python
import heapq

class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        graph = [[] for i in range(n+1)]

        for node_1, node_2 in edges:
            graph[node_1].append(node_2)
            graph[node_2].append(node_1)

        distances = [[float('inf'), float('inf')] for i in range(n+1)]
        distances[1][0] = 0

        q = [(0, 1)]

        while q:
            current_distance, current_destination = heapq.heappop(q)

            is_green_light = not (current_distance // change % 2)

            for new_destination in graph[current_destination]:
                print(new_destination)
                distance = current_distance + time if is_green_light else (current_distance//change + 1)*change + time
                if distance < distances[new_destination][0]:
                    distances[new_destination][0] = distance
                    heapq.heappush(q, (distance, new_destination))
                elif distances[new_destination][0] < distance < distances[new_destination][1]:
                    if new_destination == n:
                        return distance
                    distances[new_destination][1] = distance
                    heapq.heappush(q, (distance, new_destination))
```

[1334. Find the City WIth the Smallest number of Heighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/)

![](images/1334.png)

```python
INF = 1e4 + 1

class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        graph = [[INF] * (n) for _ in range(n)]

        for city_1, city_2, weight in edges :
            graph[city_1][city_2] = weight
            graph[city_2][city_1] = weight

        for i in range(n) :
            graph[i][i] = 0

        for k in range(n) :
            for i in range(n) :
                for j in range(n) :
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])

        min_val = n+1
        ans = -1

        for i in range(n) :
            cnt = 0
            for j in range(n) :
                if graph[i][j] <= distanceThreshold:
                    cnt += 1
            if cnt <= min_val:
                min_val = cnt
                ans = i

        return ans
```
