class Solution:
    def sortedSquares(self, A):
        squares = []
        for n in A:
            squares.append(n * n)
        squares.sort()
        return squares


class Solution2:
    def sortedSquares(self, A):
        for x in range(len(A)):
            A[x] = A[x]**2
        return sorted(A)


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([], []),
        ([0], [0]),
        ([-1], [1]),
        ([2], [4]),
        ([-4, -1, 0, 3, 10], [0, 1, 9, 16, 100]),
    )

    for test in tests:
        nums = test[0]
        exp = test[1]
        ans = s.sortedSquares(nums)
        if exp != ans:
            print(f'FAIL. nums: {nums}, exp: {exp}, ans: {ans}')
