function maxSubArray(nums: number[]): number {
    let maxSum = Number.MIN_SAFE_INTEGER
    let curSum = 0;
    for(let i = 0; i < nums.length; i++) {
        curSum += nums[i];
        maxSum = Math.max(curSum, maxSum);
        if (curSum < 0) {
            curSum = 0;
        }
    }
    return maxSum;
};