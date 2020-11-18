"""Project Euler 31. Coin sums.

In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
"""


def coin_sums(amount, coins):
    """Returns number of possible coin combinations to make amount.

    :param amount: Amount of money for calculation.
    :param coins: List of coin denominations.
    :return: Number of combinations of coins to make amount.

    Note: doesn't work correctly for amount = 0 (will return 1). Not needed. If desired,
          check at the start of the function and deal with it inside the loop.

    >>> coin_sums(1, [2, 1])
    1
    >>> coin_sums(2, [2, 1])
    2
    >>> coin_sums(3, [2, 1])
    2
    >>> coin_sums(4, [2, 1])
    3
    >>> coin_sums(5, [5, 2, 1])
    4
    >>> coin_sums(6, [5, 2, 1])
    5
    >>> coin_sums(7, [5, 2, 1])
    6
    >>> coin_sums(8, [5, 2, 1])
    7
    >>> coin_sums(10, [10, 5, 2, 1])
    11
    >>> coin_sums(20, [20, 10, 5, 2, 1])
    41
    """
    if len(coins) == 1:
        return 1
    coin = coins[0]
    coin_combinations = 0
    for x in range(0, amount + 1, coin):
        remainder = amount - x
        coin_combinations += coin_sums(remainder, coins[1:])
    return coin_combinations


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(coin_sums(200, [200, 100, 50, 20, 10, 5, 2, 1]))
