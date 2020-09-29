class Solution:
    def maxArea(self, height) -> int:
        x = 0
        y = len(height) - 1
        max_area = 0
        while x != y:
            area = min(height[x], height[y]) * (y - x)
            max_area = max(area, max_area)
            if height[x] < height[y]:
                x += 1
            else:
                y -= 1
        return max_area

    def maxArea2(self, height) -> int:
        max_area = 0
        for x in range(len(height) - 1):
            for y in range(x + 1, len(height)):
                area = min(height[x], height[y]) * (y - x)
                max_area = max(area, max_area)
        return max_area


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([1, 1], 1),
        ([2, 2], 2),
        ([1, 2], 1),
        ([2, 1], 1),
        ([1, 2, 3], 2),
        ([1, 3, 2], 2),
        ([2, 1, 3], 4),
        ([2, 3, 1], 2),
        ([3, 1, 2], 4),
        ([3, 2, 1], 2),
        ([1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
        ([7, 6, 4, 3, 1], 9),
        ([1, 2, 3, 2, 1], 4),
    )

    for test in tests:

        heights = test[0]
        exp = test[1]
        ans = s.maxArea(heights)
        if exp != ans:
            print(f'FAIL. height: {heights}, exp: {exp}, ans: {ans}')
