"""projecteuler.net problem 7.

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10001st prime number?
"""

import common


def get_nth_prime_number(n):
    """Get the n-th prime number.

    >>> get_nth_prime_number(1)
    2
    >>> get_nth_prime_number(2)
    3
    >>> get_nth_prime_number(6)
    13
    """
    if n < 1:
        return 0
    if n == 1:
        return 2
    num = 1
    while n > 1:
        num += 2
        if common.is_prime(num):
            n -= 1
    return num


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_nth_prime_number(10001))
