import PriorityQueue

class MedianFinder {
    minHeap;
    maxHeap;
    constructor() {
        this.minHeap = new PriorityQueue({
            compare: (a, b) => a - b,
        })
        this.maxHeap = new PriorityQueue({
            compare: (a, b) => b - a,
        })
    }

    addNum(num: number): void {
        if (this.maxHeap.size() === 0 || this.maxHeap.front() >= num) {
            this.maxHeap.enqueue(num);
        } else {
            this.minHeap.enqueue(num);
        }

        // balancing the two heaps
        if (this.maxHeap.size() > this.minHeap.size() + 1) {
            this.minHeap.enqueue(this.maxHeap.dequeue());
        } else if (this.minHeap.size() > this.maxHeap.size()) {
            this.maxHeap.enqueue(this.minHeap.dequeue());
        }
    }

    findMedian(): number {
        if (this.minHeap.size() == this.maxHeap.size()) {
            return (this.minHeap.front() + this.maxHeap.front()) / 2;
        } else return this.maxHeap.front();
    }
}