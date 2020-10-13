"""projecteuler.net problem 14.

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
"""


def get_term_with_longest_collatz_sequence(n_begin, n_end):
    """Get the number of terms in the longest collatz sequence.

    :param n_begin: first term to search for.
    :param n_end: up to the last term to search for (non-inclusive).
    :return: term with the largest collatz sequence

    >>> get_term_with_longest_collatz_sequence(13, 14)
    13
    >>> get_term_with_longest_collatz_sequence(13, 15)
    14
    >>> get_term_with_longest_collatz_sequence(13, 19)
    18
    """
    # Note, this took about 11 seconds on my PC. I tried a dynamic-programming approach,
    # but the size of array needed was very quicky much larger than 1 million.
    largest_num_terms = 0
    largest_x = 0
    for x in range(n_begin, n_end):
        num_terms = 1
        term = x
        while term != 1:
            if term % 2 == 0:
                term = term // 2
            else:
                term = 3 * term + 1
            num_terms += 1
        if num_terms > largest_num_terms:
            # print(f"{x}: num_terms: {num_terms}")
            largest_num_terms = num_terms
            largest_x = x
    return largest_x


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_term_with_longest_collatz_sequence(13, 1000000))
