use std::collections::HashMap;

struct Solution {}

impl Solution {
    pub fn count_operations_to_empty_array(nums: Vec<i32>) -> i64 {
        let mut arr = nums.clone();
        let mut map = HashMap::new();
        let n = nums.len() as i64;
        let mut ans = n;
        
        for (i, &num) in nums.iter().enumerate() {
            map.insert(num, i);
        }
        
        arr.sort();
        for i in 1..arr.len() {
            if map[&arr[i]] < map[&arr[i - 1]] { 
                ans += n - i as i64;
            }
        }
        
        ans
    }
}