use std::{ collections::{ HashMap, HashSet }, hash::Hash };

struct UnionFind<T> {
    parent_map: HashMap<T, T>,
    rank_map: HashMap<T, usize>,
}

impl<T> UnionFind<T> where T: Eq + Hash + Copy {
    pub fn new() -> Self {
        Self {
            parent_map: HashMap::new(),
            rank_map: HashMap::new(),
        }
    }
    pub fn reset(&mut self) {
        self.parent_map.clear();
        self.rank_map.clear();
    }
    pub fn find(&mut self, node: T) -> T {
        if let Some(parent) = self.parent_map.get(&node) {
            let parent = self.find(*parent);
            self.parent_map.insert(node, parent);
            return parent;
        } else {
            return node;
        }
    }
    pub fn union(&mut self, node1: T, node2: T) -> bool {
        let parent1 = self.find(node1);
        let parent2 = self.find(node2);
        if parent1 == parent2 {
            return false;
        }
        let rank1 = self.rank_map.get(&parent1).unwrap_or(&0);
        let rank2 = self.rank_map.get(&parent2).unwrap_or(&0);

        if rank1 < rank2 {
            self.parent_map.insert(parent1, parent2);
        } else if rank1 > rank2 {
            self.parent_map.insert(parent2, parent1);
        } else {
            self.parent_map.insert(parent1, parent2);
            *self.rank_map.entry(parent2).or_insert(0) += 1;
        }

        true
    }
}

struct Solution {}

impl Solution {
    pub fn find_critical_and_pseudo_critical_edges(n: i32, edges: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut edge_list = vec![];
        for (idx, edge) in edges.iter().enumerate() {
            edge_list.push((edge[2], edge[1], edge[0], idx));
        }
        edge_list.sort_by_key(|edge| edge.0);

        let mut min = 0;
        let mut union_find = UnionFind::new();
        let mut mst_edge_set = HashSet::new();

        for (weight, from, to, edge_idx) in edge_list.iter() {
            if union_find.union(from, to) {
                min += weight;
                mst_edge_set.insert(edge_idx);
            }
        }

        let mut include_edge_list = vec![];

        for (include_weight, include_from, include_to, include_edge_idx) in edge_list.iter() {
            if mst_edge_set.contains(include_edge_idx) {
                continue;
            }

            include_edge_list.clear();
            include_edge_list.push(include_edge_idx);

            union_find.reset();
            union_find.union(&include_from, &include_to);

            let mut total_weight = *include_weight;
            for (weight, from, to, edge_idx) in edge_list.iter() {
                if include_edge_idx != edge_idx && union_find.union(&from, &to) {
                    total_weight += weight;
                    include_edge_list.push(edge_idx);
                }
            }

            if total_weight == min {
                mst_edge_set.extend(include_edge_list.drain(..));
            }
        }

        let mut critical = vec![];
        let mut pseudo_critical = vec![];

        for exclude_edge in mst_edge_set {
            union_find.reset();

            let mut total_weight = 0;
            for (cost, from, to, edge_idx) in edge_list.iter() {
                if exclude_edge == edge_idx {
                    continue;
                }

                if union_find.union(from, to) {
                    total_weight += cost;
                }
            }

            if total_weight == min {
                pseudo_critical.push(*exclude_edge as i32);
            } else {
                critical.push(*exclude_edge as i32);
            }
        }

        vec![critical, pseudo_critical]
    }
}
