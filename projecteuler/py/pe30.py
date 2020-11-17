"""Project Euler probelm 30. Digit fifth powers.

Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

    1634 = 1⁴ + 6⁴ + 3⁴ + 4⁴
    8208 = 8⁴ + 2⁴ + 0⁴ + 8⁴
    9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴

As 1 = 1⁴ is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
"""


def digit_x_power(power):
    """

    >>> digit_x_power(4)
    19316
    """
    total = 0
    for x in range(2, 10 ** (power + 1)):
        sum_ = sum([(int(c) ** power) for c in str(x)])
        if sum_ == x:
            total += sum_
    return total


def digit_fifth_power_faster():
    """This is uglier but 4 times faster."""
    total = 0
    sum_ = 0
    num = 0

    for z in range(0, 10):
        z5 = z ** 5
        num = 100000 * z
        sum_ += z5
        for a in range(0, 10):
            a5 = a ** 5
            num += 10000 * a
            sum_ += a5
            for b in range(0, 10):
                b5 = b ** 5
                num += 1000 * b
                sum_ += b5
                for c in range(0, 10):
                    c5 = c ** 5
                    num += 100 * c
                    sum_ += c5
                    for d in range(0, 10):
                        d5 = d ** 5
                        num += 10 * d
                        sum_ += d5
                        for e in range(0, 10):
                            e5 = e ** 5
                            num += e
                            sum_ += e5
                            if sum_ == num:
                                if num > 1:
                                    # print(f"found one! {num}")
                                    total += num
                            num -= e
                            sum_ -= e5
                        num -= 10 * d
                        sum_ -= d5
                    num -= 100 * c
                    sum_ -= c5
                num -= 1000 * b
                sum_ -= b5
            num -= 10000 * a
            sum_ -= a5
        num -= 100000 * z
        sum_ -= z5
        assert num == 0
        assert sum_ == 0

    return total


if __name__ == "__main__":
    import doctest

    # doctest.testmod()

    print(digit_fifth_power_faster())
