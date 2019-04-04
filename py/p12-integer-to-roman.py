import collections


class Solution:
    def __init__(self):
        self.d = collections.OrderedDict()
        self.d[1000] = 'M'
        self.d[900] = 'CM'
        self.d[500] = 'D'
        self.d[400] = 'CD'
        self.d[100] = 'C'
        self.d[90] = 'XC'
        self.d[50] = 'L'
        self.d[40] = 'XL'
        self.d[10] = 'X'
        self.d[9] = 'IX'
        self.d[5] = 'V'
        self.d[4] = 'IV'
        self.d[3] = 'III'
        self.d[2] = 'II'
        self.d[1] = 'I'

    def intToRoman(self, num: int) -> str:
        roman = ''
        while num > 0:
            for key, value in self.d.items():
                if num >= key:
                    roman += value
                    num -= key
                    break
        return roman


if __name__ == '__main__':

    s = Solution()
    tests = (
        (1, 'I'),
        (2, 'II'),
        (3, 'III'),
        (4, 'IV'),
        (5, 'V'),
        (6, 'VI'),
        (7, 'VII'),
        (8, 'VIII'),
        (9, 'IX'),
        (10, 'X'),
        (40, 'XL'),
        (50, 'L'),
        (58, 'LVIII'),
        (90, 'XC'),
        (91, 'XCI'),
        (94, 'XCIV'),
        (99, 'XCIX'),
        (100, 'C'),
        (400, 'CD'),
        (500, 'D'),
        (900, 'CM'),
        (1000, 'M'),
        (1994, 'MCMXCIV'),
        (3999, 'MMMCMXCIX'),
    )

    for test in tests:

        num = test[0]
        exp = test[1]
        ans = s.intToRoman(num)
        if exp != ans:
            print(f'FAIL. num: {num}, exp: {exp}, ans: {ans}')
