import bisect
import math


class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        '''Stole this from the "Fermat's Theorem" on solution explanation.

        The brilliance of this is breathtaking. This is faster in the tests
        than Solution2 by a factor of 10.

        Fermat's Theorem says if there are an odd number of prime factors
        of the form "4k+3" then it isn't a sum of squares.

        Note that by dividing out the primes you don't need to calculate
        them ahead of time, since by the time you get to x == 4 you know
        it isn't divisible into c.'''

        for x in range(2, int(math.sqrt(c) + 1)):
            numFactors = 0
            if c % x == 0:
                while c % x == 0:
                    c = c // x
                    numFactors += 1

                if x % 4 == 3 and numFactors % 2 == 1:
                    return False

        return c % 4 != 3


class Solution2:
    def judgeSquareSum(self, c: int) -> bool:
        '''My first solution.

        Compute the squares and cache them. Binary search for them with c - a^2.
        Slow and takes a lot of memory.'''

        # Generate squares if needed.
        while self.cur_square < c:
            self.cur_int += 1
            self.cur_square = self.cur_int * self.cur_int
            self.squares.append(self.cur_square)

        # See if 2 squares add up to 'c'.
        for a_squared in self.squares:
            if a_squared > c:
                return False

            b_squared = c - a_squared
            pos = bisect.bisect_left(self.squares, b_squared)
            if pos < len(self.squares) and self.squares[pos] == b_squared:
                return True

        return False

    def __init__(self):
        self.squares = [0]
        self.cur_int = 0
        self.cur_square = 0


if __name__ == '__main__':

    s = Solution()
    tests = [
        [0, True],
        [1, True],
        [2, True],
        [3, False],
        [4, True],
        [5, True],
        [6, False],
        [7, False],
        [8, True],
        [9, True],
        [10, True],
        [11, False],
        [12, False],
        [13, True],
        [14, False],
        [15, False],
        [16, True],
        [17, True],
        [2910292, False],
        [29102932, True],
    ]

    for test in tests:
        c = test[0]
        exp = test[1]
        ans = s.judgeSquareSum(c)
        if exp != ans:
            print(f'FAIL. c: {c}, exp: {exp}, ans: {ans}')
