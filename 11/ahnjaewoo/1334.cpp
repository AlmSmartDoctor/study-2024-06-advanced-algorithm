class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        int inf = 100000000;
        vector<vector<int>> distance(n, vector<int>(n, inf));
        for (int i = 0; i < edges.size(); i++) {
            distance[edges[i][0]][edges[i][1]] = edges[i][2];
            distance[edges[i][1]][edges[i][0]] = edges[i][2];
        }
        for (int i = 0; i < n; i++) {
            distance[i][i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (distance[j][k] > distance[j][i] + distance[i][k]) {
                        distance[j][k] = distance[j][i] + distance[i][k];
                    }
                }
            }
        }
        int min = n + 1;
        int minNode = -1;
        for (int i = 0; i < n; i++) {
            int current = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && distance[i][j] <= distanceThreshold && distance[i][j] != 0) {
                    current += 1;
                }
            }
            if (current <= min) {
                minNode = i;
                min = current;
            }
        }

        return minNode;
    }
};