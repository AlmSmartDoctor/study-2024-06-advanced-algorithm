- [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/description/)

![alt text](images/224.png)

```python
class Solution:
    def calculate(self, s: str) -> int:
        stack = []

        s = f"({s})"

        for i in s:
            if i == ' ':
                continue
            elif i == ')':
                sum = 0
                num = 0

                while True:
                    p = stack.pop()

                    if p == '(':
                        sum += num
                        stack.append(sum)
                        break
                    elif p == '+':
                        sum += num
                        num = 0
                    elif p == '-':
                        sum -= num
                        num = 0
                    else:
                        num = int(p)
            elif i.isdecimal() and stack[-1].isdecimal():
                stack[-1] += i
            else:
                stack.append(i)

        return stack[0]
```

- [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/description/)

![alt text](images/295.png)

```python
# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()

from heapq import heappush as hpush, heappop as hpop

class MedianFinder:

    def __init__(self):
        self.maxHeap = []
        self.minHeap = []

    def addNum(self, num: int) -> None:
        if len(self.maxHeap) == len(self.minHeap):
            hpush(self.maxHeap, -num)
        else:
            hpush(self.minHeap, num)

        if self.minHeap and -self.maxHeap[0] > self.minHeap[0]:
            minPop = hpop(self.minHeap)
            maxPop = hpop(self.maxHeap)

            hpush(self.minHeap, -maxPop)
            hpush(self.maxHeap, -minPop)

    def findMedian(self) -> float:
        if len(self.maxHeap) == len(self.minHeap):
            return (self.minHeap[0]-self.maxHeap[0])/2
        else:
            return -self.maxHeap[0]

```
