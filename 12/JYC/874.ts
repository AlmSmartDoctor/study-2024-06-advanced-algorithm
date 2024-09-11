function robotSim(commands: number[], obstacles: number[][]): number {
  const dire = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0],
  ];
  let direIndex = 0,
    curr = [0, 0],
    maxx = 0;

  const obstaclesSet = new Set(
    obstacles.map((obstacle) => obstacle.toString())
  );

  commands.forEach((command) => {
    if (command === -1) {
      direIndex = (direIndex + 1) % 4;
    } else if (command === -2) {
      direIndex = (direIndex + 3) % 4;
    } else {
      const [dx, dy] = dire[direIndex];
      Array.from({ length: command }).some(() => {
        const nextPosition = [curr[0] + dx, curr[1] + dy];
        if (obstaclesSet.has(nextPosition.toString())) {
          return true;
        }
        curr = nextPosition;
        return false;
      });

      maxx = Math.max(maxx, curr[0] ** 2 + curr[1] ** 2);
    }
  });

  return maxx;
}
