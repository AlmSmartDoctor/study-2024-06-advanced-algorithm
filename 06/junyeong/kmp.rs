impl Solution {
    pub fn str_str(haystack: String, needle: String) -> i32 {
        let s: Vec<u8> = needle.bytes().chain(",".bytes()).chain(haystack.bytes()).collect();

        let mut pi = vec![0; s.len()];

        for i in 1..s.len() {
            let mut j = pi[i - 1];
            while j > 0 && s[j] != s[i] {
                j = pi[j - 1];
            }
            if s[i] == s[j] {
                j += 1;
            }
            pi[i] = j;
        }

        for i in needle.len() + 1..s.len() {
            if pi[i] == needle.len() {
                return (i - needle.len() * 2) as i32;
            }
        }
        return -1;
    }
}
