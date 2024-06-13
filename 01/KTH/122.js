/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    return prices.reduce((sum, currentPrice, index, arr) => {
        if (index > 0 && arr[index - 1] < currentPrice) {
            sum += currentPrice - arr[index - 1];
        }
        return sum;
    }, 0);
};
