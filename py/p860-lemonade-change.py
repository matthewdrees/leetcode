class Solution:
    def lemonadeChange(self, bills):
        n5s = 0
        n10s = 0

        for bill in bills:
            if bill == 5:
                n5s += 1
            elif bill == 10:
                if n5s > 0:
                    n10s += 1
                    n5s -= 1
                else:
                    return False
            elif bill == 20:
                if n10s > 0 and n5s > 0:
                    n10s -= 1
                    n5s -= 1
                elif n5s >= 3:
                    n5s -= 3
                else:
                    return False
            else:
                assert False, 'bad bill %d' % bill
        return True


if __name__ == '__main__':

    s = Solution()
    tests = (([5, 5, 5, 10, 20], True), ([5, 5, 10], True), ([10, 10], False),
             ([5, 5, 10, 10, 20], False))
    for bills, exp in tests:
        ans = s.lemonadeChange(bills)
        if exp != ans:
            print(f'FAIL, bills: {bills}, exp: {exp}, ans: {ans}')
