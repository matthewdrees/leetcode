"""projecteuler.net problem 12.

The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:

 1: 1
 3: 1,3
 6: 1,2,3,6
10: 1,2,5,10
15: 1,3,5,15
21: 1,3,7,21
28: 1,2,4,7,14,28
We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over five hundred divisors?
"""

import common

primes = common.primesfrom2to(100000)


def get_number_of_divisors(n):
    """Return number of divisors of number n.

    >>> get_number_of_divisors(1)
    1
    >>> get_number_of_divisors(3)
    2
    >>> get_number_of_divisors(6)
    4
    >>> get_number_of_divisors(10)
    4
    >>> get_number_of_divisors(28)
    6
    >>> get_number_of_divisors(32)
    6
    """
    if n < 1:
        return 0
    if n < 2:
        return 1

    # The number of divisors is related to the number of prime factors:
    #
    #     num_divisors = (num_p1 + 1) * (num_p2 + 1) ...
    #
    # Count the runs of prime factors and calculate num_divisors.
    num_divisors = 1
    stop = n // 2
    for prime in primes:
        if prime > stop or n == 1:
            break
        prime_count = 0
        while n % prime == 0:
            n = n // prime
            prime_count += 1
        num_divisors = num_divisors * (prime_count + 1)

    if num_divisors == 1:
        return 2
    return num_divisors


def get_triangle_number_with_minimum_divisors(minimum_divisors):

    max_num_divisors = 0
    triangle_number = 0
    for x in range(100000):
        triangle_number += x
        num_divisors = get_number_of_divisors(triangle_number)
        if num_divisors > max_num_divisors:
            if num_divisors >= minimum_divisors:
                return triangle_number
            # print(f"triangle number: {triangle_number}, divisors: {num_divisors}")
            max_num_divisors = num_divisors

    return None


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_triangle_number_with_minimum_divisors(500))
