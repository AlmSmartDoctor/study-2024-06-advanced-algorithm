class Solution(object):
    def maxMidArray(self, nums, left, mid, right):
        total = 0
        left_sum = -1e9
        for i in range(mid, left - 1, -1):
            total += nums[i]
            if total > left_sum:
                left_sum = total

        total = 0
        right_sum = -1e9
        for i in range(mid + 1, right + 1):
            total += nums[i]
            if total > right_sum:
                right_sum = total

        return left_sum + right_sum

    def maxSubArrayHelper(self, nums, left, right):
        if left == right:
            return nums[left]

        mid = (left + right) // 2

        left_max = self.maxSubArrayHelper(nums, left, mid)
        right_max = self.maxSubArrayHelper(nums, mid + 1, right)
        mid_max = self.maxMidArray(nums, left, mid, right)

        return max(left_max, right_max, mid_max)

    def maxSubArray(self, nums):
        if not nums:
            return 0
        return self.maxSubArrayHelper(nums, 0, len(nums) - 1)