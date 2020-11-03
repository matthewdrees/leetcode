"""projecteuler.net problem 25, 1000-digit Fibonacci number.

The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:

F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
"""


def get_xth_term_of_fibonacci_with_num_digits(num_digits):
    """Get the xth term of the first fibonacci number with a num_digits.

    :param num_digits: number of digits in the fibonacci number.
    :return: index of the term for the given fibonacci number.

    >>> get_xth_term_of_fibonacci_with_num_digits(0)
    0
    >>> get_xth_term_of_fibonacci_with_num_digits(1)
    1
    >>> get_xth_term_of_fibonacci_with_num_digits(2)
    7
    >>> get_xth_term_of_fibonacci_with_num_digits(3)
    12
    """
    if num_digits <= 0:
        return 0
    xth_term = 1
    fib1 = 1
    fib2 = 1
    while fib1 < 10 ** (num_digits - 1):
        xth_term += 1
        fib1, fib2 = fib2, fib1 + fib2
    return xth_term


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_xth_term_of_fibonacci_with_num_digits(1000))
