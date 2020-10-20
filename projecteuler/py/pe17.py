"""projecteuler.net problem 17

Number letter counts

If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there
are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words,
how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two)
contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of
"and" when writing out numbers is in compliance with British usage.
"""

ones = (
    "",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen",
)

tens = (
    "",
    "",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
)


def write_out_number(n):
    """Write out number in words (with no spaces).

    >>> write_out_number(1)
    'one'
    >>> write_out_number(10)
    'ten'
    >>> write_out_number(12)
    'twelve'
    >>> write_out_number(19)
    'nineteen'
    >>> write_out_number(20)
    'twenty'
    >>> write_out_number(90)
    'ninety'
    >>> write_out_number(100)
    'onehundred'
    >>> write_out_number(101)
    'onehundredandone'
    >>> write_out_number(110)
    'onehundredandten'
    >>> write_out_number(250)
    'twohundredandfifty'
    >>> write_out_number(300)
    'threehundred'
    >>> write_out_number(976)
    'ninehundredandseventysix'
    >>> write_out_number(1000)
    'onethousand'
    """
    assert n <= 1000

    if n == 1000:
        return "onethousand"

    written_num = ""

    if n > 99:
        written_num += ones[n // 100] + "hundred"
        if n % 100 != 0:
            written_num += "and"

    mod100 = n % 100
    if mod100 < len(ones):
        written_num += ones[mod100]
    else:
        written_num += tens[mod100 // 10]
        written_num += ones[mod100 % 10]

    return written_num


def number_letter_counts(n):
    """Return the total number of letters of all written numbers up to n (inclusive).

    >>> number_letter_counts(0)
    0
    >>> number_letter_counts(1)
    3
    >>> number_letter_counts(5)
    19
    """

    # Implementation note... this was a quick way to implement a solution that took
    # less than 1 second to run. A faster implementation (that would be more time-consuming
    # to code up) would be to calculate all the instances of the word "hundred", "thirteeen",
    # etc, and multiply by the length of the word. Didn't need it though.
    total = 0
    for x in range(n + 1):
        total += len(write_out_number(x))

    return total


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(number_letter_counts(1000))
