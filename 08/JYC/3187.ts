class SegmentTree {
  private n: number;
  private total: number[];

  constructor(n: number) {
    this.n = n;
    // Initialize the segment tree with zeros
    this.total = new Array(4 * n).fill(0);
  }

  update(idx: number, val: number, o: number, l: number, r: number): void {
    if (l === r) {
      // Leaf node
      this.total[o] = val;
      return;
    }

    const mid = Math.floor(l + (r - l) / 2);

    if (idx <= mid) {
      this.update(idx, val, 2 * o, l, mid);
    } else {
      this.update(idx, val, 2 * o + 1, mid + 1, r);
    }

    // Update current node value
    this.total[o] = this.total[2 * o] + this.total[2 * o + 1];
  }

  query(o: number, l: number, r: number, left: number, right: number): number {
    // If segment is out of range
    if (r < left || right < l) {
      return 0;
    }

    // If segment is fully within range
    if (left <= l && r <= right) {
      return this.total[o];
    }

    const mid = Math.floor(l + (r - l) / 2);
    let result = 0;

    if (left <= mid) {
      result += this.query(2 * o, l, mid, left, right);
    }

    if (mid + 1 <= right) {
      result += this.query(2 * o + 1, mid + 1, r, left, right);
    }

    return result;
  }
}

function countOfPeaks(nums: number[], queries: number[][]): number[] {
  const n = nums.length;
  const p = new SegmentTree(n);

  // Initialize the segment tree with initial peak counts
  for (let i = 1; i < n - 1; i++) {
    if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
      p.update(i + 1, 1, 1, 1, n); // using 1-based index for the tree
    }
  }

  const result: number[] = [];
  for (const q of queries) {
    if (q[0] === 1) {
      // Query type [1, li, ri]
      const [, left, right] = q;
      result.push(p.query(1, 1, n, left + 2, right));
    } else {
      // Update type [2, indexi, vali]
      const [, index, val] = q;
      nums[index] = val;

      // Check and update peak status at index and its neighbors
      if (1 <= index && index <= n - 2) {
        if (nums[index - 1] < nums[index] && nums[index] > nums[index + 1]) {
          p.update(index + 1, 1, 1, 1, n);
        } else {
          p.update(index + 1, 0, 1, 1, n);
        }
      }

      if (index >= 2) {
        const left = index - 1;
        if (nums[left - 1] < nums[left] && nums[left] > nums[left + 1]) {
          p.update(left + 1, 1, 1, 1, n);
        } else {
          p.update(left + 1, 0, 1, 1, n);
        }
      }

      if (index <= n - 3) {
        const right = index + 1;
        if (nums[right - 1] < nums[right] && nums[right] > nums[right + 1]) {
          p.update(right + 1, 1, 1, 1, n);
        } else {
          p.update(right + 1, 0, 1, 1, n);
        }
      }
    }
  }

  return result;
}
