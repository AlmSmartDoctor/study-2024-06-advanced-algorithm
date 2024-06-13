// sol 1. sort and select kth from back
// class Solution {
//     public int findKthLargest(int[] nums, int k) {
//         Arrays.sort(nums);
//         return nums[nums.length - k];
//     }
// }

// sol 2. Using frequency map, deduct count from k while decreasing max
class Solution {
    public int findKthLargest(int[] nums, int k) {
        int max = Integer.MIN_VALUE;
        Map<Integer, Integer> map = new HashMap<>();
        for(int num : nums) {
            map.put(num, map.getOrDefault(num, 0) + 1);
            max = Math.max(max, num);
        }

        if (map.size() == 1) return max;
        
        k -= map.get(max);
        while(k > 0) {
            max--;
            if(map.containsKey(max)) {
                k -= map.get(max);
            }
        }
        return max;
    }
}

// sol 3. quick select