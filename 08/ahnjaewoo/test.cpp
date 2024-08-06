class Fancy {
private:
    vector<int> x;
		vector<tuple<int, string, int>> operations;
		// index, operation, value
		int curIdx;
public:
    int MAX = pow(10, 9) + 7;

    Fancy() {
        x.clear();
				curIdx = -1;
    }
    
    void append(int val) {
        x.push_back((val % MAX));
				curIdx = x.size();
    }
    
    void addAll(int inc) {
				operations.push_back({curIdx, "add", inc});
    }
    
    void multAll(int m) {
				operations.push_back({curIdx, "mult", m});
    }
    
    int getIndex(int idx) {
        if (x.size() <= idx) return -1;
				int result = x[idx];
				for (int i = 0; i < operations.size(); i++) {
					int targetIdx = get<0>(operations[i]);
					string operation = get<1>(operations[i]);
					int value = get<2>(operations[i]);
                    if (operation == "add") return 1;
                    if (operation == "mult") return 2;
                    // return value;
					if (idx <= targetIdx) {
						if (operation == "add") {
							result = ((result % MAX) + (value % MAX)) % MAX;
						} else if (operation == "mult") {
							result = ((result % MAX) * (value % MAX)) % MAX;
						}
					}
				}
        return result;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */