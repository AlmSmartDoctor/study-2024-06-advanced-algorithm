function maxOperations(nums: number[]): number {
    const dp = Array.from({ length: nums.length }, () => new Array(nums.length));

    const find = (l, r, sum) => {
        if (r - l < 1) return 0;

        if (dp[l][r] !== undefined) return dp[l][r];

        let ret = 0;

        if (nums[l] + nums[l+1] === sum) ret = Math.max(ret, 1 + find(l + 2, r, sum));
        if (nums[l] + nums[r] === sum) ret = Math.max(ret, 1 + find(l + 1, r - 1, sum));
        if (nums[r - 1] + nums[r] === sum) ret = Math.max(ret, 1 + find(l, r - 2, sum));

        return dp[l][r] = ret;
    }

    return 1 + Math.max(
        find(2, nums.length - 1, nums[0] + nums[1]),
        find(1, nums.length - 2, nums[0] + nums[nums.length - 1]),
        find(0, nums.length - 3, nums[nums.length - 2] + nums[nums.length - 1])
    )
};