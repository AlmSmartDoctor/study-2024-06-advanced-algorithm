object FindMin {
    fun minInteger(num: String, _k: Int): String {
        if (_k <= 0) return num

        var sb = StringBuilder(num)
        var k = _k

        (0 until num.length).forEach { i ->

            var v: Int? = null

            (i until num.length).forEach { j ->
                if (j - i <= k && (v == null || sb[j] < sb[v!!])) {
                    v = j
                }
            }

            if (v != null) {
                val tmp = sb[v!!]
                sb = sb.deleteAt(v!!).insert(i, tmp)
                k -= v!! - i
            }
        }

        return sb.toString()
    }
}
