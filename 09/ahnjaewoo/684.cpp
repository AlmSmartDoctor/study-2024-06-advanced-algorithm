class Solution {
public:
    unordered_map<int, int> parent;

    int findParent(int node) {
        if (parent.find(node) == parent.end() || parent[node] == node) {
            parent[node] = node;
            return node;
        }
        else return findParent(parent[node]);
    }

    int merge(int node1, int node2) {
        if (node1 == node2) return 1;
        else if (findParent(node1) == findParent(node2)) return 0;
        parent[findParent(node1)] = findParent(node2);
        return 1; 
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> answer;
        for (int i = 0; i < edges.size(); i++) {
            int node1 = edges[i][0];
            int node2 = edges[i][1];
            if (merge(node1, node2) == 0) answer = {node1, node2};
        }
        return answer;
    }
};