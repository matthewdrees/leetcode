class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows >= len(s) or numRows < 2:
            return s
        ret = ''
        biggestGap = (numRows - 1) * 2

        # Handle first row
        for x in range(0, len(s), biggestGap):
            ret += s[x]

        # Middle rows alternate gaps.
        nextGap = biggestGap - 2
        for numRow in range(1, numRows - 1):
            x = numRow
            gap = nextGap
            while x < len(s):
                ret += s[x]
                x += gap
                gap = biggestGap - gap
            nextGap -= 2

        # Handle last row
        for x in range(numRows - 1, len(s), biggestGap):
            ret += s[x]

        return ret


if __name__ == '__main__':

    s = Solution()
    tests = (
        ("", 0, ""),
        ("", 1, ""),
        ("a", 1, "a"),
        ("ab", 1, "ab"),
        ("a", 2, "a"),
        ("ab", 2, "ab"),
        ("abc", 2, "acb"),
        ("abcd", 2, "acbd"),
        ("abcde", 2, "acebd"),
        ("a", 3, "a"),
        ("ab", 3, "ab"),
        ("abc", 3, "abc"),
        ("abcd", 3, "abdc"),
        ("abcde", 3, "aebdc"),
        ("abcdef", 3, "aebdfc"),
        ("a", 4, "a"),
        ("ab", 4, "ab"),
        ("abc", 4, "abc"),
        ("abcd", 4, "abcd"),
        ("abcde", 4, "abced"),
        ("abcdef", 4, "abfced"),
        ("abcdefg", 4, "agbfced"),
        ("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"),
        ("PAYPALISHIRING", 4, "PINALSIGYAHRPI"),
    )

    for test in tests:
        string = test[0]
        numRows = test[1]
        exp = test[2]
        ans = s.convert(string, numRows)
        if exp != ans:
            print(
                f'FAIL. s: {string}, numRows: {numRows}, exp: {exp}, ans: {ans}'
            )
