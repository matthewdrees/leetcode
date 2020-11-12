"""projecteuler.net problem 28. Number spiral diagonals.

Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

    21 22 23 24 25
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
"""


def number_spiral_diagonals(n):
    """Get the sum of the numbers on the diagonals with n x n spiral.

    Note, only handles the case where n is odd.

    :param n: dimension of the spiral.
    :return: sum of the numbers on the diagonals.

    >>> number_spiral_diagonals(1)
    1
    >>> number_spiral_diagonals(3)
    25
    >>> number_spiral_diagonals(5)
    101
    """
    assert n % 2 != 0

    cur_num = 1
    total = 1
    for x in range(2, n, 2):
        for y in range(4):
            cur_num += x
            total += cur_num
    return total


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(number_spiral_diagonals(1001))
