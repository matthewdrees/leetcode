"""projecteuler.net problem 6

The sum of the squares of the first ten natural numbers is,

    1² + 2² + ... + 10² = 358

The square of the sum of the first ten natural numbers is,

    (1 + 2 + ... + 10)² = 55² = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is .

    3025 - 385 = 2640

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
"""

import common


def sum_square_difference(n):
    """Return the difference of the sum of squares for first 'n' natural numbers.

    >>> sum_square_difference(1)
    0
    >>> sum_square_difference(2)
    4
    >>> sum_square_difference(10)
    2640
    >>> sum_square_difference(20)
    41230
    """
    return common.sum_of_continous_numbers(1, n) ** 2 - common.sum_of_squares(n)


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(sum_square_difference(100))
