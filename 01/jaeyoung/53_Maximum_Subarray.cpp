class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        const int INF = 1000000000;
        int max_sum = -INF, cur_sum = -INF;

        for (int num : nums) {
            cur_sum = max(num, cur_sum + num);
            max_sum = max(max_sum, cur_sum);
        }

        return max_sum;
    }
};