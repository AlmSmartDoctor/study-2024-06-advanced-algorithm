const input = require("fs")
  .readFileSync(process.platform === "linux" ? "/dev/stdin" : "./input.txt")
  .toString()
  .trim()
  .split("\n")
  .map((el) => el.split(" ").map(Number));

const [n, m] = input[0];
const board = input.slice(1);

let visit: boolean[][] = [];
const move: [number, number][] = [
  [0, 1],
  [1, 0],
  [0, -1],
  [-1, 0],
];
const land = new Map<string, number>();
let landArr: [number, number, number][] = [];
let landNum = 0;

const bfs = (i: number, j: number) => {
  const q: [number, number][] = [[i, j]];
  visit[i][j] = true;
  land.set(`${i},${j}`, landNum);
  landArr.push([i, j, landNum]);

  while (q.length > 0) {
    const [x, y] = q.shift()!;
    for (const [a, b] of move) {
      const dx = x + a,
        dy = y + b;
      if (
        dx >= 0 &&
        dx < n &&
        dy >= 0 &&
        dy < m &&
        !visit[dx][dy] &&
        board[dx][dy] === 1
      ) {
        q.push([dx, dy]);
        visit[dx][dy] = true;
        land.set(`${dx},${dy}`, landNum);
        landArr.push([dx, dy, landNum]);
      }
    }
  }
};

const solve = async () => {
  visit = Array.from({ length: n }, () => Array(m).fill(false));

  // BFS
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      if (board[i][j] === 1 && !visit[i][j]) {
        bfs(i, j);
        landNum++;
      }
    }
  }

  // make edges
  const edges: [number, number, number][] = [];
  for (const [x, y, curLand] of landArr) {
    for (const [a, b] of move) {
      let dist = 0;
      let dx = x + a,
        dy = y + b;
      while (dx >= 0 && dx < n && dy >= 0 && dy < m) {
        const toLand = land.get(`${dx},${dy}`);
        if (curLand === toLand) break;
        if (toLand === undefined) {
          dx += a;
          dy += b;
          dist++;
          continue;
        }
        if (dist >= 2) {
          edges.push([dist, curLand, toLand]);
        }
        break;
      }
    }
  }
  edges.sort((a, b) => b[0] - a[0]);

  // Kruskal
  const parents = Array.from({ length: landNum }, (_, i) => i);

  const find = (k: number): number => {
    if (k !== parents[k]) {
      parents[k] = find(parents[k]);
    }
    return parents[k];
  };

  const union = (x: number, y: number) => {
    const rootX = find(x);
    const rootY = find(y);
    parents[rootY] = rootX;
  };

  let ans = 0;
  let cnt = landNum - 1;
  while (cnt > 0) {
    if (edges.length === 0) {
      console.log(-1);
      process.exit();
    }
    const [w, a, b] = edges.pop()!;
    if (find(a) !== find(b)) {
      union(a, b);
      ans += w;
      cnt--;
    }
  }
  console.log(ans);
  process.exit();
};

solve();
