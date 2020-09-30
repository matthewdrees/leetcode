"""Common project euler operations."""

import math


def is_prime(n):
    """True if n is prime.

    >>> is_prime(1)
    False
    >>> is_prime(2)
    True
    >>> is_prime(3)
    True
    >>> is_prime(4)
    False
    >>> is_prime(5)
    True
    >>> is_prime(6)
    False
    >>> is_prime(7)
    True
    >>> is_prime(8)
    False
    >>> is_prime(9)
    False
    >>> is_prime(10)
    False
    """
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for x in range(3, math.isqrt(n) + 1, 2):
        if n % x == 0:
            return False
    return True


def sieve_of_eratosthenes(n):
    """Return list of prime numbers up to and including n.

    Created by pythoning the description from the wikipedia entry.

    :param n: Calculate prime numbers up to and including this value.
    :return: list of prime numbers.
    >>> sieve_of_eratosthenes(2)
    [2]
    >>> sieve_of_eratosthenes(3)
    [2, 3]
    >>> sieve_of_eratosthenes(4)
    [2, 3]
    >>> sieve_of_eratosthenes(5)
    [2, 3, 5]
    >>> sieve_of_eratosthenes(6)
    [2, 3, 5]
    >>> sieve_of_eratosthenes(7)
    [2, 3, 5, 7]
    >>> sieve_of_eratosthenes(8)
    [2, 3, 5, 7]
    >>> sieve_of_eratosthenes(9)
    [2, 3, 5, 7]
    >>> sieve_of_eratosthenes(10)
    [2, 3, 5, 7]
    >>> sieve_of_eratosthenes(11)
    [2, 3, 5, 7, 11]
    """
    n += 1  # Include n in the primes if it is
    a = [True] * n
    for i in range(2, math.isqrt(n) + 1):
        if a[i]:
            for j in range(i * i, n, i):
                a[j] = False
    primes = []
    for x in range(2, n):
        if a[x]:
            primes.append(x)
    return primes


if __name__ == "__main__":
    import doctest

    doctest.testmod()
