// Project Euler problem 49. Prime permutations.
//
// The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases
// by 3330, is unusual in two ways: (i) each of the three terms are prime, and,
// (ii) each of the 4-digit numbers are permutations of one another.
//
// There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
// exhibiting this property, but there is one other 4-digit increasing sequence.
//
// What 12-digit number do you form by concatenating the three terms in this sequence?
#include <algorithm>
#include <iostream>
#include <vector>

#include "project_euler_common.h"

// Return n as sorted digits.
std::vector<int8_t> get_sorted_digits(int n)
{
    std::vector<int8_t> v;
    while (n != 0)
    {
        v.push_back(static_cast<int8_t>(n % 10));
        n /= 10;
    }
    std::sort(v.begin(), v.end());
    return v;
}

int test_get_sorted_digits()
{
    struct TestCase
    {
        int n;
        std::vector<int8_t> expected;
    };
    TestCase testCases[] = {
        {0, {}},
        {1, {1}},
        {9, {9}},
        {10, {0, 1}},
        {11, {1, 1}},
        {12, {1, 2}},
        {321, {1, 2, 3}},
        {320, {0, 2, 3}},
        {333, {3, 3, 3}},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_sorted_digits(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << "), expected: "
                      << tc.expected.size() << ", actual: " << actual.size() << "\n";
        }
    }
    return num_fails;
}

int64_t pe49()
{
    const auto primes = get_primes(10000);

    // Advance index to first 4 digit number past 1487
    size_t i = 0;
    for (; i < primes.size(); ++i)
    {
        if (primes[i] > 1487)
        {
            break;
        }
    }

    // Search 4 digit prime numbers
    for (; i < primes.size(); ++i)
    {
        const int p1 = primes[i];
        const auto p1_sorted_digits = get_sorted_digits(p1);

        for (size_t j = i + 1; j < primes.size(); ++j)
        {
            const int p2 = primes[j];
            const auto p2_sorted_digits = get_sorted_digits(p2);
            if (p1_sorted_digits == p2_sorted_digits)
            {
                const int delta = p2 - p1;
                const int p3 = p2 + delta;
                if (std::binary_search(primes.begin(), primes.end(), p3))
                {
                    const auto p3_sorted_digits = get_sorted_digits(p3);
                    if (p1_sorted_digits == p3_sorted_digits)
                    {
                        return static_cast<int64_t>(p1) * 100000000 + p2 * 10000 + p3;
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    std::cout << pe49() << '\n';
    return test_get_sorted_digits() == 0 ? 0 : 1;
}
