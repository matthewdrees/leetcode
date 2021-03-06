"""Common project euler operations."""

import math
import numpy as np


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


def is_number_palendrome(n: int, base: int = 10):
    """Return true if n is a palendrome.

    :param n: number to check for palendrome.
    :param base: base of number to check for.
    :return: True if is a palendrome.

    >>> is_number_palendrome(0)
    True
    >>> is_number_palendrome(1)
    True
    >>> is_number_palendrome(9)
    True
    >>> is_number_palendrome(10)
    False
    >>> is_number_palendrome(11)
    True
    >>> is_number_palendrome(12)
    False
    >>> is_number_palendrome(121)
    True
    >>> is_number_palendrome(921)
    False
    >>> is_number_palendrome(129)
    False
    >>> is_number_palendrome(9009)
    True
    >>> is_number_palendrome(1011)
    False
    >>> is_number_palendrome(1101)
    False
    >>> is_number_palendrome(1111)
    True
    >>> is_number_palendrome(1, 2)
    True
    >>> is_number_palendrome(2, 2)
    False
    >>> is_number_palendrome(3, 2)
    True
    >>> is_number_palendrome(4, 2)
    False
    >>> is_number_palendrome(5, 2)
    True
    >>> is_number_palendrome(6, 2)
    False
    >>> is_number_palendrome(7, 2)
    True
    >>> is_number_palendrome(8, 2)
    False
    >>> is_number_palendrome(9, 2)
    True
    """
    # Notes:
    # 1. It's possible to have a base 1 number (counting with line scratches). YAGNI.
    # 2. Deal with base 16 if it ever comes up (substitute in letters for 10 - 15).
    assert base >= 2 and base <= 10
    digits = []
    while n != 0:
        digits.append(n % base)
        n = n // base
    half = len(digits) // 2
    # Compare first half to last half reversed.
    return digits[0:half] == digits[: -half - 1 : -1]


def primesfrom2to(n):
    """Primes from 2 to < n.

    Lifted from:
    https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188

    :param n: primes 2 <= to < n. n must be >= 6.
    :return: numpy array of primes

    >>> primesfrom2to(3)
    array([2])
    >>> primesfrom2to(6)
    array([2, 3, 5])
    >>> primesfrom2to(7)
    array([2, 3, 5])
    >>> primesfrom2to(8)
    array([2, 3, 5, 7])
    """
    if n < 3:
        return np.array()
    if n < 4:
        return np.array([2])
    if n < 6:
        return np.array([2, 3])

    sieve = np.ones(n // 3 + (n % 6 == 2), dtype=np.bool)
    sieve[0] = False
    for i in range(int(n ** 0.5) // 3 + 1):
        if sieve[i]:
            k = 3 * i + 1 | 1
            sieve[((k * k) // 3) :: 2 * k] = False
            sieve[(k * k + 4 * k - 2 * k * (i & 1)) // 3 :: 2 * k] = False
    return np.r_[2, 3, ((3 * np.nonzero(sieve)[0] + 1) | 1)]


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


def sum_of_continous_numbers(first_number, last_number):
    """Return the sum of continous number from first_number to last_number.

    Calculates in O(1) time. Uses Carl Gauss's equation for sum of consecutive numbers.

    :param first_number: first number in continous run
    :param last_number: last number in continous run
    :return: sum of the run of numbers.

    >>> sum_of_continous_numbers(1, 1)
    1
    >>> sum_of_continous_numbers(1, 2)
    3
    >>> sum_of_continous_numbers(1, 3)
    6
    >>> sum_of_continous_numbers(2, 3)
    5
    >>> sum_of_continous_numbers(1, 10)
    55
    """
    assert first_number <= last_number
    total_numbers = last_number - first_number + 1
    return int(total_numbers / 2 * (first_number + last_number))


def sum_of_squares(n):
    """Return sum of squares up to n.

    :param n: sum of squares up to n.
    :return: sum of squares.

    >>> sum_of_squares(1)
    1
    >>> sum_of_squares(2)
    5
    >>> sum_of_squares(3)
    14
    >>> sum_of_squares(4)
    30
    >>> sum_of_squares(10)
    385
    >>> sum_of_squares(20)
    2870
    """
    assert n >= 0
    # TODO: there must be a faster/geometrical way to do this.
    total = 0
    for x in range(1, n + 1):
        total += x ** 2
    return total


if __name__ == "__main__":
    import doctest

    doctest.testmod()
