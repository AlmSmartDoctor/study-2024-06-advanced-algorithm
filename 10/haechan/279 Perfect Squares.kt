import java.util.*

class Solution {
    
    fun numSquares(n: Int): Int {
        val queue = PriorityQueue<Pair<Int, Int>>() { p1, p2 -> p1.second - p2.second }
        queue.add(Pair(0, 0))
        
        while (!queue.isEmpty()) {
            val (k, depth) = queue.remove()

            if (k == n) return depth

            (100 downTo 1).filter {
                (n - k) / (it * it) > 0
            }.forEach {
                queue.add(Pair(k + it * it * ((n - k) / (it *  it)), depth + (n - k) / (it *  it)))
            }
        }
        
        return throw Exception("정답을 찾지 못함")
    }
}
