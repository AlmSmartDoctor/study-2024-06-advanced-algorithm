class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int sgas = 0, scost = 0, total = 0, res = 0;
        for(int i = 0; i < gas.length; i++) {
            sgas += gas[i];
            scost += cost[i];
        }
        
        if (sgas < scost) return -1;

        for(int i = 0; i < gas.length; i++) {
            total += gas[i] - cost[i];
            if (total < 0) {
                total = 0;
                res = i + 1;
            }
        }

        return res;
    }
}