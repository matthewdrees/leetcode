"""projecteuler.net problem 3"""

import math

import common


def largest_prime_factor(n):
    """Return the largest prime factor of n.

    :param n: find largest prime factor of n
    :type n: int

    >>> largest_prime_factor(2)
    2
    >>> largest_prime_factor(3)
    3
    >>> largest_prime_factor(4)
    2
    >>> largest_prime_factor(5)
    5
    >>> largest_prime_factor(6)
    3
    >>> largest_prime_factor(7)
    7
    >>> largest_prime_factor(8)
    2
    >>> largest_prime_factor(9)
    3
    >>> largest_prime_factor(13195)
    29
    """
    largest_prime = 0
    while n % 2 == 0:
        n = n // 2
        largest_prime = 2

    if common.is_prime(n):
        return n

    for p in range(3, math.isqrt(n) + 1, 2):
        if n == 1:
            break
        if common.is_prime(p):
            while n % p == 0 and n != 1:
                n = n // p
                largest_prime = p

    return largest_prime


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(largest_prime_factor(600851475143))
