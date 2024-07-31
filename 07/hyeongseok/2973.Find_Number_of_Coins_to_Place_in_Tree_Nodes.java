class Solution {
    public long[] placedCoins(int[][] edges, int[] cost) {
        Map<Integer, List<Integer>> map = new HashMap<>();
        for(int[] edge: edges) {
            map.putIfAbsent(edge[0], new ArrayList());
            map.putIfAbsent(edge[1], new ArrayList());
            map.get(edge[0]).add(edge[1]);
            map.get(edge[1]).add(edge[0]);
        }
        int n = cost.length;
        long[] ans = new long[n];
        Arrays.fill(ans, 0l);
        boolean[] visited = new boolean[n];
        dfs(map, cost, ans, 0, visited);
        return ans;
    }

    public List<Integer> dfs(Map<Integer, List<Integer>> map, int[] cost, 
        long[] ans, int curr, boolean[] visited) {
        
        visited[curr] = true;

        List<Integer> temp = new ArrayList<>();
        for(int adj: map.get(curr)) {
            if(!visited[adj]) 
                temp.addAll(dfs(map, cost, ans, adj, visited));
        }
        temp.add(cost[curr]);
        Collections.sort(temp);

        int n = temp.size();
        if(n >= 3) {
            long left = (long) temp.get(0) * temp.get(1);
            long right = (long) temp.get(n-3) * temp.get(n-2);
            ans[curr] = Math.max(0, Math.max(left, right) * temp.get(n-1));
         } else {
            ans[curr] = 1;
        }
        
        if(n <= 5) return temp;
        
        return new ArrayList<>(Arrays.asList(temp.get(0), temp.get(1), 
            temp.get(n - 3), temp.get(n - 2), temp.get(n - 1)));
    }
}