class Solution:
    def minimumAverageDifference(self, nums: List[int]) -> int:

        def absdif():
            if rlen == 0:
                return abs(lsumm // llen)
            return abs((lsumm // llen) - (rsumm // rlen))

        if len(nums) == 1:
            return 0
        
        left = [nums[0]]
        right = nums[1:]

        lsumm = sum(left)
        rsumm = sum(right)
        llen = 1
        rlen = len(nums) - 1

        currDiff = absdif()
        currIndex = 0

        for i in range(1, len(nums)):
            lsumm += nums[i]
            llen += 1

            rsumm -= nums[i]
            rlen -= 1

            if currDiff > absdif():
                currDiff = absdif()
                currIndex = i

        return currIndex
