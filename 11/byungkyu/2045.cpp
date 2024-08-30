#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  int dis[10005][2];
  vector<int> ch[10005];
  int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
    for (int i = 0; i <= n; i++) {
      dis[i][0] = dis[i][1] = -1;
    }
    for (auto& vec : edges) {
      int a = vec[0], b = vec[1];
      ch[a].push_back(b);
      ch[b].push_back(a);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    dis[1][0] = 0;
    pq.push({0, 1});
    int ret = -1;
    while (pq.size()) {
      auto [w, a] = pq.top();
      printf("%d %d\n", w, a);
      pq.pop();
      for (auto b : ch[a]) {
        if (dis[b][0] == -1) {
          dis[b][0] = w + time;
          if (dis[b][0] % (change * 2) >= change) {
            dis[b][0] = (dis[b][0] / (change * 2) + 1) * (change * 2);
          }
          pq.push({dis[b][0], b});
        } else if (dis[b][1] == -1) {
          int k = w + time;
          if (b == n && k > dis[n][0]) {
            return k;
          }
          if (k % (change * 2) >= change) {
            k = (k / (change * 2) + 1) * (change * 2);
          }
          if (k > dis[b][0]) {
            dis[b][1] = k;
            pq.push({dis[b][1], b});
          }
        }
      }
    }
  }
};