from collections import deque
from typing import List

class Solution:
    def numSquares(self, n: int) -> int:
        squares = []
        i = 1
        while i * i <= n:
            squares.append(i * i)
            i += 1
        
        q = deque([(n, 0)])
        visited = set()
        
        while q:
            remainder, steps = q.popleft()
            
            for square in squares:
                remaining = remainder - square
                if remaining == 0:
                    return steps + 1
                if remaining > 0 and remaining not in visited:
                    visited.add(remaining)
                    q.append((remaining, steps + 1))
        
        return -1
