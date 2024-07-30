### 28. Find the Index of the First Occurrence in a String
![image](https://github.com/user-attachments/assets/e51757ee-076d-4614-a4a2-819aef2b50bb)
```cpp
class Solution {
public:
	int strStr(string haystack, string needle) {
		int n = needle.size();
		if (n == 0) return 0;

		vector<int> pi = getPi(needle);
		int m = haystack.size();
		int begin = 0, matched = 0;
        
		while (begin + matched < m) {
			if (haystack[begin + matched] == needle[matched]) {
        matched++;
				if (matched == n) return begin;
        continue;
			}
			
      if (matched == 0) {
        begin++;
        continue;
      }
				
			begin += matched - pi[matched - 1];
			matched = pi[matched - 1];
		}

		return -1;
	}

  vector<int> getPi(const string& word) {
		int m = word.size();
		vector<int> pi(m, 0);

		int begin = 1, matched = 0;
		while (begin + matched < m) {
			if (word[begin + matched] == word[matched]) {
        matched++;
				pi[begin + matched - 1] = matched;
        continue;
			}

      if (matched == 0) {
				begin++;
        continue;
			}
					
      begin += matched - pi[matched - 1];
			matched = pi[matched - 1];
		}

		return pi;
	}
};
```
<br/>

### 1392. Longest Happy Prefix
![image](https://github.com/user-attachments/assets/d136cd25-9a53-4500-8e31-cf2cac778dff)
```cpp
class Solution {
public:
    string longestPrefix(string s) {
        long long prefixHash = 0, suffixHash = 0, power = 1;
        int longestIndex = -1, length = s.size();

        for (int i = 0; i < length - 1; i++) {
            prefixHash = updateHash(prefixHash, s[i]);
            suffixHash = updateReverseHash(suffixHash, s[length - 1 - i], power);
            power = (power * BASE) % MOD;
            if (prefixHash == suffixHash) {
                longestIndex = i;
            }
        }

        return s.substr(0, longestIndex + 1);
    }

private:
    const int MOD = 1e9 + 9;
    const int BASE = 26;

    long long updateHash(long long prevHash, char ch) {
        return (BASE * prevHash + (ch - 'a')) % MOD;
    }

    long long updateReverseHash(long long prevHash, char ch, long long power) {
        return ((ch - 'a') * power + prevHash) % MOD;
    }
};
```
