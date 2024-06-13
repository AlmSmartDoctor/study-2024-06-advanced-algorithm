class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        def remain(i):
            return gas[i] - cost[i]
        
        if sum(gas) < sum(cost):
            return -1
        
        tank = 0
        ind = 0
        
        for i in range(len(gas)):
            newTank = tank + remain(i)
            if newTank < 0:
                ind = i + 1
                tank = 0
            else:
                tank = newTank
        return ind
