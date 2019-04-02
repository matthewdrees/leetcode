class Solution:
    def longestPalindrome(self, s: str) -> str:
        if len(s) == 0:
            return ''
        longestPos = 0
        longestLen = 1
        # odd palendrome
        for x in range(1, len(s) - 1):
            maxY = min(x, len(s) - x - 1) + 1
            for y in range(1, maxY):
                if s[x - y] != s[x + y]:
                    break
                if 2 * y + 1 > longestLen:
                    longestPos = x - y
                    longestLen = x + y + 1 - longestPos
        # even palendrome
        for x in range(len(s) - 1):
            maxY = min(x, len(s) - x - 2) + 1
            for y in range(0, maxY):
                if s[x - y] != s[x + 1 + y]:
                    break
                if 2 * (y + 1) > longestLen:
                    longestPos = x - y
                    longestLen = x + y + 2 - longestPos
        return s[longestPos:longestPos + longestLen]


class Solution2:
    def longestPalindrome(self, s: str) -> str:
        '''First submission.'''
        if len(s) == 0:
            return ''
        lp = s[0]
        # odd palendrome
        for x in range(1, len(s) - 1):
            maxY = min(x, len(s) - x - 1) + 1
            for y in range(1, maxY):
                if s[x - y] == s[x + y]:
                    if 2 * y + 1 > len(lp):
                        lp = s[x - y:x + y + 1]
                else:
                    break
        # even palendrome
        for x in range(len(s) - 1):
            maxY = min(x, len(s) - x - 2) + 1
            for y in range(0, maxY):
                if s[x - y] == s[x + 1 + y]:
                    if 2 * (y + 1) > len(lp):
                        lp = s[x - y:x + y + 2]
                else:
                    break
        return lp


if __name__ == '__main__':

    s = Solution()
    tests = (
        ("babad", "bab"),
        ("adbab", "bab"),
        ("cbbd", "bb"),
        ("amanaplanacanalpanama", "amanaplanacanalpanama"),
        ("bbbbba", "bbbbb"),
        ("wwkew", "ww"),
        ("wkeww", "ww"),
        ("abcdefghijklmnopqrstuvwxyz", "a"),
    )

    for test in tests:

        string = test[0]
        exp = test[1]
        ans = s.longestPalindrome(string)
        if exp != ans:
            print(f'FAIL. s: {string}, exp: {exp}, ans: {ans}')
