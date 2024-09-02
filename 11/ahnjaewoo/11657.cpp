#include <iostream>
#include <vector>

using namespace std;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int a, b, c, m, n;
	vector<vector<int>> edges;
	int inf = 1000000000;

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		vector<int> edge{a, b, c};
		edges.push_back(edge);
	}
	vector<int> distance(n + 1, inf);

	distance[1] = 0;
	bool negative_cycle = false;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			vector<int> currentEdge = edges[j];
			int fromNode = currentEdge[0];
			int toNode = currentEdge[1];
			int edgeDistance = currentEdge[2];
			if (distance[fromNode] != inf && distance[toNode] > distance[fromNode] + edgeDistance) {
				distance[toNode] = distance[fromNode] + edgeDistance;
				if (distance[toNode] > 2 * inf || distance[toNode] < (-2) * inf) {
					negative_cycle = true;
					break;
				}
			}
		}
		if (negative_cycle) break;
	}
	for (int j = 0; j < m; j++) {
		vector<int> currentEdge = edges[j];
		int fromNode = currentEdge[0];
		int toNode = currentEdge[1];
		int edgeDistance = currentEdge[2];
		if (distance[fromNode] != inf && distance[toNode] > distance[fromNode] + edgeDistance) {
			negative_cycle = true;
		}
	}

	if (negative_cycle) cout << -1 << '\n';
	else {
		for (int i = 0; i < n - 1; i++) {
			if (distance[i + 2] == inf) cout << -1 << '\n';
			else cout << distance[i + 2] << '\n';
		}
	}

	return 0;
}