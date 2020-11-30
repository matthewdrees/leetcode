"""Project Euler problem 35. Circular primes.

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
"""

import common

import numpy


def circular_primes(n):
    """Find the number of circular primes under n.

    >>> circular_primes(100)
    13
    """
    primes = common.primesfrom2to(n)
    num_circular_primes = 0
    for prime in primes:
        s = str(prime)
        is_circular_prime = True
        for _ in range(len(s) - 1):
            s = s[1:] + s[0]
            next_prime = int(s)
            i = numpy.searchsorted(primes, next_prime)
            if i == len(primes) or primes[i] != next_prime:
                is_circular_prime = False
                break
        if is_circular_prime:
            # print(f"found one: {prime}")
            num_circular_primes += 1

    return num_circular_primes


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(circular_primes(1000000))
