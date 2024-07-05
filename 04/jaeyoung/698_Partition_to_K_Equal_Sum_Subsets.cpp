class Solution {
   public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (int num : nums) sum += num;
        if (sum % k != 0) return false;

        unordered_map<int, bool> memo;
        int mask = 0;
        return recursion(nums, k, sum / k, 0, 0, mask, memo);
    }

    bool recursion(vector<int>& nums, int k, int target, int start, int curSum,
                   int& mask, unordered_map<int, bool>& memo) {
        if (k == 1) return true;

        if (curSum > target) return false;

        if (memo.find(mask) != memo.end()) return memo[mask];

        if (curSum == target)
            return memo[mask] =
                       recursion(nums, k - 1, target, 0, 0, mask, memo);

        for (int i = start; i < nums.size(); i++) {
            if ((mask & (1 << i)) != 0) continue;
            mask |= (1 << i);

            if (recursion(nums, k, target, i + 1, curSum + nums[i], mask, memo))
                return memo[mask] = true;
            mask &= ~(1 << i);
        }

        return memo[mask] = false;
    }
};