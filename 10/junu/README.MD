- [1992. Find All Groups of Farmland](https://leetcode.com/problems/find-all-groups-of-farmland/description/)

![alt-text](./1992.png)

```python
class Solution:
    def findFarmland(self, land: List[List[int]]) -> List[List[int]]:
        rows, cols = len(land), len(land[0])
        visit = set()

        def dfs(r, c, ans):
            if r < 0 or r == rows or c < 0 or c == cols or land[r][c] == 0 or (r, c) in visit:
                return []
            visit.add((r, c))

            group[0] = min(group[0], r)
            group[1] = min(group[1], c)
            group[2] = max(group[2], r)
            group[3] = max(group[3], c)

            dfs(r, c+1, group)
            dfs(r+1, c, group)

        result = []
        for r in range(rows):
            for c in range(cols):
                if land[r][c] == 1 and (r, c) not in visit:
                    group = [r, c, r, c]
                    dfs(r, c, group)
                    result.append(group)
                    
        return result
```

- [675. Cut Off Trees for Golf Event](https://leetcode.com/problems/cut-off-trees-for-golf-event/description/)

![alt-text](./675.png)

```python
class Solution:
    def cutOffTree(self, forest: List[List[int]]) -> int:
        trees = []
        heapq.heapify(trees)
        m = len(forest)
        n = len(forest[0])
        
        for i in range(m):
            for j in range(n):
                if forest[i][j]>1:
                    heapq.heappush(trees,(forest[i][j],i,j))
                    
        curr = (0,0,0)
        res = 0
        while trees:
            queue = [curr]
            visited = set([(curr[0],curr[1])])
            find = False
            for i,j,d in queue:
                if (i,j) == (trees[0][1],trees[0][2]):
                    forest[i][j] = 1
                    res += d
                    curr = (i,j,0)
                    heapq.heappop(trees)
                    find = True
                    break
                else:
                    for di,dj in [(0,1),(1,0),(0,-1),(-1,0)]:
                        if 0<=i+di<m and 0<=j+dj<n and forest[i+di][j+dj] > 0 and (i+di,j+dj) not in visited:
                            visited.add((i+di,j+dj))
                            queue.append((i+di,j+dj,d+1))
            if not find:
                return -1
        return res
```
