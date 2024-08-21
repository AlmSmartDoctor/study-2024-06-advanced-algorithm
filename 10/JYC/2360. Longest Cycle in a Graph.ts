function longestCycle(edges: number[]): number {
  const visited = new Array(edges.length).fill(false);
  let result = -1;

  const DFS = (n: number, depth: number, register: Record<number, number>) => {
    if (register[n] != null) {
      result = Math.max(depth - register[n], result);
    } else {
      if (!visited[n]) {
        visited[n] = true;
        const next = edges[n];
        if (next != -1) {
          register[n] = depth;
          DFS(next, depth + 1, register);
        }
      }
    }
  };

  for (let i = 0; i < edges.length; i++) {
    if (!visited[i]) {
      DFS(i, 0, {});
    }
  }

  return result;
}
