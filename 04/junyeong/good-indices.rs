impl Solution {
    pub fn good_indices(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let n = nums.len();
        let (mut non_increase, mut non_decrease) = (vec![0; n], vec![0; n]);

        for i in 1..n {
            non_increase[i] = 1;
            if i == 1 {
                continue;
            }
            if nums[i - 1] <= nums[i - 2] {
                non_increase[i] += non_increase[i - 1];
            }
        }

        for i in (0..n - 1).rev() {
            non_decrease[i] = 1;
            if i == n - 2 {
                continue;
            }
            if nums[i + 1] <= nums[i + 2] {
                non_decrease[i] += non_decrease[i + 1];
            }
        }

        let mut res = vec![];
        for i in 0..n {
            if non_decrease[i] < k || non_increase[i] < k {
                continue;
            }
            res.push(i as i32);
        }

        res
    }
}
