class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        total = 0
        current = prices[0]
        for i in range(1, len(prices)):
            if prices[i]- current > 0:
                total += prices[i] - current
                current = prices[i]
            else:
                current = min(current, prices[i])
        return total 