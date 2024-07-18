class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        stack = []
        max_area = 0
        
        for height in heights:
            width_accumulator = 0
            while stack and stack[-1][1] >= height:
                width, prev_height = stack.pop()
                width_accumulator += width
                current_area = width_accumulator * prev_height
                if current_area > max_area:
                    max_area = current_area
            
            stack.append((width_accumulator + 1, height))
        
        width_accumulator = 0
        while stack:
            width, height = stack.pop()
            width_accumulator += width
            current_area = width_accumulator * height
            if current_area > max_area:
                max_area = current_area
        
        return max_area
