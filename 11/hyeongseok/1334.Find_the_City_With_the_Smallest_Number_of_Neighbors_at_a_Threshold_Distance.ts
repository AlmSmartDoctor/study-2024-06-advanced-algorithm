function findTheCity(n: number, edges: number[][], distanceThreshold: number): number {
  const dist: number[][] = Array.from({ length: n }, () => Array(n).fill(Infinity));

  // init dist
  for(let i = 0; i < n; i++) {
      dist[i][i] = 0;
  }

  for (const [from, to, weight] of edges) {
      dist[from][to] = weight;
      dist[to][from] = weight;
  }

  // calculate min dist
  for (let k = 0; k < n; k++) {
      for (let i = 0; i < n; i++) {
          for (let j = 0; j < n; j++) {
              if (dist[i][k] + dist[k][j] < dist[i][j]) {
                  dist[i][j] = dist[i][k] + dist[k][j]
              }
          }
      }
  }

  let minNeighbors = Infinity;
  let resultCity = -1;

  for (let i = 0; i < n; i++) {
      let neighborsCount = 0;
      for (let j = 0; j < n; j++) {
          if (i !== j && dist[i][j] <= distanceThreshold) {
              neighborsCount++;
          }
      }
      if (
          neighborsCount < minNeighbors || 
          (neighborsCount === minNeighbors && i > resultCity)
      ) {
          minNeighbors = neighborsCount;
          resultCity = i;
      }
  }

  return resultCity;
};