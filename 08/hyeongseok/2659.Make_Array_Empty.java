// class Solution {
//     int[] seg;
//     void init(int index, int start, int end) {
//         if (start == end) {
//             seg[index] = 1;
//             return;
//         }
//         int mid = (start + end) / 2;
//         init(2 * index, start, mid);
//         init(2 * index + 1, mid + 1, end);
//         seg[index] = seg[2 * index] + seg[2 * index + 1];
//     }
//     int query(int index, int start, int end, int left, int right) {
//         if (left > right) return 0;
//         if (right < start || left > end) return 0;
//         if (left <= start && end <= right) return seg[index];
//         int mid = (start + end) / 2;
//         int l = query(index * 2, start, mid, left, right);
//         int r = query(index * 2 + 1, mid + 1, end, left, right);
//         return l + r; 
//     }
//     void update(int index, int start, int end, int pos) {
//         if (pos < start || pos > end) return;
//         if (pos == start && pos == end) {
//             seg[index] = 0;
//             return;
//         }
//         int mid = (start + end) / 2;
//         update(index * 2, start, mid, pos);
//         update(index * 2 + 1, mid + 1, end, pos);
//         seg[index] = seg[2*index] + seg[2*index + 1];
//     }
//     public long countOperationsToEmptyArray(int[] nums) {
//         int n = nums.length;
//         int[][] numsI = new int[n][2];
//         for(int i = 0; i < n; i++) {
//             numsI[i][0] = nums[i];
//             numsI[i][1] = i;
//         }
//         Arrays.sort(numsI, (a, b) -> (a[0] - b[0]));
//         seg = new int[4 * n];
//         init(1, 0, n-1);
//         int prev = -1;
//         int index = 0;
//         long ans = 0;
//     }
// }

class Solution {
  public long countOperationsToEmptyArray(int[] A) {
      Map<Integer, Integer> pos = new HashMap<>();
      long n = A.length, res = n;
      for (int i = 0; i < n; ++i)
          pos.put(A[i], i);
      Arrays.sort(A);
      for (int i = 1; i < n; ++i)
          if (pos.get(A[i]) < pos.get(A[i - 1]))
              res += n - i;
      return res;
  }
}