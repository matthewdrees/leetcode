/* Functions that are helpful for project euler problems. */

#include <algorithm>
#include <cmath>
#include <vector>

// Returns sum of consecutive numbers from first to last.
// e.g. add_consectutive_numbers(1, 5) -> 15
template <class T>
T add_consecutive_numbers(T first, T last)
{
    if (first > last)
    {
        return 0;
    }
    // Carl Gauss's formula.
    const T total_numbers = last - first + 1;
    return total_numbers * (first + last) / 2;
}

// Primes from 2 to < n.
//
// \param n: primes up to n
// \return: vector of primes up to n
//
// Idea taken from function "primesfrom2to":
// https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188
template <class T>
std::vector<T> get_primes(T n)
{
    std::vector<T> primes;
    if (n <= 2)
    {
        return primes;
    }
    primes.push_back(2);
    if (n <= 3)
    {
        return primes;
    }
    primes.push_back(3);

    std::vector<bool> sieve(n / 3 + (n % 6 == 2), true);
    sieve[0] = false;
    const int iEnd = int(std::sqrt(n)) / 3 + 1;
    for (int i = 0; i < iEnd; ++i)
    {
        if (sieve[i])
        {
            const int k_inc = 3 * i + 1 | 1;
            for (size_t k = (k_inc * k_inc) / 3; k < sieve.size(); k += 2 * k_inc)
            {
                sieve[k] = false;
            }
            for (size_t k = (k_inc * k_inc + 4 * k_inc - 2 * k_inc * (i & 1)) / 3; k < sieve.size(); k += 2 * k_inc)
            {
                sieve[k] = false;
            }
        }
    }
    const auto num_primes = std::count(sieve.begin(), sieve.end(), true) + 2;
    primes.reserve(num_primes);
    for (size_t i = 1; i < sieve.size(); ++i)
    {
        if (sieve[i])
        {
            primes.push_back(3 * i + 1 | 1);
        }
    }
    return primes;
}

// True if n is prime.
template <class T>
bool is_prime(T n)
{
    if (n < 2)
    {
        return false;
    }
    if (n == 2)
    {
        return true;
    }
    if (n % 2 == 0)
    {
        return false;
    }
    const T end_i = static_cast<T>(std::sqrt(n)) + 1;
    for (int i = 3; i < end_i; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
