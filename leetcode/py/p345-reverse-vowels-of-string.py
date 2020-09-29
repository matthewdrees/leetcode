class Solution:
    def reverseVowels(self, s: str) -> str:
        l = list(s)
        if len(l) <= 1:
            return s
        vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'}
        x1 = 0
        x2 = len(l) - 1
        while x1 < x2:
            if l[x1] in vowels:
                if l[x2] in vowels:
                    l[x1], l[x2] = l[x2], l[x1]
                    x1 += 1
                    x2 -= 1
                else:
                    x2 -= 1
            else:
                x1 += 1
        return ''.join(l)


if __name__ == '__main__':

    tests = (
        ("hello", "holle"),
        ("leetcode", "leotcede"),
        ("HELLO", "HOLLE"),
    )

    s = Solution()
    for test in tests:
        string = test[0]
        exp = test[1]
        act = s.reverseVowels(string)
        if exp != act:
            print(f'FAIL. {exp} != {act}')
