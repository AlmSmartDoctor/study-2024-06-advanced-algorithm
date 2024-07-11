function largestRectangleArea(heights: number[]): number {
    // Store (index, height)
    const stack: number[][] = [];
    let maxArea = 0;

    heights.forEach((h, i) => {
        let start = i;
        
        // previous greater height cannot be expanded after smaller height appears
        // pop all height in stack greater than current height and update Area
        // stack stores heights in ascending order
        while (stack.length > 0 && stack[stack.length - 1][1] > h) {
            const lastItem = stack.pop()
            const index = lastItem[0]
            const height = lastItem[1]
            maxArea = Math.max(maxArea, height * (i - index));

            start = index;
        }

        stack.push([start, h]);
    });

    // find candidate area on remaining stack
    stack.forEach(item => 
        maxArea = Math.max(maxArea, item[1] * (heights.length - item[0]))
    );

    return maxArea;
};