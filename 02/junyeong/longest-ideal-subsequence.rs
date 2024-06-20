use std::collections::HashMap;

struct Solution {}

impl Solution {
    pub fn longest_ideal_string(s: String, k: i32) -> i32 {
        let mut map: HashMap<u8, i32> = HashMap::new();
        for byte in s.bytes() {
            let mut len = 1;
            for satisfied_byte in byte - (k as u8)..=byte + (k as u8) {
                len = len.max(*map.get(&satisfied_byte).unwrap_or(&0) + 1);
            }
            map.insert(byte, len);
        }
        *map.values().max().unwrap_or(&1)
    }
}
