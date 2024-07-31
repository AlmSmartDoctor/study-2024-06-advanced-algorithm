class Solution {
public:
    double depthFirstSearch(int n, unordered_map<int, vector<int>>& connection, int t, int target, unordered_set<int>& visited) {
        int choice_num = 0;
        for (int i = 0; i < connection[n].size(); i++) {
            if (!visited.count(connection[n][i])) choice_num += 1;
        }
        if (n == target) {
            if (t == 0 || choice_num == 0) return 1;
            else return 0;
        }
        if (t == 0) return 0;
        double search_result;
        for (int i = 0; i < connection[n].size(); i++) {
            int next_target = connection[n][i];
            if (visited.count(next_target)) continue;
            visited.insert(n);
            search_result = depthFirstSearch(next_target, connection, t - 1, target, visited);
            if (search_result != 0) {
                return (double) search_result / (double) choice_num;
            }
        }
        visited.erase(n);
        return 0;
    } 

    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        unordered_map<int, vector<int>> connection;
        for (int i = 0; i < edges.size(); i++) {
            connection[edges[i][0]].push_back(edges[i][1]);
            connection[edges[i][1]].push_back(edges[i][0]);
        }
        unordered_set<int> visited;
        double result = depthFirstSearch(1, connection, t, target, visited);
        return result;
    }
};