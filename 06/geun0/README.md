[28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)

![alt text](images/214.png)

```javascript
/**
 * @param {string} s
 * @return {string}
 */

function isPalindrome(s, endIndex) {
  let left = 0;
  let right = endIndex;

  while (left <= right) {
    if (s[left] !== s[right]) return false;

    left += 1;
    right -= 1;
  }

  return true;
}

function shortestPalindrome(s) {
  for (let i = s.length - 1; i >= 0; i--) {
    if (isPalindrome(s, i))
      return (
        s
          .slice(i + 1)
          .split('')
          .reverse()
          .join('') + s
      );
  }
  return '';
}
```

[214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/description/)

![alt text](images/28.png)

```python
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        table = [0] * len(needle)

        pidx = 0
        for idx in range(1, len(needle)):
            while pidx > 0 and needle[pidx] != needle[idx]:
                pidx = table[pidx-1]

            if needle[pidx] == needle[idx]:
                pidx += 1
                table[idx] = pidx

        pidx = 0
        for idx in range(len(haystack)):
            while pidx > 0 and haystack[idx] != needle[pidx]:
                pidx = table[pidx-1]
            if haystack[idx] == needle[pidx]:
                if pidx == len(needle)-1:
                   return idx-len(needle)+1
                else:
                    pidx += 1

        return -1
```
