- [2659. Make Array Empty](https://leetcode.com/problems/make-array-empty/description/)

![alt text](images/2659.png)

```python
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n+1)

    def update(self, pos, val):
        while pos <= self.n:
            self.tree[pos] += val
            pos += pos & -pos

    def query(self, pos):
        sum = 0
        while pos:
            sum += self.tree[pos]
            pos -= pos & -pos
        return sum

class Solution:
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:
        n = len(nums)
        tree = FenwickTree(n)

        pos = {x:i+1 for i, x in enumerate(nums)}

        nums.sort()

        min_num_pos = pos[nums[0]]
        tree.update(min_num_pos,1)
        ans = min_num_pos

        for i in range(n-1):
            prev, cur = nums[i], nums[i+1]
            p1, p2 = pos[prev], pos[cur]

            if p1 < p2:
                ans += (p2-p1) - (tree.query(p2)-tree.query(p1))
            else:
                ans += (n-p1+p2) - (tree.query(n)-tree.query(p1)+tree.query(p2))

            tree.update(p2,1)

        return ans
```
