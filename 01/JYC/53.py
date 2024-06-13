class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        summ = nums[0]
        curr = 0

        for num in nums:
            curr = max(num, curr + num)
            summ = max(summ, curr)
            
        return summ

