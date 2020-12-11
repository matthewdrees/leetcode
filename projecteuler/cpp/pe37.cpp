// Project Euler problem 37. Truncatable primes.
//
// The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
//
// Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
//
// NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
#include "project_euler_common.h"

#include <algorithm>
#include <iostream>
#include <vector>

struct Primes
{
    Primes(int max) : primes(get_primes(max)) {}

    std::vector<int> primes;

    bool is_truncatable_prime(int prime) const
    {
        if (prime < 10)
        {
            return false;
        }

        int mod = 1;
        // See if it's a prime truncating digits on the right.
        for (int p = prime / 10; p != 0; p = p / 10)
        {
            if (!std::binary_search(primes.begin(), primes.end(), p))
            {
                return false;
            }
            mod = mod * 10;
        }

        // See if it's a prime truncating digits on the left.
        for (; mod > 1; mod /= 10)
        {
            int p = prime % mod;
            if (!std::binary_search(primes.begin(), primes.end(), p))
            {
                return false;
            }
        }
        return true;
    }

    // Get sum of truncatable primes
    int get_sum_truncatable_primes() const
    {
        int total = 0;
        // Skip primes 2, 3, 5, 7.
        int counter = 0;
        for (size_t i = 4; i < primes.size(); ++i)
        {
            const int prime = primes[i];
            if (is_truncatable_prime(prime))
            {
                // std::cout << "Found one: " << prime << '\n';
                total += prime;
                ++counter;
                if (counter == 11)
                {
                    break;
                }
            }
        }
        if (counter != 11)
        {
            std::cout << "expected 11, found " << counter << '\n';
        }
        return total;
    }
};

int test_is_truncatable_prime()
{
    struct TestCase
    {
        int n;
        bool expected;
    };
    TestCase testCases[] = {
        {2, false},
        {7, false},
        {13, false},
        {37, true},
        {97, false},
        {797, true},
        {3797, true},
    };
    int num_fails = 0;
    Primes primes(10000);
    for (const auto &tc : testCases)
    {
        const auto actual = primes.is_truncatable_prime(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    Primes primes(1000000);
    std::cout << primes.get_sum_truncatable_primes() << '\n';

    return test_is_truncatable_prime() == 0 ? 0 : 1;
}
