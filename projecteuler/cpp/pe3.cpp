/* projecteuler.net problem 3. Largest prime factor.

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

#include "project_euler_common.h"
#include <iostream>

// Return the largest prime factor of n.
int64_t largest_prime_factor(int64_t n)
{
    int64_t largest_prime = 0;
    while (n % 2 == 0)
    {
        n = n / 2;
        largest_prime = 2;
    }

    if (is_prime(n))
    {
        return n;
    }

    const auto end_p = static_cast<int64_t>(sqrt(n)) + 1;
    for (int p = 3; p < end_p; p += 2)
    {
        if (n == 1)
        {
            break;
        }
        if (is_prime(p))
        {
            while (n % p == 0 && n != 1)
            {
                n = n / p;
                largest_prime = p;
            }
        }
    }

    return largest_prime;
}

bool test_largest_prime_factor()
{
    struct TestCase
    {
        int64_t n;
        int64_t expected;
    };

    TestCase testCases[] = {
        {2, 2},
        {3, 3},
        {4, 2},
        {5, 5},
        {6, 3},
        {7, 7},
        {8, 2},
        {9, 3},
        {13195, 29},
    };

    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = largest_prime_factor(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

int main()
{
    std::cout << largest_prime_factor(600851475143) << '\n';
    return test_largest_prime_factor() ? 0 : 1;
}
