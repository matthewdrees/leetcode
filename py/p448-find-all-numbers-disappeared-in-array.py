class Solution:
    def findDisappearedNumbers(self, nums):
        """Track number counts in a separate list.

        This turned out to be the fastest (and simplest).
        """
        l = [0] * (len(nums) + 1)
        for n in nums:
            l[n] += 1

        return [n for n in range(1, len(l)) if l[n] == 0]


class Solution3:
    def findDisappearedNumbers(self, nums):
        """Stolen from 'Discuss' section by yang2007chun.

        Clever, but leaves nums negative after the call. Jarring!

        :type nums: List[int]
        :rtype: List[int]
        """
        # For each number i in nums,
        # we mark the number that i points as negative.
        # Then we filter the list, get all the indexes
        # who points to a positive number
        for i in range(len(nums)):
            index = abs(nums[i]) - 1
            nums[index] = -abs(nums[index])

        return [i + 1 for i in range(len(nums)) if nums[i] > 0]


class Solution2:
    def findDisappearedNumbers(self, nums):
        l = []
        s = set(nums)
        for x in range(1, len(nums) + 1):
            if x not in s:
                l.append(x)

        return l


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([], []),
        ([1], []),
        ([1, 1], [2]),
        ([2, 2], [1]),
        ([1, 1, 1], [2, 3]),
        ([4, 3, 2, 7, 8, 2, 3, 1], [5, 6]),
    )

    for test in tests:
        nums = test[0]
        exp = test[1]
        ans = s.findDisappearedNumbers(nums)
        if exp != ans:
            print(f'FAIL. nums: {nums}, exp: {exp}, ans: {ans}')
