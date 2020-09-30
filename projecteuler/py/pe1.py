"""Projecteuler.net problem 1"""


def carl_gauss_sum_helper(n, multiple):
    """Return the sum of multiples using Carl Gauss's sum of consecutive numbers.

    >>> carl_gauss_sum_helper(3, 3)
    0
    >>> carl_gauss_sum_helper(4, 3)
    3
    >>> carl_gauss_sum_helper(6, 3)
    3
    >>> carl_gauss_sum_helper(7, 3)
    9
    >>> carl_gauss_sum_helper(10, 3)
    18
    >>> carl_gauss_sum_helper(5, 5)
    0
    >>> carl_gauss_sum_helper(6, 5)
    5
    >>> carl_gauss_sum_helper(16, 5)
    30
    """
    total_numbers = (n - 1) // multiple
    return int(total_numbers / 2 * (1 + total_numbers)) * multiple


def sum_of_multiples_of_3_and_5_below(n):
    """Sum of numbers below n that are multiples of 3 or 5.

    Uses the Carl Gauss equation for summing consecutive integers to avoid
    using loops.

    >>> sum_of_multiples_of_3_and_5_below(3)
    0
    >>> sum_of_multiples_of_3_and_5_below(5)
    3
    >>> sum_of_multiples_of_3_and_5_below(6)
    8
    >>> sum_of_multiples_of_3_and_5_below(7)
    14
    >>> sum_of_multiples_of_3_and_5_below(10)
    23
    """
    return (
        carl_gauss_sum_helper(n, 3)
        + carl_gauss_sum_helper(n, 5)
        - carl_gauss_sum_helper(n, 15)
    )


def sum_of_multiples_of_3_and_5_below2(n):
    """Sum of numbers below n that are multiples of 3 or 5.

    This is the simple, first-cut way.
    """
    total = 0
    for x in range(n):
        if x % 3 == 0 or x % 5 == 0:
            total += x
    return total


if __name__ == "__main__":

    import doctest

    doctest.testmod()

    print(sum_of_multiples_of_3_and_5_below(1000))
