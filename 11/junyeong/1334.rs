struct Solution {}

impl Solution {
    pub fn find_the_city(n: i32, edges: Vec<Vec<i32>>, distance_threshold: i32) -> i32 {
        let mut distance_memo = vec![vec![1e4 as i32 + 1; n as usize];n as usize];
        for i in 0..n as usize {
            distance_memo[i][i] = 0;
        }

        for edge in edges {
            let from = edge[0] as usize;
            let to = edge[1] as usize;
            let weight = edge[2];
            distance_memo[from][to] = weight;
            distance_memo[to][from] = weight;
        }

        for bridge in 0..n as usize {
            for from in 0..n as usize {
                for to in 0..n as usize {
                    distance_memo[from][to] = distance_memo[from][to].min(
                        distance_memo[from][bridge] + distance_memo[bridge][to]
                    );
                }
            }
        }

        let mut ans = 0;
        let mut least_move_count = n;
        for from in 0..n {
            let mut move_count = 0;
            for to in 0..n {
                if from != to && distance_memo[from as usize][to as usize] <= distance_threshold {
                    move_count += 1;
                }
            }
            if move_count <= least_move_count {
                least_move_count = move_count;
                ans = from;
            }
        }
        ans
    }
}
