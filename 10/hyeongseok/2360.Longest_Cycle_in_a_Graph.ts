function longestCycle(edges: number[]): number {
  const seen = new Set();
  let result = -1;
  const dfs = (n: number, depth: number, register: Record<number, number>) => {
      if (register[n] != null) {
          result = Math.max(depth - register[n], result)
      }
      if (!seen.has(n)) {
          seen.add(n);
          const next = edges[n];
          if (next != -1) {
              register[n] = depth;
              dfs(next, depth + 1, register)
          } else {
              seen.add(next);
          }
      }
  }
  for(const key in edges) {
      if (!seen.has(key)) {
          dfs(Number(key), 0, {})
      }
  }
  return result;
};

function longestCycle(edges: number[]): number {
  const seen = new Set();
  let result = -1;
  for(let key = 0; key < edges.length; key++) {
      if((key != -1) && !seen.has(key)) {
          seen.add(key)
          let count = 0, node = key, found = new Map();
          found.set(node, 0);
          while(node != -1) {
              count++;
              node = edges[node]
              if (seen.has(node)) {
                  if (found.has(node)) {
                      result = Math.max(result, count - found.get(node))
                  }
                  break;
              } else {
                  found.set(node, count);
                  seen.add(node);
              }
          }
      }
  }
  return result;
}