// Project Euler problem 47. Distinct prime factors.
//
// The first two consecutive numbers to have two distinct prime factors are:
//
// 14 = 2 × 7
// 15 = 3 × 5
//
// The first three consecutive numbers to have three distinct prime factors are:
//
// 644 = 2² × 7 × 23
// 645 = 3 × 5 × 43
// 646 = 2 × 17 × 19.
//
// Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
#include "project_euler_common.h"

#include <algorithm>
#include <iostream>
#include <vector>

// Find first of consecutive numbers with n prime factors.
//
// \param num_prime_factors: number of prime factors to find.
// \param sieve_size: size of sieve to set up to find the numbers.
// \return: first of consecutive numbers with num_prime_factors.
int find_first_of_consecutive_numbers_with_n_prime_factors(int num_prime_factors, int sieve_size)
{
    const auto primes = get_primes(sieve_size);

    // Build the sieve
    std::vector<int> sieve(sieve_size, 0);
    for (const auto prime : primes)
    {
        for (int i = prime; i < sieve_size; i += prime)
        {
            sieve[i] += 1;
        }
    }

    // Sift through the sieve, looking for a run.
    auto it = std::search_n(sieve.begin(), sieve.end(), static_cast<size_t>(num_prime_factors), num_prime_factors);
    if (it != sieve.end())
    {
        return static_cast<int>(std::distance(sieve.begin(), it));
    }

    return 0;
}

int test_find_first_of_consecutive_numbers_with_n_prime_factors()
{
    struct TestCase
    {
        int num_prime_factors;
        int sieve_size;
        int expected;
    };

    TestCase testCases[] = {
        {2, 15, 0},
        {2, 16, 14},
        {3, 647, 644},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = find_first_of_consecutive_numbers_with_n_prime_factors(tc.num_prime_factors, tc.sieve_size);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(num_prime_factors: " << tc.num_prime_factors
                      << ", sieve_size: " << tc.sieve_size
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    std::cout << find_first_of_consecutive_numbers_with_n_prime_factors(4, 150000) << '\n';

    const int num_fails = test_find_first_of_consecutive_numbers_with_n_prime_factors();
    return num_fails == 0 ? 0 : 1;
}
