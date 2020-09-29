def sum_of_multiples_of_3_and_5_below(n):
    """Sum of numbers below n that are multiples of 3 or 5.

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
    total = 0
    for x in range(n):
        if x % 3 == 0 or x % 5 == 0:
            total += x
    return total


if __name__ == "__main__":

    import doctest

    doctest.testmod()

    print(sum_of_multiples_of_3_and_5_below(1000))