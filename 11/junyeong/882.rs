use std::collections::{ BinaryHeap, HashMap };

struct Solution {}

impl Solution {
    pub fn reachable_nodes(edges: Vec<Vec<i32>>, max_moves: i32, n: i32) -> i32 {
        let mut adjacent_list = vec![vec![]; n as usize];
        let mut subdivide_map = HashMap::new();

        for edge in edges {
            let from = edge[0] as usize;
            let to = edge[1] as usize;

            adjacent_list[from].push(to);
            adjacent_list[to].push(from);

            subdivide_map.insert((from.min(to), from.max(to)), edge[2] as usize);
        }

        let mut visited = vec![false; n as usize];
        let mut queue = BinaryHeap::new();
        queue.push((max_moves as usize, 0usize));

        let mut answer = 0;
        while let Some((remaining_moves, node)) = queue.pop() {
            if visited[node] {
                continue;
            }
            visited[node] = true;
            answer += 1;

            if remaining_moves == 0 {
                continue;
            }

            for &child in adjacent_list[node].iter() {
                let from = node.min(child);
                let to = node.max(child);

                if let Some(moves) = subdivide_map.get_mut(&(from, to)) {
                    let distance = *moves + 1;

                    if distance <= remaining_moves && !visited[child] {
                        queue.push((remaining_moves - distance, child));
                    }

                    answer += remaining_moves.min(*moves);
                    *moves -= remaining_moves.min(*moves);
                }
            }
        }

        answer as i32
    }
}
