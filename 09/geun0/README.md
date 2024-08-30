- [1632. Rank Transform of a Matrix](https://leetcode.com/problems/rank-transform-of-a-matrix/description/)

![](images/1632.png)

```python
from collections import defaultdict

class NaiveDisjointSet:
    def __init__(self):
        self.parent = {}

    def find(self, u: int) -> int:
        if self.parent[u] == u:
            return u
        return self.find(self.parent[u])

    def merge(self, u: int, v: int) -> None:
        self.parent.setdefault(u, u)
        self.parent.setdefault(v, v)

        u, v = self.find(u), self.find(v)

        if u != v:
            self.parent[u] = v

    def getGroups(self) -> dict[int, list[int]]:
        groups = defaultdict(list)
        for u in self.parent.keys():
            groups[self.find(u)].append(u)
        return groups

class Solution:
    def matrixRankTransform(self, matrix: list[list[int]]) -> list[list[int]]:
        m, n = len(matrix), len(matrix[0])
        ans = [[0] * n for _ in range(m)]
        positions_dict = defaultdict(list)
        maxRank_list = [0] * (m + n)

        for i, row in enumerate(matrix):
            for j, val in enumerate(row):
                positions_dict[val].append((i, j))

        for _, positions in sorted(positions_dict.items()):
            nds = NaiveDisjointSet()

            for i, j in positions:
                nds.merge(i, j+m)

            for values in nds.getGroups().values():
                maxRank = max(maxRank_list[i] for i in values)
                for i in values:
                    maxRank_list[i] = maxRank + 1

            for i, j in positions:
                ans[i][j] = maxRank_list[i]

        return ans
```

- [1268. Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/description/)

![](images/1268.png)

```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = None


class Solution:
    def suggestedProducts(self, products: list[str], searchWord: str) -> list[list[str]]:
        ans = []
        search_res = []
        root = TrieNode()

        def insert(word: str) -> None:
            cur_node = root

            for letter in word:
                cur_node = cur_node.children.setdefault(letter, TrieNode())

            cur_node.word = word

        def search(node: TrieNode | None) -> None:
            if not node or len(search_res) == 3:
                return

            if node.word:
                search_res.append(node.word)

            for letter in 'abcdefghijklmnopqrstuvwxyz':
                if letter in node.children:
                    search(node.children[letter])

        for product in products:
            insert(product)

        cur_node = root

        for letter in searchWord:
            if not cur_node or letter not in cur_node.children:
                cur_node = None
                ans.append([])
                continue

            cur_node = cur_node.children[letter]
            search_res = []
            search(cur_node)
            ans.append(search_res)

        return ans
```
