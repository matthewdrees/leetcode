def sum_of_even_valued_fibonacci_numbers_below(n):
    """Sum of even fibonacci numbers below n.

    >>> sum_of_even_valued_fibonacci_numbers_below(2)
    0
    >>> sum_of_even_valued_fibonacci_numbers_below(3)
    2
    >>> sum_of_even_valued_fibonacci_numbers_below(5)
    2
    >>> sum_of_even_valued_fibonacci_numbers_below(8)
    2
    >>> sum_of_even_valued_fibonacci_numbers_below(9)
    10
    >>> sum_of_even_valued_fibonacci_numbers_below(34)
    10
    >>> sum_of_even_valued_fibonacci_numbers_below(35)
    44
    """
    fib1, fib2 = 1, 2
    total = 0
    while fib2 < n:
        if fib2 % 2 == 0:
            total += fib2
        fib1, fib2 = fib2, fib1 + fib2
    return total


if __name__ == "__main__":

    import doctest

    doctest.testmod()

    print(sum_of_even_valued_fibonacci_numbers_below(4000001))
