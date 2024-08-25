import java.util.*

class Solution {
    fun findCheapestPrice(n: Int, _flights: Array<IntArray>, src: Int, dst: Int, k: Int): Int {
        val isVisited = Array(n) { BooleanArray(k + 2) { false} }
        val flights = _flights.groupBy { it[0] }
        val pq = PriorityQueue<Node> { n1, n2 -> n1.price - n2.price }.apply {
            add(Node(src, 0, 0, setOf()))
        }
        while (pq.isNotEmpty()) {
            val (number, price, stop, route) = pq.remove()

            if (stop > k + 1 || isVisited[number][stop]) continue
            isVisited[number][stop] = true

            if (number == dst) {
                return price
            }

            flights[number]?.filterNot { (_, nextNumber, _) ->
                route.contains(nextNumber)
            }?.forEach { (_, nextNumber, cost) ->
                pq.add(Node(nextNumber, price + cost, stop + 1, route.toMutableSet().apply { add(number) }))
            }
        }

        return -1
    }
}

data class Node(
    val number: Int,
    val price: Int,
    val stop: Int,
    val route: Set<Int>,
)
