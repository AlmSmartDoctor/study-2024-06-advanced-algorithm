import java.util.*
import kotlin.math.*

class Solution {
    lateinit var stack: Stack<Int>

    fun longestCycle(edges: IntArray): Int {
        val visited = BooleanArray(edges.size) { false }
        var longestCycle = -1
        
        for (i in edges.indices) {
            stack = Stack<Int>().apply {
                push(i)
            }

            while (stack.isNotEmpty()) {
                val current = stack.peek()

                visited[current] = true

                val next = edges[current]
                if (next == -1) break

                if (visited[next]) {
                    if (stack.contains(next)) {
                        var count = 1
                        while (stack.pop() != next) {
                            count++
                        }
                        longestCycle = max(longestCycle, count)
                    }
                    break
                }

                stack.push(next)
            }
        }

        return longestCycle
    }
}
