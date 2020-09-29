class Solution:
    def myAtoi(self, str: str) -> int:

        i = 0  # Index of str.
        n = 0  # Number to return

        # Skip leading whitespace.
        while i < len(str):
            if str[i] != ' ':
                break
            i += 1

        # Track optional +/- prefix.
        isPositive = True
        if i < len(str):
            if str[i] == '-':
                isPositive = False
                i += 1
            elif str[i] == '+':
                i += 1

        # Read in the number.
        while i < len(str):
            if str[i] < '0' or '9' < str[i]:
                break
            n *= 10
            n += int(str[i])
            i += 1

        # Cap positive number to 32 bit signed integer.
        if isPositive:
            if n > 2147483647:
                return 2147483647
            return n

        # Cap negative number to 32 bit signed integer.
        n = -1 * n
        if n < -2147483648:
            return -2147483648
        return n


if __name__ == '__main__':

    s = Solution()
    tests = (
        ("", 0),
        (" ", 0),
        (" -", 0),
        (" +", 0),
        ("42", 42),
        ("   -42", -42),
        ("+42", 42),
        ("4193 with words", 4193),
        ("words and 987", 0),
        ("-91283472332", -2147483648),
        ("-2147483648", -2147483648),
        ("2147483648", 2147483647),
        ("2147483647", 2147483647),
        ("0", 0),
    )

    for test in tests:
        str = test[0]
        exp = test[1]
        ans = s.myAtoi(str)
        if exp != ans:
            print(f'FAIL. s: {str}, exp: {exp}, ans: {ans}')
