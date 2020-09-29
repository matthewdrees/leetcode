class Solution:
    def longestCommonPrefix(self, strs) -> str:
        if len(strs) == 0:
            return ''
        end = min([len(s) for s in strs])
        for x in range(end):
            c = strs[0][x]
            for s in strs[1:]:
                if s[x] != c:
                    return strs[0][0:x]
        return strs[0][0:end]


if __name__ == '__main__':

    passed = True

    s = Solution()
    tests = (
        (["flower", "flow", "flight"], 'fl'),
        (["dog", "racer", "car"], ''),
        (["a", "a"], 'a'),
        (["ab", "ab"], 'ab'),
        (["a"], 'a'),
        (["abcd"], 'abcd'),
        ([""], ''),
        ([], ''),
    )

    for test in tests:
        words = test[0]
        exp = test[1]
        ans = s.longestCommonPrefix(words)
        if exp != ans:
            passed = False
            print(f'FAIL. words: {words}, exp: {exp}, ans: {ans}')
