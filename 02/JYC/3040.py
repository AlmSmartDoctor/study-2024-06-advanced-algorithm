class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        if len(nums) < 2:
            return 0
        cache = {}

        def get_max_operations(i, j, score):
            if i >= j:
                return 0
            if (i, j, score) in cache:
                return cache[(i, j, score)]

            max_ops = 0

            if i + 1 <= j and nums[i] + nums[i + 1] == score:
                max_ops = max(max_ops, 1 + get_max_operations(i + 2, j, score))
            if j - 1 >= i and nums[j - 1] + nums[j] == score:
                max_ops = max(max_ops, 1 + get_max_operations(i, j - 2, score))
            if i < j and nums[i] + nums[j] == score:
                max_ops = max(max_ops, 1 + get_max_operations(i + 1, j - 1, score))

            cache[(i, j, score)] = max_ops
            return max_ops

        max_operations = 0
        for i in range(len(nums)):
            for j in range(i + 1, len(nums)):
                score = nums[i] + nums[j]
                max_operations = max(max_operations, get_max_operations(0, len(nums) - 1, score))

        return max_operations
