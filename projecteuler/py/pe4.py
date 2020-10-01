"""projecteuler.net problem 4

A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
"""


def is_number_palendrome(number):
    """Return true if number is a palendrome.

    >>> is_number_palendrome(0)
    True
    >>> is_number_palendrome(1)
    True
    >>> is_number_palendrome(9)
    True
    >>> is_number_palendrome(10)
    False
    >>> is_number_palendrome(11)
    True
    >>> is_number_palendrome(12)
    False
    >>> is_number_palendrome(121)
    True
    >>> is_number_palendrome(921)
    False
    >>> is_number_palendrome(129)
    False
    >>> is_number_palendrome(9009)
    True
    >>> is_number_palendrome(1011)
    False
    >>> is_number_palendrome(1101)
    False
    >>> is_number_palendrome(1111)
    True
    """
    s = str(number)
    for i in range(len(s) // 2):
        if s[i] != s[-(i + 1)]:
            return False
    return True


def largest_palendromic_number_multiplying_x_digits(num_digits_to_multiply):
    """Largest palendromic number when multiplying x-digit numbers.

    :param num_digits_to_multiply: Number of digits in numbers to multiply.
                                   (e.g. 1: 1-9, 2: 1-99, 3: 1-999)

    >>> largest_palendromic_number_multiplying_x_digits(1)
    9
    >>> largest_palendromic_number_multiplying_x_digits(2)
    9009
    >>> largest_palendromic_number_multiplying_x_digits(3)
    906609
    """
    assert num_digits_to_multiply > 0
    smallest_x_digit_num = 10 ** (num_digits_to_multiply - 1)
    largest_palendrome = 0

    # work from biggest to smallest
    for x in range(10 ** num_digits_to_multiply - 1, smallest_x_digit_num, -1):
        if x * x <= largest_palendrome:
            # found it!
            break
        for y in range(x, largest_palendrome // x, -1):
            num = x * y
            if num < largest_palendrome:
                break
            if is_number_palendrome(num):
                if num > largest_palendrome:
                    largest_palendrome = num
                    break
    return largest_palendrome


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(largest_palendromic_number_multiplying_x_digits(3))
