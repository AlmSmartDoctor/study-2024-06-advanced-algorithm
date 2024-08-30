### 778. Swim in Rising Water

![image](https://github.com/user-attachments/assets/9182b550-d81b-4ee6-a4ec-326dce92c795)

```cpp
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
};

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n): parent(n), rank(n, 1) {
        for(int i = 0; i < n; ++i)
        parent[i] = i;
    }

    int find(int u) {
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u); v = find(v);
        if(u == v) return;
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
    }
};

class Solution {
public:
    int n;

    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();

        vector<int> indexList = getIndexListByValue(grid);
        DisjointSet ds(n * n);

        int t = 0;
        while (1) {
            if (ds.find(0) == ds.find(n * n - 1)) break;

            t++;        
            Point current = toPoint(indexList[t]);

            for (int i = 0; i < 4; i++) {
                Point next(current.x + dx[i], current.y + dy[i]);
                if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= n) continue;

                if (grid[next.x][next.y] < t) ds.merge(toIndex(current), toIndex(next));
            }
        }

        return t;
    }

    vector<int> getIndexListByValue(const vector<vector<int>>& grid) {
        vector<int> indexList(n * n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                indexList[grid[i][j]] = i * n + j;

        return indexList;
    }

    Point toPoint(int index) {
        return {index / n, index % n};
    }

    int toIndex(Point point) {
        return point.x * n + point.y;
    }
};
```

<br/>

### 212. Word Search II

![image](https://github.com/user-attachments/assets/1fb0618d-c415-4260-b797-e1a2a68fa9f9)

```cpp
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
};

class TrieNode {
public:
    TrieNode* children[26] = {};
    string* endWord;

    TrieNode() { endWord = nullptr; }

    void insert(string& word) {
        TrieNode* node = this;
        for (char c : word) {
            int i = c - 'a';
            if (node->children[i] == nullptr) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->endWord = &word;
    }

};

class Solution {
public:
    TrieNode* root;
    int m, n;
    bool isVisited[12][12];
    vector<string> foundWords;
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new TrieNode();
        m = board.size();
        n = board[0].size();

        for (string& word : words)
            root->insert(word);

        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if(root->children[board[r][c] -'a'] != nullptr)
                    findWordInTrie(board, root->children[board[r][c] - 'a'], r, c);

        return foundWords;
    }

    void findWordInTrie(const vector<vector<char>>& board, TrieNode* node, int r, int c) {
        if (node->endWord != nullptr) {
            foundWords.push_back(*node->endWord);
            node->endWord = nullptr;
        }

        isVisited[r][c] = true;

        for (int i = 0; i < 4; i++) {
            Point next(r + dx[i], c + dy[i]);
            if (next.x < 0 || next.x >= m || next.y < 0 || next.y >= n || isVisited[next.x][next.y]) continue;

            TrieNode* nextNode = node->children[board[next.x][next.y] - 'a'];
            if (nextNode == nullptr) continue;
            
            findWordInTrie(board, nextNode, next.x, next.y);
        }

        isVisited[r][c] = false;
        return;
    }
};
```
