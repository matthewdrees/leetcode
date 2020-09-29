import bisect
import collections


class Solution:
    def threeSum(self, nums):
        '''Copied from solutions to see it with my own eyes. 99.6% runtime.'''
        triplets = []
        if len(nums) < 3:
            return triplets
        num_freq = collections.Counter(nums)
        nums = sorted(num_freq)

        max_num = nums[-1]
        nums = nums[bisect.bisect_left(nums, -2 * max_num):]
        for i, v in enumerate(nums):
            if num_freq[v] >= 2:
                if v == 0 and num_freq[v] >= 3:
                    triplets.append([v] * 3)
                else:
                    complement = -2 * v
                    if complement in num_freq and complement != v:
                        triplets.append([v] * 2 + [complement])
            if v < 0:
                two_sum = -v
                lb = bisect.bisect_left(nums, two_sum - max_num, i + 1)
                ub = bisect.bisect(nums, two_sum // 2, lb)
                # lower/up bound
                for u in nums[lb:ub]:
                    complement = two_sum - u
                    if complement in num_freq and u != complement:
                        triplets.append([v, u, complement])
        return triplets


class Solution4:
    def threeSum(self, nums):
        '''My best effort, 97% runtime.'''
        posNums = sorted(n for n in nums if n > 0)
        posNumsSet = set(posNums)
        negNums = sorted(n for n in nums if n < 0)
        negNumsSet = set(negNums)
        numZeros = sum(1 for n in nums if n == 0)
        s = set()
        for x in range(len(posNums) - 1):
            for y in range(x + 1, len(posNums)):
                negNum = -posNums[x] - posNums[y]
                if negNum in negNumsSet:
                    s.add((negNum, posNums[x], posNums[y]))

        for x in range(len(negNums) - 1):
            for y in range(x + 1, len(negNums)):
                posNum = -negNums[x] - negNums[y]
                if posNum in posNumsSet:
                    s.add((negNums[x], negNums[y], posNum))

        if numZeros > 0:
            if numZeros > 2:
                s.add((0, 0, 0))
            if len(negNums) < len(posNums):
                for negNum in negNumsSet:
                    if -negNum in posNums:
                        s.add((negNum, 0, -negNum))
            else:
                for posNum in posNums:
                    if -posNum in negNumsSet:
                        s.add((-posNum, 0, posNum))

        return [list(t) for t in s]


class Solution3:
    def threeSum(self, nums):
        nums.sort()
        s = set()
        for left in range(len(nums) - 2):
            right = len(nums) - 1
            ans = -(nums[left] + nums[right])
            mid = bisect.bisect_left(nums, ans, left + 1, right)
            while left < mid and mid < right:
                if ans == nums[mid]:
                    s.add((nums[left], nums[mid], nums[right]))
                    right -= 1
                elif ans < nums[mid]:
                    right -= 1
                else:  # ans > nums[mid]:
                    mid += 1
                ans = -(nums[left] + nums[right])

        return [list(t) for t in s]


class Solution2:
    def threeSum(self, nums):
        nums.sort()
        s = set()
        for x in range(len(nums) - 2):
            for y in range(x + 1, len(nums) - 1):
                for z in range(y + 1, len(nums)):
                    if nums[x] + nums[y] + nums[z] == 0:
                        s.add((nums[x], nums[y], nums[z]))
        return [list(t) for t in sorted(s)]


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([0, 0, 0], [[0, 0, 0]]),
        ([1, 0, -1], [[-1, 0, 1]]),
        ([2, -1, -1], [[-1, -1, 2]]),
        ([1, -1, 0, 2], [[-1, 0, 1]]),
        ([3, 1, -1, 0], [[-1, 0, 1]]),
        ([1, -2, -1, 0], [[-1, 0, 1]]),
        ([1, -1, -2, 0], [[-1, 0, 1]]),
        ([1, -1, 2, -1, 0], [[-1, -1, 2], [-1, 0, 1]]),
        ([-1, 0, 1, 2, -1, -4], [[-1, -1, 2], [-1, 0, 1]]),
        ([-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6],
         [[-4, -2, 6], [-4, 0, 4], [-4, 1, 3], [-2, -2, 4], [-2, 0, 2],
          [2, 2, -4]]),
    )

    for test in tests:

        nums = test[0]
        exp = test[1]
        ans = s.threeSum(nums)
        grr = 2
        if exp != ans:
            print(f'FAIL. nums: {nums}, exp: {exp}, ans: {ans}')
