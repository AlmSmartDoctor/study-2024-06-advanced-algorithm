class Solution {
public:
    int searchSquare(int n, vector<int>& memo) {
        int maxSquare = (int)sqrt(n);
        if (pow(maxSquare, 2) == n) return 1;
        if (memo[n - 1] > 0) return memo[n - 1];
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < maxSquare; i++) {
            pq.push(searchSquare(n - pow(i + 1, 2), memo));
        }
        memo[n - 1] = pq.top() + 1;
        return memo[n - 1];
    }

    int numSquares(int n) {
        vector<int> memo(n);
        return searchSquare(n, memo);
    }
};