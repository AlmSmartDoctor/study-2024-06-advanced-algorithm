class Solution {
    companion object {
        const val COUNT_ALPHABET = 'z' - 'a' + 1
    }

    val root = Node()
    val dr = intArrayOf(-1, 0, 1, 0)
    val dc = intArrayOf(0, -1, 0, 1)

    val visited = Array(COUNT_ALPHABET) { BooleanArray(COUNT_ALPHABET) { false } }

    fun findWords(board: Array<CharArray>, words: Array<String>): List<String> {
        // init
        for (r in board.indices) {
            for (c in board[r].indices) {
                root.addChild(board[r][c])
                val child = root.getChild(board[r][c])

                visited[r][c] = true
                dfs(board, r, c, child, 1)
                visited[r][c] = false
            }
        }

        return words.filter {
            isContainedInBoard(it)
        }.toList()
    }

    fun dfs(board: Array<CharArray>, r: Int, c: Int, parent: Node, depth: Int) {
        if (depth == 10) return

        (0 .. 3).map { d ->
            Pair(r + dr[d], c + dc[d])
        }.filter { (r, c) ->
            r in board.indices && c in board[r].indices
        }.filterNot { (r, c) ->
            visited[r][c]
        }.onEach { (r, c) ->

            parent.addChild(board[r][c])
            val child = parent.getChild(board[r][c])

            visited[r][c] = true
            dfs(board, r, c, child, depth + 1)
            visited[r][c] = false
        }
    }

    fun isContainedInBoard(word: String): Boolean {
        var node = root

        for (c in word) {
            if (!node.hasChild(c)) return false
            node = node.getChild(c)
        }
        
        return true
    }

    class Node {
        private val children = Array<Node?>(COUNT_ALPHABET) { null }

        fun hasChild(c: Char): Boolean {
            return children[c - 'a'] != null
        }

        fun addChild(c: Char) {
            if (!hasChild(c)) children[c - 'a'] = Node()
        }

        fun getChild(c: Char): Node {
            if (!hasChild(c)) throw Exception("No such child")
            return children[c - 'a']!!
        }
    }
}
