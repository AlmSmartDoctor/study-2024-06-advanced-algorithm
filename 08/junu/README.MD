- [2659. Make Array Empty](https://leetcode.com/problems/make-array-empty/description/)

![alt text](images/2659.png)

```python
from heapq import heapify, heappop
from typing import List

class Solution:
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:
        n = len(nums)
        tree = [0]*(n+1)
        
        def update(tree, i, delta):
            while i <= n:
                tree[i] += delta
                i += i&-i
        
        def query(tree, i):
            res = 0
            while i > 0:
                res += tree[i]
                i -= i&-i
            return res
        
        for i in range(n):
            update(tree, i+1, 1)
        
        heap = [(num, i) for i, num in enumerate(nums)]
        heapify(heap)
        i = 0
        res = 0
        while heap:
            v, j = heappop(heap)
            if j+1 > i:
                res +=  query(tree, j+1) - query(tree, i) 
            else:
                res += query(tree, n) - query(tree, i) + query(tree, j+1)
            update(tree, j+1, -1)
            i = j + 1
        return res
```