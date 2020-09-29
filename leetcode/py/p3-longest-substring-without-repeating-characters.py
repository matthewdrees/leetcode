import collections


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:

        longest = 0
        x = 0
        y = 0
        while y != len(s):
            if s[y] in s[x:y]:
                x += 1
            else:
                y += 1
                if y - x > longest:
                    longest = y - x

        return longest


class Solution4:
    def lengthOfLongestSubstring(self, s: str) -> int:
        longest = 0
        chars = collections.deque()
        for c in s:
            while c in chars:
                chars.popleft()
            chars.append(c)
            if longest < len(chars):
                longest = len(chars)
        return longest


class Solution3:
    def lengthOfLongestSubstring(self, s: str) -> int:

        if s == '':
            return 0

        longest = 1
        chars = {s[0]}
        x = 0
        y = 1
        while y != len(s):

            if s[y] in chars:
                chars.remove(s[x])
                x += 1
            else:
                chars.add(s[y])
                y += 1
                if y - x > longest:
                    longest = y - x

        return longest


class Solution2:
    def lengthOfLongestSubstring(self, s: str) -> int:
        '''First cut.
        
        Did not submit, just thought of a faster way.'''
        longest = 1
        for x in range(len(s)):
            chars = {s[x]}
            y = x + 1
            while y != len(s):
                if s[y] in chars:
                    break
                chars.add(s[y])
                y += 1
            if y - x > longest:
                longest = y - x
        return longest


if __name__ == '__main__':

    s = Solution()
    tests = (
        ("", 0),
        ("a", 1),
        ("abcabcbb", 3),
        ("bbbbb", 1),
        ("pwwkew", 3),
    )

    for test in tests:

        substr = test[0]
        exp = test[1]
        ans = s.lengthOfLongestSubstring(substr)
        if exp != ans:
            print(f'FAIL. s: {substr}, exp: {exp}, ans: {ans}')
