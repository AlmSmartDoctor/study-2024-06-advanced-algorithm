class Solution {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size();
		int target = grid[n-1][n-1];
		int maxValue = grid[0][0];

		if (n == 1) return 0;

		set<int> passedBy = { 0 };
		set<int> neighbor = { 1, n };
		for (int i = 0; i < pow(n, 2); i++) {
			int minValue = pow(n, 2) + 1;
			int minValuePoint = 0;
			for (set<int>::iterator j = neighbor.begin(); j != neighbor.end(); j++) {
				int curPoint = *j;
				int curValue = grid[curPoint / n][curPoint % n];

				if (minValue > curValue) {
					minValue = curValue;
					minValuePoint = curPoint;
				}
			}

			int minValuePointX = minValuePoint / n;
			int minValuePointY = minValuePoint % n;

			if (maxValue < grid[minValuePointX][minValuePointY]) maxValue = grid[minValuePointX][minValuePointY];
			
			if (minValuePoint + n == pow(n, 2) - 1 || minValuePoint + 1 == pow(n, 2) - 1) {
				if (maxValue > target) return maxValue;
				else return target;
			}
			
			neighbor.erase(minValuePoint);
			passedBy.insert(minValuePoint);

			if (minValuePointX != 0 && (passedBy.find(minValuePoint - n) == passedBy.end())) {
				neighbor.insert(minValuePoint - n);
			}
			if (minValuePointX != n - 1 && (passedBy.find(minValuePoint + n) == passedBy.end())) {
				neighbor.insert(minValuePoint + n);
			}
			if (minValuePointY != 0 && (passedBy.find(minValuePoint - 1) == passedBy.end())) {
				neighbor.insert(minValuePoint - 1);
			}
			if (minValuePointY != n - 1 && (passedBy.find(minValuePoint + 1) == passedBy.end())) {
				neighbor.insert(minValuePoint + 1);
			}
		}
	return 0;
	}
};