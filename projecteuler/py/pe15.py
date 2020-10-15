"""projecteuler.net problem 15.

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
"""


def num_lattice_paths(n):
    """Number of routes from top left corner of an nxn lattice to bottom right.

    :param n: size of nxn lattice
    :return: number of routes
    >>> num_lattice_paths(2)
    6
    """
    matrix = [[1] * (n + 1) for x in range(n + 1)]
    for y in range(1, n + 1):
        for x in range(1, n + 1):
            matrix[y][x] = matrix[y - 1][x] + matrix[y][x - 1]
    return matrix[n][n]


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(num_lattice_paths(20))
