class Solution:
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:   
        total = sum(nums)
        if total % k != 0:
            return False

        target = total // k
        n = len(nums)
        memo = {}

        def canPartition(mask, k, current_sum):
            if k == 1:
                return True
            if current_sum == target:
                res = canPartition(mask, k - 1, 0)
                memo[mask] = res
                return res
            if mask in memo:
                return memo[mask]

            for i in range(n):
                if not (mask & (1 << i)) and current_sum + nums[i] <= target:
                    if canPartition(mask | (1 << i), k, current_sum + nums[i]):
                        memo[mask] = True
                        return True
            
            memo[mask] = False
            return False

        return canPartition(0, k, 0)

