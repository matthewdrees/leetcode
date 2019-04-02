class Solution:
    def twoSum(self, nums, target: int):
        # value -> index mapping
        d = {}
        for x in range(len(nums)):
            num = nums[x]
            ans = target - num
            if ans in d:
                return [d[ans], x]
            d[num] = x


if __name__ == '__main__':
    s = Solution()
    tests = (
        ([1, 1], 2, [0, 1]),
        ([2, 7], 9, [0, 1]),
        ([2, 7, 11, 15], 9, [0, 1]),
        ([2, 7, 11, 15], 13, [0, 2]),
        ([2, 7, 11, 15], 17, [0, 3]),
        ([2, 7, 11, 15], 18, [1, 2]),
        ([2, 7, 11, 15], 22, [1, 3]),
        ([2, 7, 11, 15], 26, [2, 3]),
    )
    for test in tests:
        nums = test[0]
        target = test[1]
        exp = test[2]
        ans = s.twoSum(nums, target)
        if exp != ans:
            print(
                f'FAIL. nums: {nums}, target: {target}, exp: {exp}, ans: {ans}'
            )
