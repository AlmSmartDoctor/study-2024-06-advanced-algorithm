class Solution {
    public List<List<Integer>> getSkyline(int[][] buildings) {
        List<List<Integer>> result = new ArrayList<>();
        List<int[]> heights = new ArrayList<>();

        // Step 1: Convert buildings into events.
        for(int[] b:buildings) {
            // Add start event with negative height to distinguish from end event.
            heights.add(new int[]{b[0], -b[2]});
            // Add end event with positive height.
            heights.add(new int[]{b[1], b[2]});
        }

        // Step 2: Sort events.
        Collections.sort(heights, (a, b) -> {
            if(a[0] != b[0]) 
                return a[0] - b[0];
            // If same x coordinate, start event (-height) should come before end event (+height)
            return a[1] - b[1];
        });

        // Step 3: Max-heap to keep track of current heights.
        Queue<Integer> pq = new PriorityQueue<>((a, b) -> (b - a));
        pq.offer(0);
        int prevMaxheight = 0;

        // Step 4: Process each event.
        for(int[] height : heights) {
            int pos = height[0], h = height[1];
            if(h < 0) {
                // Start event: add the building height.
                pq.offer(-h);
            } else {
                // End event: remove the building height.
                pq.remove(h);
            }
            int currMaxheight = pq.peek();
            // If the max height changes, add a key point.
            if(prevMaxheight != currMaxheight) {
                result.add(Arrays.asList(pos, currMaxheight));
                prevMaxheight = currMaxheight;
            }
        }
        return result;
    }
}