from typing import List

# https://www.geeksforgeeks.org/trie-insert-and-search/
class TrieNode:
    def __init__(self):
        self.child = [None] * 26
        self.word_end = False

        self.suggestions = []        

def insert_key(root: TrieNode, key: str):
    curr = root

    for c in key:
        index = ord(c) - ord('a')
        
        if curr.child[index] is None:
            curr.child[index] = TrieNode()
        
        curr = curr.child[index]
        
        if len(curr.suggestions) < 3:
            curr.suggestions.append(key)
            curr.suggestions.sort()
        else:
            if key < curr.suggestions[-1]:
                curr.suggestions[-1] = key
                curr.suggestions.sort()
                
    curr.word_end = True

def getSuggestions(root: TrieNode, prefix: str) -> List[List[str]]:
    curr = root
    result = []

    for c in prefix:
        index = ord(c) - ord('a')
        if curr.child[index] is None:
            break
        curr = curr.child[index]
        result.append(curr.suggestions)

    while len(result) < len(prefix):
        result.append([])

    return result

class Solution:
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        products.sort()
        
        root = TrieNode()
        for product in products:
            insert_key(root, product)
        
        return getSuggestions(root, searchWord)
