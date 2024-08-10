import kotlin.math.min
import kotlin.math.max

class Solution {
    lateinit var parent: IntArray

    fun findRedundantConnection(edges: Array<IntArray>): IntArray {
        for (i in edges.indices.reversed()) {
            parent = IntArray(edges.size + 1) { it }
            
            val (start, end) = edges[i]
            edges[i] = intArrayOf(-1, -1)
            if (!hasCycle(edges)) return intArrayOf(start, end)
            edges[i] = intArrayOf(start, end)
        }
        throw Exception("No Answer")
    }
    
    fun hasCycle(edges: Array<IntArray>): Boolean {
        for ((start, end) in edges) {
            if (start == -1 && end == -1) continue // removed edge
            
            if (find(start) == find(end)) return true
            union(start, end)
        }
        return false
    }

    fun union(a: Int, b: Int) {
        val c = find(a)
        val d = find(b)

        parent[min(c, d)] = max(c, d)
    }

    fun find(a: Int): Int {
        if (parent[a] == a) return a

        return find(parent[a]).also {
            parent[a] = it
        }
    }
}
