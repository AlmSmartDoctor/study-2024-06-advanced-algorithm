
class Solution {
 public:
  int tree[400005] = {
      0,
  };
  void upd(int now, int s, int e, int p, int d) {
    if (s >= e) {
      tree[now] = d;
      return;
    }
    if (p <= (s + e) / 2)
      upd(now * 2, s, (s + e) / 2, p, d);
    else
      upd(now * 2 + 1, (s + e) / 2 + 1, e, p, d);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
  }
  int get(int now, int s, int e, int l, int r) {
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[now];
    return get(now * 2, s, (s + e) / 2, l, r) +
           get(now * 2 + 1, (s + e) / 2 + 1, e, l, r);
  }
  void init(int n) {
    for (int i = 0; i <= n * 4; i++) tree[i] = 0;
  }

  long long countOperationsToEmptyArray(vector<int> &nums) {
    int n = nums.size();
    init(n);
    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++) vec.push_back({nums[i], i + 1});
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) {
      upd(1, 1, n, i, 1);
    }
    long long ret = 0;
    int bef = 0;
    for (int i = 1; i < n; i++) {
      int p = vec[i - 1].second;
      if (bef < p) {
        ret += get(1, 1, n, bef, p);
      } else {
        ret += get(1, 1, n, 1, p) + get(1, 1, n, bef, n);
      }
      upd(1, 1, n, p, 0);
    }
    return ret;
  }
};