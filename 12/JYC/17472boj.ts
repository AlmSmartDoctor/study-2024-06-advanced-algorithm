import * as fs from "fs";

const input = fs
  .readFileSync(process.platform === "linux" ? "/dev/stdin" : "./input.txt")
  .toString()
  .trim()
  .split("\n")
  .map((line) => line.split(" ").map(Number));

const [rows, cols] = input[0];
const grid = input.slice(1);

let visited: boolean[][] = [];
const directions: [number, number][] = [
  [0, 1],
  [1, 0],
  [0, -1],
  [-1, 0],
];
const islandMap = new Map<string, number>();
let islandDetails: [number, number, number][] = [];
let islandCount = 0;

const bfs = (startRow: number, startCol: number) => {
  const queue: [number, number][] = [[startRow, startCol]];
  visited[startRow][startCol] = true;
  islandMap.set(`${startRow},${startCol}`, islandCount);
  islandDetails.push([startRow, startCol, islandCount]);

  while (queue.length > 0) {
    const [currentRow, currentCol] = queue.shift()!;
    for (const [rowOffset, colOffset] of directions) {
      const newRow = currentRow + rowOffset;
      const newCol = currentCol + colOffset;
      if (
        newRow >= 0 &&
        newRow < rows &&
        newCol >= 0 &&
        newCol < cols &&
        !visited[newRow][newCol] &&
        grid[newRow][newCol] === 1
      ) {
        queue.push([newRow, newCol]);
        visited[newRow][newCol] = true;
        islandMap.set(`${newRow},${newCol}`, islandCount);
        islandDetails.push([newRow, newCol, islandCount]);
      }
    }
  }
};

const solve = () => {
  visited = Array.from({ length: rows }, () => Array(cols).fill(false));

  // BFS to identify islands
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === 1 && !visited[r][c]) {
        bfs(r, c);
        islandCount++;
      }
    }
  }

  // Create edges between islands
  const edgeList: [number, number, number][] = [];
  for (const [row, col, currentIsland] of islandDetails) {
    for (const [rowOffset, colOffset] of directions) {
      let distance = 0;
      let newRow = row + rowOffset;
      let newCol = col + colOffset;
      while (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
        const neighboringIsland = islandMap.get(`${newRow},${newCol}`);
        if (currentIsland === neighboringIsland) break;
        if (neighboringIsland === undefined) {
          newRow += rowOffset;
          newCol += colOffset;
          distance++;
          continue;
        }
        if (distance >= 2) {
          edgeList.push([distance, currentIsland, neighboringIsland]);
        }
        break;
      }
    }
  }
  edgeList.sort((a, b) => b[0] - a[0]);

  // Kruskal's algorithm
  const parent = Array.from({ length: islandCount }, (_, i) => i);

  const findParent = (node: number): number => {
    if (node !== parent[node]) {
      parent[node] = findParent(parent[node]);
    }
    return parent[node];
  };

  const union = (x: number, y: number) => {
    const rootX = findParent(x);
    const rootY = findParent(y);
    parent[rootY] = rootX;
  };

  let totalCost = 0;
  let remainingIslands = islandCount - 1;
  while (remainingIslands > 0) {
    if (edgeList.length === 0) {
      console.log(-1);
      return; // Exiting the function gracefully
    }
    const [weight, islandA, islandB] = edgeList.pop()!;
    if (findParent(islandA) !== findParent(islandB)) {
      union(islandA, islandB);
      totalCost += weight;
      remainingIslands--;
    }
  }
  console.log(totalCost);
};

solve();
