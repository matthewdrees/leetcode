// Project Euler problem 50. Consecutive prime sum.
//
// The prime 41, can be written as the sum of six consecutive primes:
//
//      41 = 2 + 3 + 5 + 7 + 11 + 13
//
// This is the longest sum of consecutive primes that adds to a prime below one-hundred.
//
// The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
//
// Which prime, below one-million, can be written as the sum of the most consecutive primes?
#include "project_euler_common.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

// Find the prime < n that can be written as the sum of the most consecutive primes
//
// If there are 2 runs the same length, the first (lower) prime is chosen. That shouldn't matter
// for this problem.
//
// \param n: Consider primes < n.
// \return: Prime that is the sum of the most consecutive primes.
int get_sum_most_consecutive_primes(int n)
{
    if (n <= 2)
    {
        return 0;
    }
    const auto primes = get_primes(n);

    // Find the longest possible run size.
    size_t run_size = 0;
    int start_run_sum = 0;
    for (; start_run_sum < n && run_size < primes.size(); ++run_size)
    {
        start_run_sum += primes[run_size];
    }

    // Look for the answer by run size, from longest to shortest.
    for (; run_size > 1; --run_size)
    {
        auto i1 = primes.begin();
        auto i2 = std::next(primes.begin(), run_size);
        int run_sum = std::accumulate(i1, i2, 0);
        for (; run_sum < n && i2 != primes.end(); ++i1, ++i2)
        {
            if (std::binary_search(i2, primes.end(), run_sum))
            {
                return run_sum;
            }
            run_sum -= *i1;
            run_sum += *i2;
        }
    }
    return 2;
}

bool test_get_sum_most_consecutive_primes()
{
    struct TestCase
    {
        int n;
        int expected;
    };
    TestCase testCases[] = {
        {2, 0},
        {3, 2},
        {4, 2},
        {5, 2},
        {6, 5},
        {41, 17},
        {42, 41},
        {43, 41},
        {954, 953},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = get_sum_most_consecutive_primes(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << "), expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

int main()
{
    std::cout << get_sum_most_consecutive_primes(1000000) << "\n";

    const bool passed = test_get_sum_most_consecutive_primes();
    return passed ? 0 : 1;
}
