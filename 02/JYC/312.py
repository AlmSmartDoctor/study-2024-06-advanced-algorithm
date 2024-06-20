class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        nums = [1, *nums, 1]
        cache = [[0] * len(nums) for _ in range(len(nums))]
        
        for length in range(2, len(nums)): 
            for left in range(0, len(nums) - length):
                right = left + length  
                for k in range(left + 1, right):
                    cache[left][right] = max(cache[left][right], cache[left][k] + nums[left] * nums[k] * nums[right] + cache[k][right])
        
        return cache[0][len(nums)-1]
        