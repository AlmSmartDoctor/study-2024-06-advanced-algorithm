class Fancy {
private:
    vector<int> x;
		vector<tuple<int, string, int>> operations;
		// index, operation, value
		int curIdx;
		vector<tuple<int, int>> memo;
		// current calculated index, current value
public:
    int MAX = pow(10, 9) + 7;

    Fancy() {
        x.clear();
				curIdx = -1;
    }
    
    void append(int val) {
        x.push_back((val % MAX));
				memo.push_back({0, (val % MAX)});
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
				int memoIdx = get<0>(memo[idx]);
				int result = get<1>(memo[idx]);
				for (int i = memoIdx; i < operations.size(); i++) {
					int targetIdx = get<0>(operations[i]);
					string operation = get<1>(operations[i]);
					int value = get<2>(operations[i]);
					if (idx < targetIdx) {
						if (operation == "add") {
							result = (int)(((unsigned long)(result % MAX) + (value % MAX)) % MAX);
						} else if (operation == "mult") {
							result = (int)(((unsigned long)(result % MAX) * (value % MAX)) % MAX);
						}
					}
				}
				memo[idx] = {operations.size(), result};
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