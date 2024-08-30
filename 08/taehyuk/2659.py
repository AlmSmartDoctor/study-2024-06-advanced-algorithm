class FenwickTree:
    def __init__(self, size):
        self.size = size
        self.tree = [0 for _ in range(size + 1)]
    
    def add(self, pos, val):
        while pos <= self.size:
            self.tree[pos] += val
            pos += pos & -pos
    
    def sum(self, pos):
        ret = 0
        while pos > 0:
            ret += self.tree[pos]
            pos &= (pos - 1)
        return ret

class Solution:
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:
        n = len(nums)
        tree = FenwickTree(n)
        
        positions = {}
        for i, num in enumerate(nums):
            positions[num] = i + 1

        for i in range(1, n + 1):
            tree.add(i, 1)
        
        sortedNums = sorted(nums)
        criteria = 1 
        
        result = 0
        for num in sortedNums:
            pos = positions[num]
            if pos >= criteria:
                result += tree.sum(pos) - tree.sum(criteria - 1)
            else:
                result += tree.sum(n) - tree.sum(criteria - 1) 
                result += tree.sum(pos)

            tree.add(pos, -1)
            criteria = pos % n + 1
        
        return result