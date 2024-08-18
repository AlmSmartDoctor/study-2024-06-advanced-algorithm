- [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/description/)

![alt-text](./279.png)

```python
class Solution:
    def numSquares(self, n: int) -> int:
        squares = [ x ** 2 for x in range(1, int(n ** 0.5) + 1)]
        queue = deque([(n, 0)])
        visited = set()

        while queue:
            remaining, level = queue.popleft()

            for square in squares:
                next_remaining = remaining - square

                if next_remaining == 0:
                    return level + 1

                if next_remaining > 0 and next_remaining not in visited:
                    visited.add(next_remaining)
                    queue.append((next_remaining, level + 1))
                elif next_remaining < 0:
                    break

        return 0
```

- [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/description/)

![alt-text](./2360.png)

```python
class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        visited = [0] * n
        longest_cycle = -1

        def dfs(node, path):
            nonlocal longest_cycle
            if visited[node] == 1:
                cycle_length = len(path) - path.index(node)
                longest_cycle = max(longest_cycle, cycle_length)
                return
            if visited[node] == 2 or edges[node] == -1:
                return

            visited[node] = 1
            path.append(node)

            if edges[node] != -1:
                dfs(edges[node], path)

            visited[node] = 2
            path.pop()


        for i in range(n):
            if visited[i] == 0:
                dfs(i, [])

        return longest_cycle
```
