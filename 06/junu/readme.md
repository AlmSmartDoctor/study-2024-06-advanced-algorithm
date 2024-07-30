<img width="674" alt="스크린샷 2024-07-18 오후 9 58 33" src="https://github.com/user-attachments/assets/120639e6-0663-4896-9ea4-749861c01870">

```python
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        if not needle:
            return 0
        
        table = self.KMP_table(needle)
        pidx = 0
        for idx in range(len(haystack)):
            while pidx > 0 and haystack[idx] != needle[pidx]:
                pidx = table[pidx-1]
            if haystack[idx] == needle[pidx]:
                if pidx == len(needle) - 1:
                    return idx - len(needle) + 1
                else:
                    pidx += 1
        
        return -1

    def KMP_table(self, pattern):
        lp = len(pattern)
        tb = [0 for _ in range(lp)]
        
        pidx = 0
        for idx in range(1, lp): 
            while pidx > 0 and pattern[idx] != pattern[pidx]:
                pidx = tb[pidx-1]
            
            if pattern[idx] == pattern[pidx]:
                pidx += 1
                tb[idx] = pidx
        
        return tb
```

<img width="678" alt="스크린샷 2024-07-18 오후 10 08 30" src="https://github.com/user-attachments/assets/25e7005e-ed31-4e8b-828b-a3ba6bb0e668">

```python
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        if not s:
            return s
        
        rev_s = s[::-1]
        new_s = s + '#' + rev_s
        kmp_table = self.KMP_table(new_s)
        to_add = rev_s[:len(s) - kmp_table[-1]]
        return to_add + s
    
    def KMP_table(self, pattern: str):
        lp = len(pattern)
        table = [0] * lp
        
        pidx = 0
        for idx in range(1, lp):
            while pidx > 0 and pattern[idx] != pattern[pidx]:
                pidx = table[pidx - 1]
            if pattern[idx] == pattern[pidx]:
                pidx += 1
                table[idx] = pidx
        return table
```
