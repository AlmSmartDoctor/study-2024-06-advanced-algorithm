- [337. House Robber III](https://leetcode.com/problems/house-robber-iii/description/)

![alt text](images/337.png)

```python
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     val: number
 *     left: TreeNode | null
 *     right: TreeNode | null
 *     constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.left = (left===undefined ? null : left)
 *         this.right = (right===undefined ? null : right)
 *     }
 * }
 */

function rob(root: TreeNode | null): number {
    const memory = new Array(10**4);

    function getMaxMoney(root: TreeNode | null): number{
        if(!root) return 0

        if(root.val < 0) return -root.val-1;

        const includeRootMaxMoney = root.val + getMaxMoney(root.left?.left) + getMaxMoney(root.left?.right) + getMaxMoney(root.right?.left) + getMaxMoney(root.right?.right);

        const excludeRootMaxMoney = getMaxMoney(root.left) + getMaxMoney(root.right);

        const maxMoney = includeRootMaxMoney > excludeRootMaxMoney ? includeRootMaxMoney : excludeRootMaxMoney;

        root.val = -maxMoney-1;

        return maxMoney;
    }

    return getMaxMoney(root);
};
```

- [1377. Frog Position After T Seconds](https://leetcode.com/problems/frog-position-after-t-seconds/description/)

![alt text](images/1377.png)

```javascript
class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        answer = 1

        children_list = [[] for i in range((n+1))]

        children_count_list = [0] * (n+1)
        parent_list = [0] * (n+1)
        depth_list = [0] * (n+1)

        for edge in edges:
            children_list[edge[0]].append(edge[1])
            children_list[edge[1]].append(edge[0])

        stack = [1]

        while stack:
            parent = stack.pop()

            for child in children_list[parent]:
                if children_count_list[child]:
                    continue

                children_count_list[parent] += 1
                parent_list[child] = parent
                depth_list[child] = depth_list[parent]+1

                stack.append(child)

        cur = target

        while parent_list[cur]:
            parent = parent_list[cur]

            answer /= children_count_list[parent]

            cur = parent

        return answer if t == depth_list[target] or (t > depth_list[target] and not children_count_list[target]) else 0
```
