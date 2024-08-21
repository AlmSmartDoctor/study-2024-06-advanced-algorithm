### 2360. Longest Cycle in a Graph

![image](https://github.com/user-attachments/assets/015ce305-cdcd-4093-a5e9-54bc8f76d8c5)


```cpp
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int ans = -1, time = 1;
        vector<int> visitedTime(edges.size());

        for (int i = 0; i < edges.size(); ++i) {
            if (visitedTime[i]) continue;
            
            const int startTime = time;
            int u = i;
            while (u != -1 && !visitedTime[u]) {
                visitedTime[u] = time++;
                u = edges[u];
            }
            if (u != -1 && visitedTime[u] >= startTime)
                ans = max(ans, time - visitedTime[u]);
        }

        return ans;
    }
};
```

<br/>

### 279. Perfect Squares

![image](https://github.com/user-attachments/assets/7a18274e-5fed-4f39-8d94-f491ddea308c)

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n);
        dp[0] = 0, dp[1] = 1;

        for (int i = 2; i <= n; ++i)
            for (int j = 1; j * j <= i; ++j)
                dp[i] = min(dp[i], dp[i - j * j] + 1);

        return dp[n];
    }
};
```
