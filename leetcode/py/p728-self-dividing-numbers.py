class Solution:
    def selfDividingNumbers(self, left: int, right: int):
        output = []
        for n in range(left, right + 1):
            alldivisible = True
            for c in str(n):
                if c == '0':
                    alldivisible = False
                    break
                if n % int(c) != 0:
                    alldivisible = False
                    break
            if alldivisible:
                output.append(n)
        return output


if __name__ == '__main__':
    s = Solution()
    tests = (
        (10, 10, []),
        (1, 1, [1]),
        (1, 22, [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]),
    )

    for test in tests:

        left = test[0]
        right = test[1]
        exp = test[2]
        ans = s.selfDividingNumbers(left, right)
        if exp != ans:
            print(f'FAIL. n1: {left}, n2: {right}, exp: "{exp}", ans: "{ans}"')
