"""projecteuler.net problem 10.

Summation of primes.

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
"""

import common


def sum_of_primes_below(n):
    """return the sum of primes below n.

    :param n: sum of primes below this number.
    :return: sum

    >>> sum_of_primes_below(6)
    10
    >>> sum_of_primes_below(8)
    17
    """
    return sum(common.primesfrom2to(n))


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(sum_of_primes_below(2000000))
