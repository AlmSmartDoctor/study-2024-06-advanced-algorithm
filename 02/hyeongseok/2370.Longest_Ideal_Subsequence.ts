function longestIdealString(s: string, k: number): number {
    let dp = new Array(26).fill(0)
    const charCodeA = 'a'.charCodeAt(0)

    for (let char of s) {
        let currIdx = char.charCodeAt(0) - charCodeA
        let longest = 1

        for(let prevIdx = 0; prevIdx < 26; prevIdx++) {
            if (Math.abs(prevIdx - currIdx) <= k) {
                longest = Math.max(longest, dp[prevIdx] + 1);
            }
        }
        dp[currIdx] = Math.max(dp[currIdx], longest)
    }

    return Math.max(...dp)
};