struct UnionFind {
    parent: Vec<usize>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        Self {
            parent: (0..n).collect(),
        }
    }
    fn union(&mut self, x: usize, y: usize) {
        let x = self.find(x);
        let y = self.find(y);
        self.parent[y] = x;
    }
    fn find(&mut self, x: usize) -> usize {
        if x != self.parent[x] {
            self.parent[x] = self.find(self.parent[x]);
        }
        self.parent[x]
    }
}

struct Solution {}

impl Solution {
    pub fn find_redundant_connection(edges: Vec<Vec<i32>>) -> Vec<i32> {
        let mut unionFind = UnionFind::new(edges.len());
        for edge in edges {
            let n0 = (edge[0] - 1) as usize;
            let n1 = (edge[1] - 1) as usize;
            if unionFind.find(n0) == unionFind.find(n1) {
                return edge;
            }
            unionFind.union(n0, n1);
        }
        unreachable!()
    }
}
