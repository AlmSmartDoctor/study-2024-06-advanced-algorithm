class Solution {
public:
	vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
		sort(products.begin(), products.end());
		vector<vector<string>> answer;
		vector<string> hubo = products;
		for (int i = 0; i < searchWord.size(); i++) {
			string prefix = searchWord.substr(0, i + 1);
			int matched = 0;
			vector<string> matchedProducts;
			for (int j = 0; j < hubo.size(); j++) {
				if (hubo[j].substr(0, i + 1) == prefix) {
					matched++;
					matchedProducts.push_back(hubo[j]);
				}
				if (matched == 3) break;
			}
			if (matched < 3) hubo = matchedProducts;
			answer.push_back(matchedProducts);
		}
		return answer;
	}
};