#include <vector>
using namespace std;

class Solution {
 public:
  double ans = 0;
  int targetTime;
  void dfs(vector<int> graph[], int start, int time, int target,
           vector<int>& visited, double prob) {
    visited[start] = 1;
    if (target == start) {
      if (time == targetTime)
        ans = prob;
      else {
        if (time < targetTime && start != 1 && graph[start].size() <= 1)
          ans = prob;
      }
      return;  // ans = 0
    }
    for (auto node : graph[start]) {
      double size = graph[start].size();

      // 부모 노드도 그래프 요소에 추가되어 있음
      if (start != 1) size -= 1;

      double p = 1.0 / size;
      if (!visited[node]) dfs(graph, node, time + 1, target, visited, prob * p);
    }
  }
  double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
    vector<int> graph[n + 1];
    targetTime = t;
    for (auto nodes : edges) {
      graph[nodes[0]].push_back(nodes[1]);
      graph[nodes[1]].push_back(nodes[0]);
    }
    if (graph[1].size() == 0 && target == 1) return 1.0;
    vector<int> visited(n + 1, 0);
    dfs(graph, 1, 0, target, visited, 1);
    return ans;
  }
};