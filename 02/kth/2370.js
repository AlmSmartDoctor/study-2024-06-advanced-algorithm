/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var longestIdealString = function(s, k) {
  const dp = new Array(128).fill(0);
  let maxLen = 0;

  for (const char of s) {
    const ascii = char.charCodeAt(0);
    let maxForChar = 0;

    const start = Math.max(0, ascii - k);
    const end = Math.min(127, ascii + k);

    for (let i = start; i <= end; i++) {
      maxForChar = Math.max(maxForChar, dp[i]);
    }

    dp[ascii] = maxForChar + 1; 
    maxLen = Math.max(maxLen, dp[ascii]); 
  }

  return maxLen;
};
