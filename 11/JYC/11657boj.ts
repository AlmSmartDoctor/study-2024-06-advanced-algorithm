const input = [
  [3, 4],
  [1, 2, 4],
  [1, 3, 3],
  [2, 3, -1],
  [3, 1, -2],
];

function bellmanFord(
  n: number,
  edges: [number, number, number][]
): [boolean, number[]] {
  const dist = new Array(n + 1).fill(Infinity);
  dist[1] = 0;

  for (let i = 1; i <= n; i++) {
    let updated = false;
    for (let j = 0; j < edges.length; j++) {
      const [now, next, cost] = edges[j];
      if (dist[now] !== Infinity && dist[next] > dist[now] + cost) {
        dist[next] = dist[now] + cost;
        updated = true;
        if (i === n) {
          return [true, dist];
        }
      }
    }
    if (!updated) break;
  }

  return [false, dist];
}

const [n, m] = input[0];
const edges: [number, number, number][] = input.slice(1) as [
  number,
  number,
  number
][];

const [negativeCycle, dist] = bellmanFord(n, edges);

if (negativeCycle) {
  console.log(-1);
} else {
  for (let i = 2; i <= n; i++) {
    if (dist[i] === Infinity) {
      console.log(-1);
    } else {
      console.log(dist[i]);
    }
  }
}
