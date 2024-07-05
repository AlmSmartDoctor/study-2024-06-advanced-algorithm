class Solution {
   public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> decrease(n, 1);
        for (int i = 2; i < n; i++)
            if (nums[i - 1] <= nums[i - 2]) decrease[i] = decrease[i - 1] + 1;

        vector<int> increase(n, 1);
        for (int i = n - 3; i > 0; i--)
            if (nums[i + 1] <= nums[i + 2]) increase[i] = increase[i + 1] + 1;

        vector<int> ans;
        for (int i = k; i < n - k; i++)
            if (decrease[i] >= k && increase[i] >= k) ans.push_back(i);

        return ans;
    }
};