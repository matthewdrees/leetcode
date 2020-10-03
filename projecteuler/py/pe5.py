"""projecteuler.net problem 5

2520 is the smallest number that can be divided by each of the numbers
from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all
of the numbers from 1 to 20?
"""

# Honestly, didn't need programming for this one.
#
# Primes in 2-20 are: 2, 3, 5, 7, 11, 13, 17, 19
#
# Factors in the non-primes:
#
# 4: 2 * 2
# 6: 2 * 3
# 8: 2 * 2 * 2
# 9: 3 * 3
# 10: 2 * 5
# 12: 2 * 3
# 14: 2 * 7
# 15: 3 * 5
# 16: 2 * 2 * 2 * 2
# 18: 2 * 3 * 3
# 20: 2 * 2 * 5
print(2 ** 4 * 3 ** 2 * 5 * 7 * 11 * 13 * 17 * 19)
