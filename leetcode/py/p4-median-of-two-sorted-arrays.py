"""leetcode.com problem 4. Median of Two Sorted Arrays.

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

Follow up: The overall run time complexity should be O(log (m+n)).
"""

import math
import statistics
from typing import List


class Solution:
    def medianOfSortedArray(self, nums: List[int]) -> float:
        if len(nums) % 2 == 0:
            i = len(nums) // 2 - 1
            return statistics.mean(nums[i : i + 2])
        else:
            return float(nums[len(nums) // 2])

    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

        # One or both are empty
        if len(nums1) == 0 and len(nums2) == 0:
            return None
        if len(nums1) == 0:
            return self.medianOfSortedArray(nums2)
        if len(nums2) == 0:
            return self.medianOfSortedArray(nums1)

        # Odd number of elements

        # Start off in middle of each.

        # Whichever number is bigger, set ranges, from that number to end.


def test_findMedianSortedArrays():

    tests = (
        ([], [], None),
        ([1], [], 1.0),
        ([], [1], 1.0),
        ([1], [1], 1.0),
        ([1], [2], 1.5),
        ([2], [1], 1.5),
    )

    s = Solution()
    for t in tests:
        expected = t[2]
        actual = s.findMedianSortedArrays(t[0], t[1])
        if expected is None:
            passed = actual is None
        else:
            if actual is None:
                passed = False
            else:
                passed = math.isclose(expected, actual, abs_tol=0.01)
        if not passed:
            print(
                f"FAIL. findMedianSortedArrays({t[0]}, {t[1]}), exp: {expected}, ans: {actual}"
            )


if __name__ == "__main__":
    test_findMedianSortedArrays()