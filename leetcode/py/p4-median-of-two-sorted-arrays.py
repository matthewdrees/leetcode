"""leetcode.com problem 4. Median of Two Sorted Arrays.

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

Follow up: The overall run time complexity should be O(log (m+n)).
"""

import itertools
import math
import statistics
from typing import List


class BisectIndex:
    """Track an index for bisecting a collection with length n."""

    def __init__(self, low, high):
        self.right = high
        self.left = low
        self.index = (high + low) // 2

    def get_index(self):
        return self.index

    def go_left(self):
        if self.index <= self.left:
            return False
        self.right = self.index
        self.index -= (self.index - self.left + 1) // 2
        return True

    def go_right(self):
        if self.index >= self.right:
            return False
        self.left = self.index
        self.index += (self.right - self.index + 1) // 2
        return True


def calculate_bounds(nums1, nums2):
    len1 = len(nums1)
    len2 = len(nums2)
    bound = (len1 - len2) // 2
    if bound > 0:
        return bound, len1 - bound - 1
    return 0, len1 - 1


class Solution:
    def medianOfSortedArray(self, nums: List[int]) -> float:
        if len(nums) % 2 == 0:
            i = len(nums) // 2 - 1
            return statistics.mean(nums[i : i + 2])
        else:
            return float(nums[len(nums) // 2])

    def findMedianSortedArraysOdd(self, nums1: List[int], nums2: List[int]) -> float:

        # Put the odd list first.
        if len(nums1) % 2 == 0:
            nums1, nums2 = nums2, nums1
        assert len(nums1) % 2 == 1

        low, high = calculate_bounds(nums1, nums2)
        bi1 = BisectIndex(low, high)
        i2 = (len(nums2) - 1) // 2
        i2_low, i2_high = calculate_bounds(nums2, nums1)
        while True:
            i1 = bi1.get_index()
            if i2 < 0 or i2 >= len(nums2):
                return nums1[i1]
            if nums1[i1] < nums2[i2]:
                i2_high = i2
                if bi1.go_right():
                    i2 -= i1 - bi1.get_index()
                    continue
                else:
                    # number is in nums2
                    break

            # if i2 is last index in nums2:
            if i2 + 1 >= len(nums2):
                if nums1[i1] < nums2[i2]:
                    return nums2[i2]
                else:
                    return nums1[i1]

            if nums1[i1] > nums2[i2 + 1]:
                i2_low = i2 + 1
                if bi1.go_left():
                    i2 += bi1.get_index() - i1
                    continue
                else:
                    break

            return nums1[i1]

        return nums2[(i2_high + i2_low) // 2]

    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

        if len(nums1) == 0 and len(nums2) == 0:
            return None

        if (len(nums1) + len(nums2)) % 2 == 1:
            return self.findMedianSortedArraysOdd(nums1, nums2)
        return 1.0


def test_all_combinations(arr):
    """Test all combinations, making 2 arrays out of arr."""

    passed = True
    expected = statistics.median(arr)
    for len_arr_1 in range(len(arr) + 1):
        for l1_indexes in itertools.combinations(range(len(arr)), len_arr_1):
            l1 = []
            l2 = []
            for x in range(len(arr)):
                if x in l1_indexes:
                    l1.append(arr[x])
                else:
                    l2.append(arr[x])
            s = Solution()
            actual = s.findMedianSortedArrays(l1, l2)
            if expected is None:
                passed = actual is None
            else:
                if actual is None:
                    passed = False
                else:
                    passed = math.isclose(expected, actual, abs_tol=0.01)
            if not passed:
                print(
                    f"FAIL. findMedianSortedArrays({l1}, {l2}), exp: {expected}, ans: {actual}"
                )

    return passed


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
    # test_findMedianSortedArrays()
    s = Solution()
    print(s.findMedianSortedArrays([1, 3], [2, 4, 5]))
    test_all_combinations([1, 2, 3, 4, 5])
