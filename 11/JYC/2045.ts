function secondMinimum(
  n: number,
  edges: number[][],
  time: number,
  change: number
): number {
  const graph: number[][] = new Array(n + 1).fill(0).map(() => []);

  for (const [a, b] of edges) {
    graph[a].push(b);
    graph[b].push(a);
  }

  const distances: number[][] = new Array(n + 1)
    .fill(0)
    .map(() => new Array(2).fill(Infinity));
  distances[1][0] = 0;

  const queue: number[][] = [[1, 0]];

  // (현재시간) / (change) % 2 == 1 ? change - (현재시간 % change) : 0
  // (현재 노드까지 오는데 걸리는 시간) + waitTime + time
  while (queue.length) {
    const [node, currTime] = queue.shift()!;

    graph[node].forEach((next) => {
      const cycle = Math.floor(currTime / change);
      const waitTime = cycle % 2 === 1 ? change - (currTime % change) : 0;
      const nextTime = currTime + waitTime + time;

      if (distances[next][0] > nextTime) {
        distances[next][1] = distances[next][0];
        distances[next][0] = nextTime;
        queue.push([next, nextTime]);
      } else if (
        nextTime > distances[next][0] &&
        distances[next][1] > nextTime
      ) {
        distances[next][1] = nextTime;
        queue.push([next, nextTime]);
      }
    });
  }

  return distances[n][1];
}
