"""Project Euler problem 34. Digit factorials.

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: As 1! = 1 and 2! = 2 are not sums they are not included.
"""
import math


def is_sum_of_digit_factorials(n):
    """Return true if n is sum of its digit factorials.

    >>> is_sum_of_digit_factorials(1)
    False
    >>> is_sum_of_digit_factorials(2)
    False
    >>> is_sum_of_digit_factorials(100)
    False
    >>> is_sum_of_digit_factorials(144)
    False
    >>> is_sum_of_digit_factorials(145)
    True
    >>> is_sum_of_digit_factorials(40585)
    True
    """
    if n <= 9:
        return False

    total = 0
    x = n
    while x != 0:
        total += math.factorial(x % 10)
        x = x // 10
    return total == n


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    total = 0
    for x in range(10, 100000):
        if is_sum_of_digit_factorials(x):
            # print(f"found one {x}")
            total += x
    print(total)
