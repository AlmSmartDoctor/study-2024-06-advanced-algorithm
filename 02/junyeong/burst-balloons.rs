use std::{ cmp, collections::HashMap };

struct Solution {}

impl Solution {
    pub fn max_coins(nums: Vec<i32>) -> i32 {
        let mut nums_cpy = nums.clone();
        nums_cpy.insert(0, 1);
        nums_cpy.push(1);
        let mut map: HashMap<(i32, i32), i32> = HashMap::new();
        Self::sub_max_coins(&nums_cpy, 1, (nums_cpy.len() as i32) - 2, &mut map)
    }

    pub fn sub_max_coins(
        nums: &Vec<i32>,
        left: i32,
        right: i32,
        map: &mut HashMap<(i32, i32), i32>
    ) -> i32 {
        if left > right {
            return 0;
        }

        if let Some(value) = map.get(&(left, right)) {
            return *value;
        }

        let mut sum = 0;
        for idx in left..=right {
            let mut coins =
                nums[(left as usize) - 1] * nums[idx as usize] * nums[(right as usize) + 1];
            coins +=
                Self::sub_max_coins(nums, left, idx - 1, map) +
                Self::sub_max_coins(nums, idx + 1, right, map);
            sum = cmp::max(sum, coins);
        }
        map.insert((left, right), sum);
        sum
    }
}
