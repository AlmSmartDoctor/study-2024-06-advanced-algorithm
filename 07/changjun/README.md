- [337. House Robber III](https://leetcode.com/problems/house-robber-iii/description/)

![alt text](images/337.png)

```python
"""
[general case]

f(n) = max(n.val + f(n.left) + f(n.right), max(n.left) + max(n.right))

every step needs to store for taking the value, and not taking the value

[base case]

[0, 0]

"""
class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:

        def f(node):
            # base case
            if not node:
                return [0, 0]

            left = f(node.left)
            right = f(node.right)

            # 0 index is when we include the current node value
            # 1 index is when we not include the current node value
            return [node.val + left[1] + right[1], max(left) + max(right)]

        result = max(f(root))
        return result
```

```python
"""
[description]

# nodes in subtree >= 3 => return product of the top 3 big costs
# nodes in subtree < 3 => return 1
return the array of the above values in an array

for all node,

[general case]



[base case]

if size < 3:
    return 1


"""

class Solution:
    def placedCoins(self, edges: List[List[int]], cost: List[int]) -> List[int]:
        # will create adjaceny list for the undirected graph
        graph = defaultdict(list)

        for start, end in edges:
            graph[start].append(end)
            graph[end].append(start)

        n = len(cost)
        coins = [0] * n
        # we will check the visited coins when we dfs from the start node
        visited = [False] * n

        def dfs(node):
            visited[node] = True
            subtree_size = 1
            max_costs = []

            for neighbor in graph[node]:
                if not visited[neighbor]:
                    size, neighbor_costs = dfs(neighbor)
                    subtree_size += size
                    max_costs.extend(neighbor_costs)

            max_costs.append(cost[node])
            max_costs.sort(reverse=True)

            if subtree_size < 3:
                coins[node] = 1
            else:
                if max_costs[0] * max_costs[1] * max_costs[2] > max_costs[0] * max_costs[-1] * max_costs[-2]:
                    max_costs = [max_costs[0], max_costs[1], max_costs[2]]
                else:
                    max_costs = [max_costs[0], max_costs[-1], max_costs[-2]]

                max_product = max_costs[0] * max_costs[1] * max_costs[2]
                coins[node] = max(0, max_product)

            return subtree_size, max_costs

        dfs(0)
        return coins
```
