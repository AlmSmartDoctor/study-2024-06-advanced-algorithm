function findRedundantConnection(edges: number[][]) {
  const l = edges.length;
  const parent: number[] = Array(l);

  for (let i = 1; i <= l; i++) {
    parent[i] = i;
  }

  const union = (u: number, v: number) => {
    u = find(u);
    v = find(v);
    if (u == v) return;
    parent[u] = v;
  };

  const find = (u: number): number => {
    if (u == parent[u]) {
      return u;
    }
    return find(parent[u]);
  };

  for (const edge of edges) {
    const [u, v] = edge;

    if (find(u) === find(v)) return edge;

    union(u, v);
  }
}
