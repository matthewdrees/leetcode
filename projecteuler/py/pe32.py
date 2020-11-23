"""Project Euler problem 32. Pandigital products.

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
"""
import itertools


def compare_helper(n, len1, len2):

    num1 = int(n[0:len1])
    num2 = int(n[len1 : len1 + len2])
    ans = int(n[len1 + len2 :])

    if num1 * num2 == ans:
        print(f"found {num1} * {num2} == {ans}")
        return ans
    return 0


products = set()
for c in itertools.permutations("123456789"):

    n = "".join(c)
    products.add(compare_helper(n, 1, 3))
    products.add(compare_helper(n, 1, 4))
    products.add(compare_helper(n, 2, 2))
    products.add(compare_helper(n, 2, 3))

print(sum(products))
