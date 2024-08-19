use std::collections::{ HashSet, VecDeque };

struct Solution;

impl Solution {
    pub fn num_squares(n: i32) -> i32 {
        let mut hs = HashSet::new();
        let mut cnt = 0;
        let mut q = VecDeque::from([vec![0]]);
        while !q.is_empty() {
            cnt += 1;
            let prevSquares = q.pop_front().unwrap();
            for i in 1..=100 {
                if i * i > n {
                    break;
                }
                for prev in &prevSquares {
                    let square = i * i + prev;
                    if square == n {
                        return cnt;
                    }
                    if square > n {
                        continue;
                    }
                    if hs.get(&square) == None {
                        if q.is_empty() {
                            q.push_back(vec![square]);
                        } else {
                            if !q[0].contains(&square) {
                                q[0].push(square);
                            }
                        }
                        hs.insert(square);
                    }
                }
            }
        }
        cnt
    }
}
