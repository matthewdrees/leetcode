class Solution:
    def romanToInt(self, s: str) -> int:
        total = 0
        x = 0
        while x < len(s):
            c = s[x]
            if x + 1 < len(s):
                nextC = s[x + 1]
            else:
                nextC = ''
            if c == 'I':
                if nextC == 'V':
                    total += 4
                    x += 1
                elif nextC == 'X':
                    total += 9
                    x += 1
                else:
                    total += 1
            elif c == 'V':
                total += 5
            elif c == 'X':
                if nextC == 'L':
                    total += 40
                    x += 1
                elif nextC == 'C':
                    total += 90
                    x += 1
                else:
                    total += 10
            elif c == 'L':
                total += 50
            elif c == 'C':
                if nextC == 'D':
                    total += 400
                    x += 1
                elif nextC == 'M':
                    total += 900
                    x += 1
                else:
                    total += 100
            elif c == 'D':
                total += 500
            elif c == 'M':
                total += 1000

            x += 1

        return total


if __name__ == '__main__':

    s = Solution()
    tests = (
        ('I', 1),
        ('II', 2),
        ('III', 3),
        ('IV', 4),
        ('V', 5),
        ('VI', 6),
        ('VII', 7),
        ('VIII', 8),
        ('IX', 9),
        ('X', 10),
        ('XL', 40),
        ('L', 50),
        ('LVIII', 58),
        ('XC', 90),
        ('C', 100),
        ('CD', 400),
        ('D', 500),
        ('CM', 900),
        ('M', 1000),
        ('MCMXCIV', 1994),
        ('MMMCMXCIX', 3999),
    )

    for test in tests:

        roman = test[0]
        exp = test[1]
        ans = s.romanToInt(roman)
        if exp != ans:
            print(f'FAIL. s: {roman}, exp: {exp}, ans: {ans}')
