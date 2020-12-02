"""Project Euler problem 36. Double-base palindromes.

The decimal number, 585 = 1001001001₂ (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)
"""
import common


def sum_double_base_palindromes_under_n(n: int):
    """Return the sum of all numbers, less than n, which are palendromic in base 10 and 2.

    :param n: Consider all numbers 1 to n (not inclusive).
    :return: Sum of all double-base palendromic numbers.
    """
    return sum(
        [
            x
            for x in range(1, n)
            if common.is_number_palendrome(x) and common.is_number_palendrome(x, base=2)
        ]
    )


if __name__ == "__main__":
    print(sum_double_base_palindromes_under_n(1000000))
