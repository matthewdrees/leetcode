"""projecteuler.net problem 21. Amicable numbers.

Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""


def get_sum_of_amicable_numbers(n):
    """Get sum of all amicable numbers < n.

    >>> get_sum_of_amicable_numbers(285)
    504
    """

    # Set up a seive of sum of factors up to n.
    l = [1] * n
    for x in range(2, n):
        for y in range(x * 2, n, x):
            l[y] += x

    # Now find and add the amicable numbers.
    sum_of_amicable_numbers = 0
    for x in range(2, n):
        if l[x] > x and l[x] < n:
            if l[l[x]] == x:
                # print(f"found amicable numbers: {x}, {l[x]}")
                sum_of_amicable_numbers += x + l[x]
    return sum_of_amicable_numbers


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_sum_of_amicable_numbers(10000))
