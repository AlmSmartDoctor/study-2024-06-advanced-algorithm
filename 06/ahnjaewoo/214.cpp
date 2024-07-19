class Solution {
public:
    vector<int> getKmp(const string& s) {
        int length = s.size();
        int start = 1;
        int match = 0;

        vector<int> p(length, 0);

        while (start + match < length) {
            if (s[start + match] == s[match]) {
                match += 1;
                p[start + match - 1] = match;
            }
            else {
                if (match == 0) start += 1;
                else {
                    start += match - p[match - 1];
                    match = p[match - 1];
                }
            }
        }
        return p;
    }

		int maxOverlap(const string& a, const string& b) {
			int a_len = a.size();
			int b_len = b.size();
			vector<int> p = getKmp(b);
			int start = 0;
			int match = 0;

			while (start < a_len) {
				if (match < b_len && a[start + match] == b[match]) {
					match += 1;
					if (start + match == a_len) {
						return match;
					}
				}
				else {
					if (match == 0) start += 1;
					else {
						start += match - p[match - 1];
						match = p[match - 1];
					}
				}
			}
			return 0;
		}

    string shortestPalindrome(string s) {
			string reversed = s;
			reverse(reversed.begin(), reversed.end());
      int suffix = maxOverlap(reversed, s);
			string prefix = s.substr(suffix);
			return reversed + prefix;
    }
};