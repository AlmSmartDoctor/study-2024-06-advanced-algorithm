/**
 * @param {number[]} nums
 * @return {number}
 */
var maxOperations = function(nums) {
        const n = nums.length;
    const dp = Array.from({ length: n }, () => new Array(n).fill(undefined));

    const find = (l, r, sum) => {
        if (r - l < 1) return 0;
        if (dp[l][r] !== undefined) return dp[l][r];

        let ret = 0;

        if (nums[l] + nums[l + 1] === sum) ret = Math.max(ret, 1 + find(l + 2, r, sum));
        if (nums[l] + nums[r] === sum) ret = Math.max(ret, 1 + find(l + 1, r - 1, sum));
        if (nums[r - 1] + nums[r] === sum) ret = Math.max(ret, 1 + find(l, r - 2, sum));

        dp[l][r] = ret;
        return ret;
    };

    return 1 + Math.max(
        find(2, n - 1, nums[0] + nums[1]),
        find(1, n - 2, nums[0] + nums[n - 1]),
        find(0, n - 3, nums[n - 2] + nums[n - 1])
    );
};
