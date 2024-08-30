struct Solution {}

impl Solution {
    fn backTracking(
        courseIdx: usize,
        forwardTracker: &Vec<Vec<usize>>,
        backTracker: &mut Vec<Vec<bool>>,
        tracked: &mut Vec<bool>
    ) {
        for postCourseIdx in forwardTracker[courseIdx].to_vec() {
            if !tracked[postCourseIdx] {
                Solution::backTracking(postCourseIdx, forwardTracker, backTracker, tracked);
            }
            backTracker[courseIdx][postCourseIdx] = true;
            for i in 0..backTracker.len() {
                backTracker[courseIdx][i] |= backTracker[postCourseIdx][i];
            }
        }
        tracked[courseIdx] = true;
    }

    pub fn check_if_prerequisite(
        num_courses: i32,
        prerequisites: Vec<Vec<i32>>,
        queries: Vec<Vec<i32>>
    ) -> Vec<bool> {
        let n = num_courses as usize;
        let mut res = Vec::new();
        if prerequisites.len() == 0 {
            return vec![false;queries.len()];
        }
        let mut forwardTracker = vec![vec![];n];
        for courses in prerequisites {
            let pre = courses[0] as usize;
            let post = courses[1] as usize;
            forwardTracker[pre].push(post);
        }

        let mut backTracker = vec![vec![false;n];n];
        let mut tracked = vec![false;n];
        for courseIdx in 0..n {
            if !tracked[courseIdx] {
                Solution::backTracking(courseIdx, &forwardTracker, &mut backTracker, &mut tracked);
            }
        }

        for q in queries {
            let pre = q[0] as usize;
            let post = q[1] as usize;
            res.push(backTracker[pre][post]);
        }
        res
    }
}
