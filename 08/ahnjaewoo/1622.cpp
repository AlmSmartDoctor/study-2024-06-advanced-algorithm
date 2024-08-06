class Fancy {
private:
    vector<int> x;
public:
    int MAX = pow(10, 9) + 7;

    Fancy() {
        x.clear();
    }
    
    void append(int val) {
        x.push_back((val % MAX));
    }
    
    void addAll(int inc) {
        for (int i = 0; i < x.size(); i++) {
            x[i] = ((x[i] % MAX) + (inc % MAX)) % MAX;
        }
    }
    
    void multAll(int m) {
        for (int i = 0; i < x.size(); i++) {
            int sum = 0;
            for (int j = 0; j < m; j++) {
                sum = ((sum % MAX) + x[i]) % MAX;
            }
            x[i] = sum;
        }
    }
    
    int getIndex(int idx) {
        if (x.size() <= idx) return -1;
        return x[idx];
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