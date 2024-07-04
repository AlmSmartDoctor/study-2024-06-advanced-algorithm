function minimumAverageDifference(nums: number[]): number {
    let ans = 0, minDiff = Infinity, partialSum = 0;

    const total = nums.reduce((sum, n) => sum + n, 0);

    for(let i = 0, n = nums.length; i < n; i++) {
        partialSum += nums[i];

        const rightSum = total - partialSum;
        const leftAvg = Math.floor(partialSum / (i + 1));
        const rightAvg = Math.floor(rightSum / ((i === n - 1) ? 1 : n - i - 1));
        const diff = Math.abs(leftAvg - rightAvg);

        if (diff < minDiff) {
            minDiff = diff;
            ans = i;
        }
    }

    return ans;
};