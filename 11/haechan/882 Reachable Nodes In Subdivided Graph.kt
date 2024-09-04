import java.util.PriorityQueue

object ReachableNodesInSubdividedGraph {
    fun main(edges: Array<IntArray>, maxMoves: Int, n: Int): Int {

        val visited = BooleanArray(n) { false }

        val bNodeManager = BNodeManager()

        edges.forEach { (a, b, distance) ->
            bNodeManager.initialize(a, b, distance)
            bNodeManager.initialize(b, a, distance)
        }

        val pq = PriorityQueue<Node>().apply {
            add(Node(0, 0))
        }

        while (pq.isNotEmpty()) {
            val (currentIndex, currentDistance) = pq.remove()

            if (currentDistance > maxMoves) break

            if (visited[currentIndex]) continue
            visited[currentIndex] = true

            bNodeManager.getAll(currentIndex)
                .forEach { (nextIndex, nodeBetween) ->

                    bNodeManager.set(currentIndex, nextIndex, maxMoves - currentDistance)

                    pq.add(Node(nextIndex, currentDistance + nodeBetween.distance + 1))
                }
        }

        val countReachableNode = visited.count { it }
        val countReachableBNode = (0 .. n).flatMap { i ->
            bNodeManager.getAll(i)
                .filter {
                    i < it.first
                }.map {
                    it.second
                }
        }.sumOf {
            (it.fromSmall + it.fromLarge).coerceAtMost(it.distance)
        }
        return countReachableNode + countReachableBNode
    }
}

data class Node(
    var index: Int,
    var distance: Int,
): Comparable<Node> {
    override fun compareTo(other: Node): Int {
        return distance - other.distance
    }
}

data class BNode(
    val distance: Int,
    var fromSmall: Int = 0,
    var fromLarge: Int = 0,
)

class BNodeManager {
    private val bNodeMap = mutableMapOf<Int, MutableMap<Int, BNode>>()

    fun get(i: Int, j: Int): BNode {
        return bNodeMap[i]!![j]!!
    }

    fun getAll(i: Int): List<Pair<Int, BNode>> {
        return bNodeMap[i]?.toList() ?: emptyList()
    }

    fun set(i: Int, j: Int, distance: Int) {
        get(Math.min(i, j), Math.max(i, j)).run {
            if (i < j) {
                fromSmall = fromSmall.coerceAtLeast(distance)
            } else {
                fromLarge = fromLarge.coerceAtLeast(distance)
            }
        }
    }

    fun initialize(i: Int, j: Int, distance: Int) {
        if (!bNodeMap.containsKey(i)) bNodeMap[i] = mutableMapOf()
        bNodeMap[i]!![j] = BNode(distance)
    }
}
