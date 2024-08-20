class Solution {
public:
    vector<int> cycle;

    int searchCycle(int edge, vector<int>& edges, map<int, int>& passedEdges) {
        if (edge == -1 || edges[edge] == -1) return -1;

        if (cycle[edges[edge]] > -2) {
            cycle[edge] = cycle[edges[edge]];
        }
        else if (passedEdges.find(edge) != passedEdges.end()) {
            cycle[edge] = passedEdges.size() - passedEdges[edge];
        }
        else {
            passedEdges[edge] = passedEdges.size();
            cycle[edge] = searchCycle(edges[edge], edges, passedEdges);
        }
        return cycle[edge];
    }

    int longestCycle(vector<int>& edges) {
        int maxCycle = -1;
        cycle.resize(edges.size(), -2);
        for (int i = 0; i < edges.size(); i++) {
            if (cycle[i] > -2) continue;
            map<int, int> passedEdges;
            int result = searchCycle(i, edges, passedEdges);
            if (result > maxCycle) maxCycle = result;
        }
        return maxCycle;
        
    }
};