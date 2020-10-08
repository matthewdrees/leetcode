"""projecteuler.net problem 9

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

    a² + b² = c²

For example, 3² + 4² = 9 + 16 = 25 = 5².

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
"""


def generate_list_of_squares(n):
    """Generate list of first n squares.

    >>> generate_list_of_squares(0)
    [0]
    >>> generate_list_of_squares(1)
    [0, 1]
    >>> generate_list_of_squares(2)
    [0, 1, 4]
    >>> generate_list_of_squares(3)
    [0, 1, 4, 9]
    >>> generate_list_of_squares(4)
    [0, 1, 4, 9, 16]
    """
    l = [0] * (n + 1)
    delta = 1
    for x in range(1, n + 1):
        l[x] = l[x - 1] + delta
        delta += 2
    return l


def pythagorean_triplet_sum_to_n(n):
    """Find the pythagorean triplet that sums to n.

    :param n: sum to n.
    :type n: int
    :return: sum of pythagorean numbers that add to n, or None if none are found.

    >>> pythagorean_triplet_sum_to_n(12)
    60
    >>> pythagorean_triplet_sum_to_n(13)

    >>> pythagorean_triplet_sum_to_n(1000)
    31875000
    """
    l = generate_list_of_squares(n + 1 // 2)
    for c in range(n // 4, n // 2):
        for b in range(c // 2, c):
            a = n - c - b
            if a >= 1 and l[a] == a ** 2:
                if l[a] + l[b] == l[c]:
                    return a * b * c
    return None


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(pythagorean_triplet_sum_to_n(1000))
