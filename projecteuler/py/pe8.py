"""projecteuler.net problem 8

The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.

    (see number below)

Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?
"""

import math


def largest_product_in_a_series(num_adjacent_digits, series):
    """Find the largest product in a series.

    :param num_adjacent_digits: number of adjacent digits to search
    :param series: series of numbers
    :type series: str

    >>> largest_product_in_a_series(1, "")
    0
    >>> largest_product_in_a_series(1, "18")
    8
    >>> largest_product_in_a_series(1, "95")
    9
    >>> largest_product_in_a_series(2, "4758")
    40
    >>> largest_product_in_a_series(2, "7768")
    49
    >>> largest_product_in_a_series(2, "6875")
    56
    >>> largest_product_in_a_series(2, "09012")
    2
    """

    largest_product = 0

    # Zeros are a pain. Split the string on zeros to avoid them.
    for no_zero_segment in series.split("0"):
        if num_adjacent_digits > len(no_zero_segment):
            continue

        # Convert string to ints and work from that.
        nums = [int(x) for x in no_zero_segment]

        # Prime the pump with the first run of adjacent digits.
        product = math.prod(nums[0:num_adjacent_digits])
        if product > largest_product:
            largest_product = product

        # One pass, recalculate the product of adjacent digits by dividing off the
        # first number and multiplying in the next.
        start_index = 0
        end_index = num_adjacent_digits
        while end_index < len(nums):
            product = product // nums[start_index]
            product = product * nums[end_index]
            if product > largest_product:
                largest_product = product
            start_index += 1
            end_index += 1

    return largest_product


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    num = (
        "73167176531330624919225119674426574742355349194934"
        "96983520312774506326239578318016984801869478851843"
        "85861560789112949495459501737958331952853208805511"
        "12540698747158523863050715693290963295227443043557"
        "66896648950445244523161731856403098711121722383113"
        "62229893423380308135336276614282806444486645238749"
        "30358907296290491560440772390713810515859307960866"
        "70172427121883998797908792274921901699720888093776"
        "65727333001053367881220235421809751254540594752243"
        "52584907711670556013604839586446706324415722155397"
        "53697817977846174064955149290862569321978468622482"
        "83972241375657056057490261407972968652414535100474"
        "82166370484403199890008895243450658541227588666881"
        "16427171479924442928230863465674813919123162824586"
        "17866458359124566529476545682848912883142607690042"
        "24219022671055626321111109370544217506941658960408"
        "07198403850962455444362981230987879927244284909188"
        "84580156166097919133875499200524063689912560717606"
        "05886116467109405077541002256983155200055935729725"
        "71636269561882670428252483600823257530420752963450"
    )
    print(largest_product_in_a_series(13, num))
