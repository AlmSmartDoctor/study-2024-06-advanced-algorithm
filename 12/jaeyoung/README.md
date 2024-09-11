### 874. Walking Robot Simulation

![image](https://github.com/user-attachments/assets/b33d07ec-bbc2-4249-9dfd-cb78d99f7837)

```cpp
class Solution {
public:
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};

    struct Point {
        int x, y;
        Point() {}
        Point(int x, int y): x(x), y(y) {}
    };

    string hash(Point point) {
        return to_string(point.x) + "," + to_string(point.y);
    }
    

    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<string> obstacleSet;
        
        for (const auto& obstacle : obstacles) {
            obstacleSet.insert(hash({obstacle[0], obstacle[1]}));
        }
        
        Point point(0, 0);
        int dir = 0, maxDist = 0;
        
        for (const int command : commands) {
            if (command == -1) {
                dir = (dir + 1) % 4;
                continue;
            }

            if (command == -2) {
                dir = (dir + 3) % 4;
                continue;
            }

            for (int i = 0; i < command; ++i) {
                Point next(point.x + dx[dir], point.y + dy[dir]);

                if (obstacleSet.find(hash(next)) != obstacleSet.end()) break;
                
                point = next;

                maxDist = max(maxDist, point.x * point.x + point.y * point.y);
            }
        }
        
        return maxDist;
    }
};

```

<br/>

### 백준 17472 - 다리 만들기 2

![image](https://github.com/user-attachments/assets/6291c12c-9115-4d1d-87cf-cb9112a6e661)

```cpp
#include <iostream>
#include <queue>
#include <vector>
#define FASTIO() ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

struct Edge {
    int end, weight;
    Edge() {}
    Edge(int end, int weight) : end(end), weight(weight) {}
    bool operator<(const Edge& e) const { return weight > e.weight; }
};

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

class Sea {
    int n, m;
    int num_island;
    vector<vector<int>> island;
    vector<vector<int>> graph;

   public:
    Sea() {}

   private:
    void bfs(Point start, const vector<vector<int>>& map,
             vector<vector<bool>>& is_visited, int index) {
        queue<Point> q;
        q.push(start);
        is_visited[start.x][start.y] = true;
        island[start.x][start.y] = index;

        while (!q.empty()) {
            Point cur = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                Point next(cur.x + dx[i], cur.y + dy[i]);
                if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= m ||
                    map[next.x][next.y] == 0 || is_visited[next.x][next.y])
                    continue;

                q.push(next);
                is_visited[next.x][next.y] = true;
                island[next.x][next.y] = index;
            }
        }
    }

    void add_edge(Point point, int start) {
        for (int i = 0; i < 4; i++) {
            Point next(point.x + dx[i], point.y + dy[i]);
            if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= m ||
                island[next.x][next.y] > 0)
                continue;

            int length = 1;
            while (1) {
                next = {next.x + dx[i], next.y + dy[i]};
                if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= m)
                    break;

                int end = island[next.x][next.y];
                if (island[next.x][next.y] > 0) {
                    if (start != end && length > 1) {
                        graph[start][end] = min(graph[start][end], length);
                        graph[end][start] = min(graph[end][start], length);
                    }
                    break;
                }

                length++;
            }
        }
    }

   public:
    void init() {
        cin >> n >> m;
        vector<vector<int>> map(n, vector<int>(m));
        island.resize(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) cin >> map[i][j];

        num_island = 0;
        vector<vector<bool>> is_visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == 0 || is_visited[i][j]) continue;
                bfs({i, j}, map, is_visited, ++num_island);
            }
        }

        graph.resize(num_island + 1, vector<int>(num_island + 1, INT16_MAX));
    }

    void set_edges() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (island[i][j] == 0) continue;
                add_edge({i, j}, island[i][j]);
            }
        }
    }

    int prim() {
        int sum = 0;
        priority_queue<Edge> pq;
        vector<bool> is_added(num_island + 1, false);

        is_added[1] = true;
        for (int i = 1; i < num_island + 1; i++) {
            if (graph[1][i] == INT16_MAX) continue;
            pq.push({i, graph[1][i]});
        }

        while (!pq.empty()) {
            Edge cur = pq.top();
            pq.pop();
            if (is_added[cur.end]) continue;

            is_added[cur.end] = true;
            sum += cur.weight;

            for (int i = 1; i < num_island + 1; i++) {
                if (graph[cur.end][i] == INT16_MAX) continue;
                pq.push({i, graph[cur.end][i]});
            }
        }

        for (int i = 1; i < num_island + 1; i++)
            if (!is_added[i]) return -1;

        return sum;
    }
};

int main() {
    FASTIO();
    Sea sea;
    sea.init();
    sea.set_edges();
    cout << sea.prim() << "\n";

    return 0;
}
```
