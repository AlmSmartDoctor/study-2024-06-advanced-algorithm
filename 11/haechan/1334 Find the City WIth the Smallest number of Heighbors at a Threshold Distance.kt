class Solution {
    fun findTheCity(n: Int, edges: Array<IntArray>, distanceThreshold: Int): Int {
        val distanceArray = getDistanceArrayByFloydWarshall(n, edges)

        return (0 until n).map { i ->
            (0 until n).count { j ->
                i != j && distanceArray[i][j] <= distanceThreshold
            }.let { count ->
                Pair(i, count)
            }
        }.sortedWith(
            compareBy(
                { it.second },
                { -it.first },
            )
        ).first().first
    }

    fun getDistanceArrayByFloydWarshall(n: Int, edges: Array<IntArray>): Array<IntArray> {
        val distanceArray = Array(n) { IntArray(n) { 123456789 } }

        (0 until n).forEach { distanceArray[it][it] = 0 }
        edges.forEach { (i, j, distance) ->
            distanceArray[i][j] = distance
            distanceArray[j][i] = distance
        }

        (0 until n).forEach { k ->
            (0 until n).forEach { i ->
                (0 until n).forEach { j ->
                    distanceArray[i][j] = Math.min(distanceArray[i][j], distanceArray[i][k] + distanceArray[k][j])
                }
            }
        }

        return distanceArray
    }
}
