class Solution {
public:
    vector<int> getKmp(string needle) {
        int length = needle.size();
        int start = 1;
        int match = 0;

        vector<int> p(length, 0);

        while (start + match < length) {
            if (needle[start + match] == needle[match]) {
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

    int strStr(string haystack, string needle) {
        int h_len = haystack.size();
        int n_len = needle.size();
        int start = 0;
        int match = 0;
        vector<int> p = getKmp(needle);
 
        while (start + n_len <= h_len) {
            if (match < n_len && haystack[start + match] == needle[match]) {
                match += 1;
                if (match == n_len) {
                    return start;
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
        return -1;
    }
};
