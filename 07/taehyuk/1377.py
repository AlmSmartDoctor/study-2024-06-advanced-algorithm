class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        graph = {i: [] for i in range(1, n + 1)}

        for v, w in edges:
            graph[v].append(w)
            graph[w].append(v)

        queue = deque([(1, t, 1.0)])
        visited = {1}

        while queue:
            current, time, p = queue.popleft()
            neighbors = len(graph[current]) - 1
            if current == 1:
                neighbors += 1

            if current == target:
                if (current == 1 and time > 1) or (neighbors > 0 and time > 0):
                    return 0
                return p

            if time > 0:
                for neighbor in graph[current]:
                    if neighbor not in visited:
                        queue.append((neighbor, time - 1, p / neighbors))
                        visited.add(neighbor)

        return 0