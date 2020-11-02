"""projecteuler.net problem 23. Non-abundant sums.

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
"""
import bisect

import numpy as np


def get_abundant_numbers(n):
    """Find all abundant numbers up to n, inclusive.

    A number is abundant if the sum of its proper divisors is greater than itself.

    :param n: find perfect numbers up to this number.
    :return: list of perfect numbers.

    >>> get_abundant_numbers(11)
    []
    >>> get_abundant_numbers(12)
    [12]
    >>> get_abundant_numbers(28)
    [12, 18, 20, 24]
    """
    n = n + 1  # (inclusive)
    assert n <= np.iinfo(np.int32).max
    sieve = np.ones(n, dtype=np.int32)
    for x in range(2, n):
        for y in range(x + x, n, x):
            sieve[y] += x

    abundant_nums = []
    for x in range(2, n):
        if sieve[x] > x:
            abundant_nums.append(x)
    return abundant_nums


def element_in_sorted_list(e, l):
    """Return true if element e in sorted list l.

    >>> element_in_sorted_list(1, [])
    False
    >>> element_in_sorted_list(1, [1])
    True
    >>> element_in_sorted_list(1, [0, 2])
    False
    >>> element_in_sorted_list(2, [0, 1, 2])
    True
    """
    x = bisect.bisect_left(l, e)
    return x < len(l) and l[x] == e


def non_abundant_sums(n):
    """Sum of positive integers that cannot be written as sum of two abundant numbers.

    :param n: Search for numbers up to n, inclusive
    >>> non_abundant_sums(1)
    1
    >>> non_abundant_sums(11)
    66
    >>> non_abundant_sums(12)
    78
    >>> non_abundant_sums(23)
    276
    >>> non_abundant_sums(24)
    276
    >>> non_abundant_sums(29)
    411
    >>> non_abundant_sums(30)
    411
    """
    abundant_numbers = get_abundant_numbers(n)

    sum_of_non_abundant_sums = 0

    for x in range(1, n + 1):
        add_x = True
        for abundant_num in abundant_numbers:
            if abundant_num >= x:
                break
            if element_in_sorted_list(x - abundant_num, abundant_numbers):
                # It is indeed the sum of 2 abundant numbers.
                add_x = False
                break
        if add_x:
            sum_of_non_abundant_sums += x

    return sum_of_non_abundant_sums


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(non_abundant_sums(28123))
