function numSquares(n: number): number {
  let level = 1;
  let visited: {[key: number]: boolean} = {};
  visited[n] = true;
  let q = [n];
  while(q.length) {
      let size = q.length;
      for(let i = 0; i < size; i++) {
          let cur = q.shift();
          for(let j = 1; j**2 <= cur; j++) {
              let diff = cur - j * j;
              if (diff == 0) return level;
              if (diff < 0) break;
              if (!visited[diff]) {
                  visited[diff] = true;
                  q.push(diff);
              }
          }
      }
      level++;
  }
  return level;
};