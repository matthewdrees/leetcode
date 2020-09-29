class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        nums = []
        while x != 0:
            nums.append(x % 10)
            x = x // 10
        for x in range(len(nums) // 2):
            if nums[x] != nums[len(nums) - 1 - x]:
                return False
        return True


if __name__ == '__main__':

    s = Solution()
    tests = (
        (121, True),
        (1221, True),
        (2147483647, False),
        (2147447412, True),
        (214747412, True),
        (0, True),
        (9, True),
        (10, False),
        (-121, False),
    )

    for test in tests:

        num = test[0]
        exp = test[1]
        ans = s.isPalindrome(num)
        if exp != ans:
            print(f'FAIL. s: {num}, exp: {exp}, ans: {ans}')
