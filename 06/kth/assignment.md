**28. Find the Index of the First Occurrence in a String**

![image](https://github.com/user-attachments/assets/721efc98-05b0-430e-b546-648ca7280a4e)

```
var strStr = function (haystack, needle) {
    let i = 0
    let j = -1
    let lps = [j]

    while (i < needle.length - 1) {
        if (j === -1 || needle[i] === needle[j]) {
            i+=1
            j+=1
            lps[i] = j
        } else j = lps[j]
    }

    i = 0
    j = 0
    while (i < haystack.length && j < needle.length) {
        if (haystack[i] === needle[j]) {
            i+=1
            j+=1
        } else {
            j = lps[j]
            if (j < 0) {
                i+=1
                j+=1
            }
        }
    }

    if (j === needle.length) {
        return i - j
    }
    
    return -1
}
```

---
**214. Shortest Palindrome**
     
![image](https://github.com/user-attachments/assets/71298342-0377-4e5c-86ad-3200a281fe44)

```
var shortestPalindrome = function (s) {
    const reverseS = s.split('').reverse().join('');
    let combined = s + '*' + reverseS;

    let kmp = new Array(combined.length).fill(0);
    for (let i = 1, j = 0; i < combined.length; ) {
        if (combined[i] === combined[j]) {
            kmp[i++] = ++j;
        } else if (j > 0) {
            j = kmp[j - 1];
        } else {
            kmp[i++] = 0;
        }
    }

    return reverseS.substring(0, s.length - kmp[combined.length - 1]) + s;
};
```
