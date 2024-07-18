- [28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)

![alt text](images/28.png)

```python
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        n = len(needle)

        for i in range(len(haystack)):
            if needle == haystack[i: i+n]:
                return i

        return -1
```

- [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/description)

![alt text](images/214.png)

```python
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        t = s[::-1]

        for i in range(len(t)):
            if s.startswith(t[i:]):
                return t[:i] + s

        return t + s
```
