const numSquares = (n: number): number => {
  let leastCounter = 0;

  const squares: number[] = [];
  for (let i = 1; i * i <= n; i++) {
    squares.push(i * i);
  }

  const visited = new Array(n + 1).fill(false);
  const queue = [n];
  visited[n] = true;

  while (queue.length > 0) {
    let size = queue.length;
    leastCounter++;

    while (size > 0) {
      const current = queue.shift();

      if (current === undefined) continue;

      for (let y = 0; y < squares.length; y++) {
        const next = current - squares[y];

        if (next === 0) return leastCounter;

        if (next < 0) break;

        if (!visited[next]) {
          queue.push(next);
          visited[next] = true;
        }
      }
      size--;
    }
  }

  return leastCounter;
};
