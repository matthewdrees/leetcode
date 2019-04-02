import bisect
import itertools
import math
import sys


class Node:
    def __init__(self, num):
        self.num = num
        self.count = 1


class MedianFinderFlatMap:
    '''Use a flat map.'''

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.nums = []  # Ordered list of unique values.
        self.occurances = []  # Ordered list of unique values.
        self.numsIndex = 0  # Index of median value in nums.
        self.numIndex = 0  # Index of median value in occurances.
        self.total = 0  # Total numbers.

    def addNum(self, num: int) -> None:

        if (self.total == 0):
            self.nums.append(num)
            self.occurances.append(1)
            self.total = 1
            self.numIndex = 1
            return

        curMiddleNum = self.nums[self.numsIndex]
        if num < curMiddleNum:
            pos = bisect.bisect_left(self.nums, num, 0, self.numsIndex)
        elif num > curMiddleNum:
            pos = bisect.bisect_left(self.nums, num, self.numsIndex,
                                     len(self.nums))
        else:
            pos = self.numsIndex

        # Number not in nums.
        if pos == len(self.nums) or self.nums[pos] != num:
            self.nums.insert(pos, num)
            self.occurances.insert(pos, 1)
            if pos <= self.numsIndex:
                if self.numIndex > 1:
                    self.numIndex -= 1
                    self.numsIndex += 1
                elif self.occurances[self.numsIndex] > 1:
                    self.numIndex = self.occurances[self.numsIndex]

        # Number is already in nums.
        else:
            self.occurances[pos] += 1
            if pos < self.numsIndex:
                if self.numIndex > 1:
                    self.numIndex -= 1
                else:
                    self.numIndex = self.occurances[self.numsIndex - 1]
                    self.numsIndex -= 1

        totalWasOdd = self.total % 2 == 1
        if totalWasOdd:
            # Adjust upwards, either numIndex or numsIndex
            if self.numIndex < self.occurances[self.numsIndex]:
                self.numIndex += 1
            else:
                self.numsIndex += 1
                self.numIndex = 1
        self.total += 1

        #print(f'{num}, {curMiddleNum}, {self.nums}, {self.occurances}, {self.numsIndex}, {self.numIndex}, {self.total}')

    def findMedian(self) -> float:
        # If odd number of elements take the middle value...
        if self.total % 2 == 1:
            return float(self.nums[self.numsIndex])

        # ... else deal with even number of elements:
        elif self.total == 0:
            return 0.0
        elif self.numIndex > 1:
            return float(self.nums[self.numsIndex])
        else:
            return (self.nums[self.numsIndex - 1] + self.nums[self.numsIndex]
                    ) / 2.0


class MedianFinder:
    def __init__(self):
        """
        initialize your data structure here.
        """
        self.l = []

    def addNum(self, num: int) -> None:
        pos = bisect.bisect_left(self.l, num)
        self.l.insert(pos, num)

    def findMedian(self) -> float:
        if len(self.l) == 0:
            return 0.0
        midIndex = len(self.l) // 2
        if len(self.l) % 2 == 0:
            # Average middle 2.
            n1 = self.l[midIndex]
            n2 = self.l[midIndex - 1]
            return (n1 + n2) / 2.0
        # Just take the middle.
        return float(self.l[midIndex])


class SimpleMedianFinder:
    '''Gets the ball rolling. Too slow to submit though.'''

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.l = []

    def addNum(self, num: int) -> None:
        self.l.append(num)
        self.l.sort()

    def findMedian(self) -> float:
        if len(self.l) == 0:
            return 0.0
        midIndex = len(self.l) // 2
        if len(self.l) % 2 == 0:
            # Average middle 2.
            n1 = self.l[midIndex]
            n2 = self.l[midIndex - 1]
            return (n1 + n2) / 2.0
        # Just take the middle.
        return float(self.l[midIndex])


if __name__ == '__main__':

    testsFromScratch = (
        ([42], 42.0),
        ((2, 2), 2.0),
        ((3, 3, 3), 3.0),
        ((4, 4, 4, 4), 4.0),
        ((5, 5, 5, 5, 5), 5.0),
        ((1, 2), 1.5),
        ((1, 2, 3), 2.0),
        ((1, 1, 2), 1.0),
        ((1, 1, 1, 2), 1.0),
        ((1, 1, 2, 3), 1.5),
        ((1, 2, 2, 3), 2.0),
        ((1, 2, 3, 3), 2.5),
        ((1, 2, 3, 4), 2.5),
        ((1, 2, 2, 3, 4, 4), 2.5),
    )

    for test in testsFromScratch:

        nums = test[0]
        exp = test[1]
        for seq in itertools.permutations(nums):
            mf = MedianFinder()
            for num in seq:
                mf.addNum(num)
            ans = mf.findMedian()
            if not math.isclose(exp, ans, rel_tol=0.01):
                print(f'FAIL. nums: {nums}, exp: {exp}, ans: {ans}')
                sys.exit(1)

    tests = (
        (1, 1.0),
        (2, 1.5),
        (3, 2.0),
        (100, 2.5),
        (92, 3.0),
        (30, 16.5),
        (7, 7.0),
        (5, 6.0),
        (85, 7.0),
        (79, 18.5),
        (73, 30.0),
        (39, 34.5),
        (70, 39.0),
        (44, 41.5),
        (82, 44.0),
        (92, 57.0),
        (74, 70.0),
        (57, 63.5),
        (94, 70.0),
        (12, 63.5),
        (38, 57.0),
        (10, 50.5),
        (44, 44.0),
        (6, 44.0),
    )

    mf = MedianFinder()
    for test in tests:

        num = test[0]
        exp = test[1]
        mf.addNum(num)
        ans = mf.findMedian()
        if not math.isclose(exp, ans, rel_tol=0.01):
            print(f'FAIL. num: {num}, exp: {exp}, ans: {ans}')
