class Solution:
    def getRow(self, rowIndex: int):
        if rowIndex == 0:
            return [1]
        l = [1, 1]
        for x in range(1, rowIndex):
            new_l = [1]
            for y in range(len(l) - 1):
                new_l.append(l[y] + l[y + 1])
            new_l.append(1)
            l = new_l

        return l


if __name__ == '__main__':
    s = Solution()
    tests = (
        (0, [1]),
        (1, [1, 1]),
        (2, [1, 2, 1]),
        (3, [1, 3, 3, 1]),
        (4, [1, 4, 6, 4, 1]),
        (5, [1, 5, 10, 10, 5, 1]),
        (6, [1, 6, 15, 20, 15, 6, 1]),
        (7, [1, 7, 21, 35, 35, 21, 7, 1]),
        (8, [1, 8, 28, 56, 70, 56, 28, 8, 1]),
        (9, [1, 9, 36, 84, 126, 126, 84, 36, 9, 1]),
    )
    for test in tests:
        rowIndex = test[0]
        exp = test[1]
        ans = s.getRow(rowIndex)
        if exp != ans:
            print(f'FAIL. {rowIndex}: exp: {exp}, ans: {ans}')
