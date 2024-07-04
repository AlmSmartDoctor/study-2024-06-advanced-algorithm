impl Solution {
    pub fn can_partition_k_subsets(nums: Vec<i32>, k: i32) -> bool {
        let range = 1 << nums.len();
        let total: i32 = nums.iter().sum();
        if total % k != 0 {
            return false;
        }
        let target = total / k;

        let mut sums = vec![0; range];
        nums.clone().sort();
        let sorted = nums;
        let mut dp = vec![false; range];
        dp[0] = true;
        if *sorted.last().unwrap() > target {
            return false;
        }
        for cur in 0..range {
            if dp[cur] {
                for (idx, &num) in sorted.iter().enumerate() {
                    let next = cur | (1 << idx);
                    if cur == next {
                        continue;
                    }
                    if num <= target - (sums[cur] % target) {
                        dp[next] = true;
                        sums[next] = num + sums[cur];
                    } else {
                        break;
                    }
                }
            }
        }
        dp[range - 1]
    }
}
