### 백준 17412

![image](https://github.com/user-attachments/assets/39b48a21-7b46-4e2c-87e1-3da69583e8c0)

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define FASTIO() ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

const int INF = 1e9;
const int MAX = 802;

class NetworkFlow {
    int capacity[MAX][MAX];
    int flow[MAX][MAX];
    vector<int> adj[MAX];

   public:
    NetworkFlow() {}

    void init() {
        int n, p;
        cin >> n >> p;

        for (int i = 0; i < p; ++i) {
            int u, v;
            cin >> u >> v;
            capacity[u][v] = 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    int fordFulkerson(int source, int target) {
        int total_flow = 0;

        while (true) {
            vector<bool> visited(MAX, false);
            int new_flow = dfs(source, target, INF, visited);
            if (new_flow == 0) break;

            total_flow += new_flow;
        }

        return total_flow;
    }

   private:
    int dfs(int cur, int target, int min_flow, vector<bool>& visited) {
        if (cur == target) return min_flow;
        visited[cur] = true;

        for (int next : adj[cur]) {
            if (visited[next] || capacity[cur][next] - flow[cur][next] <= 0)
                continue;

            int new_flow = min(min_flow, capacity[cur][next] - flow[cur][next]);
            int result_flow = dfs(next, target, new_flow, visited);

            if (result_flow > 0) {
                flow[cur][next] += result_flow;
                flow[next][cur] -= result_flow;
                return result_flow;
            }
        }

        return 0;
    }
};

int main() {
    FASTIO();

    auto nf = NetworkFlow();
    nf.init();
    cout << nf.fordFulkerson(1, 2) << "\n";

    return 0;
}

```
