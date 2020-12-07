"""Project Euler problem 33. Digit cancelling fractions.

The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting
to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by
cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in
value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the
value of the denominator.
"""
import fractions
import math


def get_2_digits(num):
    """Return a tuple of last 2 digits of number.

    >>> get_2_digits(39)
    (3, 9)
    """
    return ((num // 10) % 10, num % 10)


f = fractions.Fraction(1)
for denominator in range(12, 99):
    d1, d2 = get_2_digits(denominator)
    if d1 == d2 or d2 == 0:
        continue
    for numerator in range(11, denominator):
        n1, n2 = get_2_digits(numerator)
        if n1 == n2 or n2 == 0:
            continue
        f1 = fractions.Fraction(numerator, denominator)
        f2 = fractions.Fraction(1)
        if d1 == n2:
            f2 = fractions.Fraction(n1, d2)
        elif d2 == n1:
            f2 = fractions.Fraction(n2, d1)
        if f1 == f2:
            # print(
            #    f"found one: {numerator}/{denominator} == {f2.numerator}/{f2.denominator}"
            # )
            f *= f2

print(f.denominator)
