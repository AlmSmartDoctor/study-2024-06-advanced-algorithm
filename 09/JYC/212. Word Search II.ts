class TrieNode {
  private nodes = new Map<string, TrieNode>();
  word: string | null = null;

  insert(word: string) {
    let curr = this as TrieNode;
    for (const char of word) {
      if (!curr.nodes.has(char)) {
        curr.nodes.set(char, new TrieNode());
      }
      curr = curr.nodes.get(char);
    }
    curr.word = word;
  }

  hasChar(char: string) {
    return this.nodes.has(char);
  }

  getNode(char: string): TrieNode | null {
    return this.nodes.get(char);
  }
}

function search(
  m: number,
  n: number,
  board: string[][],
  node: TrieNode,
  result: Set<string>
) {
  const M = board.length;
  const N = board[0].length;

  if (m < 0 || n < 0 || m >= M || n >= N) return;

  const currChar = board[m][n];
  if (currChar === "#" || !node.hasChar(currChar)) return;

  node = node.getNode(currChar);

  if (node.word) {
    result.add(node.word);
    node.word = null;
  }

  board[m][n] = "#";

  const directions = [
    [1, 0],
    [0, 1],
    [0, -1],
    [-1, 0],
  ];

  for (const [dx, dy] of directions) {
    search(m + dx, n + dy, board, node, result);
  }

  board[m][n] = currChar;
}

function findWords(board: string[][], words: string[]): string[] {
  const root = new TrieNode();

  for (const word of words) {
    root.insert(word);
  }

  const result = new Set<string>();

  for (let i = 0; i < board.length; i++) {
    for (let j = 0; j < board[0].length; j++) {
      search(i, j, board, root, result);
    }
  }

  return Array.from(result);
}
