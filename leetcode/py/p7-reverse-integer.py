class Solution:
    def reverse(self, x: int) -> int:
        ret = 0
        isnegative = x < 0
        x = abs(x)
        while True:
            ret += x % 10
            x = x // 10
            if x == 0:
                break
            ret *= 10

        # Return 0 if result is an int32 underflow or overflow.
        if isnegative:
            ret *= -1
            if ret < -2147483648:
                return 0
        elif ret > 2147483647:
            return 0

        return ret


if __name__ == '__main__':

    s = Solution()
    tests = (
        (123, 321),
        (7463847412, 2147483647),
        (8463847412, 0),
        (-8463847412, -2147483648),
        (-9463847412, 0),
        (-123, -321),
        (120, 21),
    )

    for test in tests:

        num = test[0]
        exp = test[1]
        ans = s.reverse(num)
        if exp != ans:
            print(f'FAIL. num: {test[0]}, exp: {exp}, ans: {ans}')
