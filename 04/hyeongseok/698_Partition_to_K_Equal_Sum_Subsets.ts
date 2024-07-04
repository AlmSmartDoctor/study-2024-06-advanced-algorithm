function canPartitionKSubsets(nums: number[], k: number): boolean {
    if (k === 0) return false;

    const subsetSum = nums.reduce((sum, cur) => sum + cur, 0) / k;

    if (!Number.isInteger(subsetSum)) return false;

    function dfs(startIdx: number, curSum: number, subsetNum: number) {
        if (curSum > subsetSum) return false;
        if (subsetNum === 1) return true;
        if (curSum === subsetSum) return dfs(0, 0, subsetNum - 1);

        for (let i = startIdx; i < nums.length; i++) {
            if (nums[i] > 0) {
                nums[i] *= -1;
                if (dfs(i + 1, curSum - nums[i], subsetNum)) {
                    return true;
                }
                nums[i] *= -1;
            }
        }

        return false;
    }

    return dfs(0, 0, k);
};