class Solution {
   public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int length = 2; length < n; length++) {
            for (int left = 0; left < n - length; left++) {
                int right = left + length;
                for (int i = left + 1; i < right; i++) {
                    dp[left][right] = max(dp[left][right],
                                          nums[left] * nums[i] * nums[right] +
                                              dp[left][i] + dp[i][right]);
                }
            }
        }

        return dp[0][n - 1];
    }
};