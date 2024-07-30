class Solution:
    def longestPrefix(self, s: str) -> str:
        def getPartialMatch(N: str) -> list:
            m = len(N)
            pi = [0] * m
            j = 0 

            for i in range(1, m):
                print(i, j, N[i], N[j])
                while (j > 0 and N[i] != N[j]):
                    print(j)
                    j = pi[j - 1]
                
                if N[i] == N[j]:
                    j += 1
                    pi[i] = j
                else:
                    pi[i] = 0
            
            return pi
        
        pi = getPartialMatch(s)
        result = pi[-1]
        
        return s[:result]
