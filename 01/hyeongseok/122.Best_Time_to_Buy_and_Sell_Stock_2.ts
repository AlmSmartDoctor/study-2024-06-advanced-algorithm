function maxProfit(prices: number[]): number {
    let totalProfit = 0;
    for(let i = 1; i < prices.length; i++) {
        if (prices[i] > prices[i-1]) {
            totalProfit += prices[i] - prices[i-1];
        }
    }
    return totalProfit;
};

// function maxProfit(prices: number[]): number {
//     let totalProfit = 0;
//     let curr = prices[0]; 
//     for(let i = 1; i < prices.length; i++) {
//         if (prices[i] > curr) {
//             totalProfit += prices[i] - curr;
//         }
//         curr = prices[i];
//     }
//     return totalProfit;
// }