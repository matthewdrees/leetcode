// Project Euler problem 41. Pandigital prime.
// We shall say that an n-digit number is pandigital if it makes use of all the
// digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
// also prime.
//
// What is the largest n-digit pandigital prime that exists?
#include "project_euler_common.h"

#include <cassert>
#include <iostream>
#include <numeric>

// Return the largest pandigital prime
int largest_pandigital_prime(int n)
{
    assert(n > 1 && n < 10);
    std::string s = std::string("123456789").substr(0, static_cast<size_t>(n));
    int max = 0;
    do
    {
        const int i = std::stoi(s);
        if (is_prime(i))
        {
            if (i > max)
            {
                max = i;
            }
        }
    } while (std::next_permutation(s.begin(), s.end()));
    return max;
}

int main()
{
    // Note it turns out there are no pandigital primes with n == 8 or n == 9.
    for (int n = 7; n > 0; --n)
    {
        const int p = largest_pandigital_prime(n);
        if (p > 0)
        {
            std::cout << p << '\n';
            break;
        }
    }
    return 0;
}
