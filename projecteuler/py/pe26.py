"""projecteuler.net problem 26. Reciprocal cycles.

A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
"""


import decimal
import math


def get_longest_recurring_cycle(d):
    """Find largest recurring cycle from 1/d

    Limitations:
    * Only searches for cycle starting from the tenths position.
    * Only finds cyles of 2 or longer.

    :param d: 1 / d to search for largest recurring cycle.
    :return: length of largest recurring cycle

    >>> get_longest_recurring_cycle(2)
    0
    >>> get_longest_recurring_cycle(4)
    0
    >>> get_longest_recurring_cycle(7)
    6
    >>> get_longest_recurring_cycle(29)
    28
    """
    if d < 3:
        return 0

    precision = d * 2
    decimal.getcontext().prec = precision
    # [2:-1] - Chomp the starting "0." and last number
    s = str(decimal.Decimal(1) / decimal.Decimal(d))[2:-1]
    precision -= 1

    if len(s) < precision:
        # Not repeating
        return 0

    for length in range(2, d):
        is_repeating = True
        for x in range(length):
            if s[x] != s[x + length]:
                is_repeating = False
                break
        if is_repeating:
            return length
    return 0


def reciprocal_cycles(n):
    """Find the positive integer d that is < n where '1/d' has the longest repeating decimal.

    :param n: search for longest repeating cycles with d up to n.
    :return: value of 'd' with the longest repeating cycle.

    >>> reciprocal_cycles(8)
    7
    >>> reciprocal_cycles(1000)
    983
    """
    max_cycle_len = 0
    d_with_max_cycle_len = 0
    for d in range(2, n):
        cycle_len = get_longest_recurring_cycle(d)
        if cycle_len > max_cycle_len:
            max_cycle_len = cycle_len
            d_with_max_cycle_len = d
    return d_with_max_cycle_len


def reciprocal_cycles2(n):
    """Find the positive integer d that is < n where '1/d' has the longest repeating decimal.

    Fast solution inspired by "grimbal" on https://projecteuler.net/thread=26. Simply brilliant.

    :param n: search for longest repeating cycles with d up to n.
    :return: value of 'd' with the longest repeating cycle.

    >>> reciprocal_cycles2(8)
    7
    >>> reciprocal_cycles2(1000)
    983
    """
    d_with_max_cycle_len = 0
    max_cycle_len = 0
    for d in range(2, n):

        last_repeating_modulus = 1
        for x in range(d):
            last_repeating_modulus = (10 * last_repeating_modulus) % d

        repeating_modulus = last_repeating_modulus
        for cycle_len in range(1, n):
            repeating_modulus = (10 * repeating_modulus) % d
            if repeating_modulus == last_repeating_modulus:
                break

        if cycle_len > max_cycle_len:
            max_cycle_len = cycle_len
            d_with_max_cycle_len = d

    return d_with_max_cycle_len


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(reciprocal_cycles(1000))
