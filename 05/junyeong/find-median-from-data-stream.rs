use std::collections::BinaryHeap;

struct MedianFinder {
    max: BinaryHeap<i32>,
    min: BinaryHeap<i32>,
}

impl MedianFinder {
    fn new() -> Self {
        MedianFinder {
            max: BinaryHeap::new(),
            min: BinaryHeap::new(),
        }
    }

    fn add_num(&mut self, mut num: i32) {
        if self.max.len() > self.min.len() {
            self.max.push(num);
            num = self.max.pop().unwrap();
            self.min.push(-num);
        } else {
            self.min.push(-num);
            num = -self.min.pop().unwrap();
            self.max.push(num);
        }
    }

    fn find_median(&self) -> f64 {
        if self.max.len() > self.min.len() {
            *self.max.peek().unwrap() as f64
        } else {
            ((*self.max.peek().unwrap() - *self.min.peek().unwrap()) as f64) / 2.0
        }
    }
}
