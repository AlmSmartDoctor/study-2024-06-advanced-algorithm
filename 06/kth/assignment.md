28. Find the Index of the First Occurrence in a String

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
