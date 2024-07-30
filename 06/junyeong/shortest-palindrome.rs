impl Solution {
    pub fn shortest_palindrome(s: String) -> String {
        let reverse = s.chars().rev().collect::<String>();

        for i in 0..reverse.len() {
            if s.starts_with(&reverse[i..]) {
                return format!("{}{}", &reverse[..i], s);
            }
        }

        format!("{}", reverse + &s)
    }
}
