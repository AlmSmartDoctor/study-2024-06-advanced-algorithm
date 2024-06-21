class Solution {
   public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        return max({operation(nums, 0, n - 1, nums[0] + nums[1]),
                    operation(nums, 0, n - 1, nums[n - 1] + nums[n - 2]),
                    operation(nums, 0, n - 1, nums[0] + nums[n - 1])});
    }

   private:
    unordered_map<string, int> mem;

    int operation(const vector<int>& nums, int i, int j, int score) {
        if (i >= j) return 0;

        string hash_key = hash(i, j, score);
        if (mem.find(hash_key) != mem.end()) return mem[hash_key];

        int delete_first_two = (nums[i] + nums[i + 1] == score)
                                   ? 1 + operation(nums, i + 2, j, score)
                                   : 0;
        int delete_last_two = (nums[j] + nums[j - 1] == score)
                                  ? 1 + operation(nums, i, j - 2, score)
                                  : 0;
        int delete_first_and_last =
            (nums[i] + nums[j] == score)
                ? 1 + operation(nums, i + 1, j - 1, score)
                : 0;

        return mem[hash_key] = max(
                   {delete_first_two, delete_last_two, delete_first_and_last});
    }

    string hash(int i, int j, int score) {
        return to_string(i) + "-" + to_string(j) + "-" + to_string(score);
    }
};
