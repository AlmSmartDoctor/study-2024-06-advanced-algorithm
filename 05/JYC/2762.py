class Solution:
    def continuousSubarrays(self, nums: List[int]) -> int:
        min_deque = deque()
        max_deque = deque()
        count = 0
        left = 0

        for right, num in enumerate(nums):
            while min_deque and nums[min_deque[-1]] >= num:
                min_deque.pop()
            while max_deque and nums[max_deque[-1]] <= num:
                max_deque.pop()

            min_deque.append(right)
            max_deque.append(right)

            while nums[max_deque[0]] - nums[min_deque[0]] > 2:
                left += 1
                if min_deque[0] < left:
                    min_deque.popleft()
                if max_deque[0] < left:
                    max_deque.popleft()

            count += right - left + 1

        return count