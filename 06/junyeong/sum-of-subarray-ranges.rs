impl Solution {
    pub fn sub_array_ranges(mut nums: Vec<i32>) -> i64 {
        return Self::sum_max(&mut nums) - Self::sum_min(&mut nums);
    }

    pub fn sum_max(arr: &mut Vec<i32>) -> i64 {
        let mut stack: Vec<usize> = Vec::new();
        let mut sum: i64 = 0;
        let max_val: i32 = i32::MAX;
        arr.push(max_val);

        arr.iter()
            .enumerate()
            .for_each(|(idx, x)| {
                while !stack.is_empty() && arr[*stack.last().unwrap()] < *x {
                    let peak = stack.pop().unwrap();
                    let left = if stack.is_empty() {
                        peak + 1
                    } else {
                        peak - *stack.last().unwrap()
                    };
                    let right = idx - peak;
                    let count = (left * right) as i64;
                    sum = sum + (arr[peak] as i64) * count;
                }
                stack.push(idx);
            });
        arr.pop();
        return sum;
    }

    pub fn sum_min(arr: &mut Vec<i32>) -> i64 {
        let mut stack: Vec<usize> = Vec::new();
        let mut sum: i64 = 0;
        let min_val: i32 = i32::MIN;
        arr.push(min_val);

        arr.iter()
            .enumerate()
            .for_each(|(idx, x)| {
                while !stack.is_empty() && arr[*stack.last().unwrap()] > *x {
                    let peak = stack.pop().unwrap();
                    let left = if stack.is_empty() {
                        peak + 1
                    } else {
                        peak - *stack.last().unwrap()
                    };
                    let right = idx - peak;
                    let count = (left * right) as i64;
                    sum += (arr[peak] as i64) * count;
                }
                stack.push(idx);
            });
        arr.pop();
        return sum;
    }
}
