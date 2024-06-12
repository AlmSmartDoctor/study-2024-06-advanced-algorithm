/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function(nums) {
    return getSubs(nums, 0, nums.length - 1);
};

const getSubs = (subNums, left, right) => {
    if (left === right) {
        return subNums[left];
    }

    const middle = Math.floor((left + right) / 2);
    const leftSum = getSubs(subNums, left, middle);
    const rightSum = getSubs(subNums, middle + 1, right);
    const middleSum = getMiddleSum(subNums, left, middle, right);

    return Math.max(leftSum, rightSum, middleSum);
};

const getMiddleSum = (subNums, left, middle, right) => {
    let leftMaxSum = Number.NEGATIVE_INFINITY;
    let rightMaxSum = Number.NEGATIVE_INFINITY;

    let sum = 0;
    for (let i = middle; i >= left; i--) {
        sum += subNums[i];
        if (sum > leftMaxSum) {
            leftMaxSum = sum;
        }
    }

    sum = 0;
    for (let i = middle + 1; i <= right; i++) {
        sum += subNums[i];
        if (sum > rightMaxSum) {
            rightMaxSum = sum;
        }
    }

    return leftMaxSum + rightMaxSum;
};
