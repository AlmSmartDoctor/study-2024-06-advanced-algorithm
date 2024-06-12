/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function (nums) {
    return getSubs(nums)
};

const getSubs = (subNums) => {
    const middle = Math.floor(subNums.length / 2)
    if (middle === 0) return subNums[0]
    const leftNums = subNums.slice(
        0, middle
    )
    const rightNums = subNums.slice(
        subNums.length === 3 ? middle + 1 : middle, subNums.length
    )
    const middleSum = getMiddleSum(subNums, middle)

    if (leftNums.length === 1 && rightNums.length === 1) {
        return Math.max(leftNums[0], rightNums[0], middleSum)
    } else {
        return Math.max(getSubs(leftNums), getSubs(rightNums), middleSum)
    }
}

const getMiddleSum = (subNums, middle) => {
    let leftMaxSum = 0
    let rightMaxSum = 0

    let sum = 0;
    for (let i = middle - 1; i >= 0; i--) {
        sum += subNums[i]
        leftMaxSum = Math.max(sum, leftMaxSum)
    }

    sum = 0;
    for (let i = middle + 1; i <= subNums.length - 1; i++) {
        sum += subNums[i]
        rightMaxSum = Math.max(sum, rightMaxSum)
    }

    return leftMaxSum + rightMaxSum + subNums[middle];
}
