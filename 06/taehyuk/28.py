class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        if not needle:
            return 0
        
        def getPartialMatch(N: str) -> list:
            m = len(N)
            pi = [0] * m
            j = 0 

            for i in range(1, m):
                while (j > 0 and N[i] != N[j]):
                    j = pi[j - 1]
                
                if N[i] == N[j]:
                    j += 1
                    pi[i] = j
                else:
                    pi[i] = 0
            
            return pi
        
        def searchSubstring(a: str, b: str) -> int:
            n = len(a)
            m = len(b)
            pi = getPartialMatch(b)
            j = 0

            for i in range(n):
                while (j > 0 and a[i] != b[j]):
                    j = pi[j - 1]

                if a[i] == b[j]:
                    j += 1
                
                if j == m:
                    return i - m + 1
            
            return -1
        
        return searchSubstring(haystack, needle)
