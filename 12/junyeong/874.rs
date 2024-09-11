use std::collections::HashSet;

impl Solution {
    pub fn robot_sim(commands: Vec<i32>, obstacles: Vec<Vec<i32>>) -> i32 {
        let mut ans = 0;
        let mut x = 0;
        let mut y = 0;
        let mut direction = 0;
        let mut obstacle_set = HashSet::new();

        for obstacle in obstacles {
            obstacle_set.insert((obstacle[0], obstacle[1]));
        }

        for command in commands {
            if command == -1 {
                direction = (direction + 1) % 4;
            } else if command == -2 {
                direction = (direction + 3) % 4;
            } else {
                for _d in 0..command {
                    let prev_x = x;
                    let prev_y = y;
                    match direction {
                        0 => {
                            y += 1;
                        }
                        1 => {
                            x += 1;
                        }
                        2 => {
                            y -= 1;
                        }
                        3 => {
                            x -= 1;
                        }
                        _ => (),
                    }
                    if obstacle_set.contains(&(x, y)) {
                        x = prev_x;
                        y = prev_y;
                        break;
                    }
                    ans = ans.max(x * x + y * y);
                }
            }
        }

        ans
    }
}
