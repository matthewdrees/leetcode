class Solution:
    def wordPattern(self, pattern: str, str: str) -> bool:
        '''Stolen from StefanPochmann posting.

        Very elegant but same runtime as my guy below.
        '''
        s = pattern
        t = str.split()
        return len(set(zip(s, t))) == len(set(s)) == len(
            set(t)) and len(s) == len(t)


class Solution2:
    def wordPattern(self, pattern: str, str: str) -> bool:
        '''My solution.

        Several wrong submissions because of poor problem definition.
        '''
        d = {}
        words = str.split(' ')

        # str.split will give [''] for empty string.
        if words[0] == '':
            if len(pattern) != 0:
                return False
        elif len(pattern) != len(words):
            return False

        for x in range(len(pattern)):
            c = pattern[x]
            word = words[x]
            if c in d:
                if d[c] != word:
                    return False
            else:
                d[c] = word

        # check to make sure dictionary words are unique.
        s = set()
        for val in d.values():
            if val in s:
                return False
            s.add(val)

        return True


if __name__ == '__main__':

    passed = True

    s = Solution()
    tests = (
        ('', '', True),
        ('', ' ', True),
        ('', ' grr', False),
        ('', 'dog cat cat dog', False),
        ('x', 'dog', True),
        ('x', 'dog cat cat dog', False),
        ('xy', 'dog cat', True),
        ('xy', 'dog cat cat dog', False),
        ('xx', 'dog dog', True),
        ('xx', 'dog dog cat cat', False),
        ('abba', 'dog cat cat dog', True),
        ('abba', 'dog cat cat fish', False),
        ('aaaa', 'dog cat cat dog', False),
        ('aaaa', 'dog dog dog dog', True),
        ('abba', 'dog dog dog dog', False),
        ('aaaa', 'dog cat cat dog', False),
        ('jquery', 'jquery', False),
    )

    for test in tests:
        pattern = test[0]
        words = test[1]
        exp = test[2]
        ans = s.wordPattern(pattern, words)
        if exp != ans:
            passed = False
            print(
                f'FAIL. pattern: {pattern}, words: {words}, exp: {exp}, ans: {ans}'
            )
