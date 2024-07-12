class MedianFinder {
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;

   public:
    MedianFinder() {}

    void addNum(int num) {
        if (max_heap.size() == min_heap.size())
            max_heap.push(num);
        else
            min_heap.push(num);

        if (!max_heap.empty() && !min_heap.empty() &&
            max_heap.top() > min_heap.top()) {
            int max_temp = max_heap.top();
            int min_temp = min_heap.top();

            max_heap.pop();
            min_heap.pop();

            max_heap.push(min_temp);
            min_heap.push(max_temp);
        }
    }

    double findMedian() {
        if (max_heap.size() > min_heap.size()) return (double)max_heap.top();

        return (double)(max_heap.top() + min_heap.top()) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */