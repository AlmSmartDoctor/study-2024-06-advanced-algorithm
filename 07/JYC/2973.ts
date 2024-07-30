function placedCoins(edges: number[][], cost: number[]): number[] {
  const n = cost.length;
  const tree: number[][] = Array.from({ length: n }, () => []);

  for (const [u, v] of edges) {
    tree[u].push(v);
    tree[v].push(u);
  }

  const result = Array(n).fill(0);

  function dfs(node: number, parent: number): [number, number[], number[]] {
    if (tree[node].length === 1 && node !== 0) {
      result[node] = 1;
      if (cost[node] < 0) {
        return [1, [], [cost[node]]];
      }
      return [1, [cost[node]], []];
    }

    const positiveCosts = cost[node] > 0 ? [cost[node]] : [];
    const negativeCosts = cost[node] < 0 ? [cost[node]] : [];

    let subtreeSize = 1;

    for (const child of tree[node]) {
      if (child === parent) continue;

      const [childSubtreeSize, childPositives, childNegatives] = dfs(
        child,
        node
      );

      subtreeSize += childSubtreeSize;

      positiveCosts.push(...childPositives);
      negativeCosts.push(...childNegatives);

      positiveCosts.sort((a, b) => b - a);
      if (positiveCosts.length > 3) positiveCosts.length = 3;

      negativeCosts.sort((a, b) => a - b);
      if (negativeCosts.length > 2) negativeCosts.length = 2;
    }

    if (subtreeSize < 3) {
      result[node] = 1;
    } else {
      let maxProduct = 0;

      if (positiveCosts.length >= 3) {
        maxProduct = Math.max(
          maxProduct,
          positiveCosts[0] * positiveCosts[1] * positiveCosts[2]
        );
      }

      if (positiveCosts.length > 0 && negativeCosts.length >= 2) {
        maxProduct = Math.max(
          maxProduct,
          positiveCosts[0] * negativeCosts[0] * negativeCosts[1]
        );
      }

      result[node] = maxProduct > 0 ? maxProduct : 0;
    }

    return [subtreeSize, positiveCosts, negativeCosts];
  }

  dfs(0, -1);

  return result;
}
