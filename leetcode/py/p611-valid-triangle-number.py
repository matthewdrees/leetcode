# LeetCode problem 611. Valid Triangle Number.
import bisect
import math
from typing import List


class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        """Third take.

        1. Skip invalid numbers with range instead of bisect_left.
        2. Better hint for bounding the bisect_left call in invalid triangle search.

        Runtime beats 51% of other submissions. Fine. Probably need a smarter math attack at this point.
        """
        nums.sort()

        # Skip starting index past numbers < 1.
        start = 0
        for start in range(len(nums)):
            if nums[start] > 0:
                break

        # Calculate possible number of triangles.
        num_triangles = math.comb(len(nums) - start, 3)

        # Subtract off invalid triangles
        for a in range(start, len(nums) - 2):
            c = a + 2
            for b in range(a + 1, len(nums) - 1):
                c = bisect.bisect_left(nums, nums[a] + nums[b], c)
                if c == len(nums):
                    break
                num_triangles -= len(nums) - c
        return num_triangles

    def triangleNumber_take2(self, nums: List[int]) -> int:
        """Second take.

        Skip past invalid numbers rather than resize the list.

        Runtime beats 47% of other submissions."""
        nums.sort()

        # Skip starting index past numbers < 1.
        start = bisect.bisect_left(nums, 1)

        # Calculate possible number of triangles.
        num_triangles = math.comb(len(nums) - start, 3)

        # Subtract off invalid triangles
        for a in range(start, len(nums) - 2):
            for b in range(a + 1, len(nums) - 1):
                c = bisect.bisect_left(nums, nums[a] + nums[b], b + 1)
                if c == len(nums):
                    break
                num_triangles -= len(nums) - c
        return num_triangles

    def triangleNumber_take1(self, nums: List[int]) -> int:
        """First take. Runtime beats 45% of other submissions."""
        nums.sort()

        # Remove numbers < 1.
        nums = nums[bisect.bisect_left(nums, 1) :]

        # Calculate possible number of triangles.
        num_triangles = math.comb(len(nums), 3)

        # Subtract off invalid triangles
        for a in range(len(nums) - 2):
            for b in range(a + 1, len(nums) - 1):
                c = bisect.bisect_left(nums, nums[a] + nums[b], b + 1)
                if c == len(nums):
                    break
                num_triangles -= len(nums) - c
        return num_triangles


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], 0),
        ([1], 0),
        ([1, 2], 0),
        ([1, 1, 2], 0),
        ([1, 2, 0], 0),
        ([1, 2, 2], 1),
        ([1, 2, 2, 0], 1),
        ([2, 2, 3, 4], 3),
        ([4, 2, 3, 4], 4),
    )
    for nums, exp in tests:
        ans = s.triangleNumber(nums)
        if exp != ans:
            print(f"FAIL, nums: {nums}, exp: {exp}, ans: {ans}")
