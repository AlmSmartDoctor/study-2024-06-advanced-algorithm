class Solution {
 public:
  int dis[105][105];
  int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dis[i][j] = 1e9;
      }
      dis[i][i] = 0;
    }
    for (auto& vec : edges) {
      int a = vec[0], b = vec[1], w = vec[2];
      dis[a][b] = dis[b][a] = w;
    }
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          int nd = min(dis[i][j], dis[i][k] + dis[k][j]);
          dis[i][j] = dis[j][i] = nd;
        }
      }
    }
    int mi = 1e9, idx = -1;
    for (int i = 0; i < n; i++) {
      int c = 0;
      for (int j = 0; j < n; j++) {
        if (dis[i][j] <= distanceThreshold) c++;
      }
      if (mi >= c) {
        mi = c;
        idx = i;
      }
      printf("%d %d\n", i, c);
    }
    return idx;
  }
};