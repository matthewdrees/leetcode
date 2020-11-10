/* projecteuler.net problem 27. Quadratic primes.

Euler discovered the remarkable quadratic formula:

    n² + n + 41

It turns out that the formula will produce 40 primes for the consecutive integer values
0 ≤ n ≤ 39. However, when n = 40, 40² + 40 + 41 = 40 (40 + 1) + 41 is divisible by 41,
and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

The incredible formula n² - 79n + 1601 was discovered, which produces 80 primes for the
consecutive values 0 ≤ n ≤ 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

    n² + an + b, where |a| < 1000 and |b| ≤ 1000

    where |n| is the modulus/absolute value of n
    e.g. |11| = 11 and |-4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that produces
the maximum number of primes for consecutive values of n, starting with n = 0.
*/
#include "project_euler_common.h"

#include <iostream>
#include <unordered_set>

std::unordered_set<int> get_primes_as_unordered_set(int n)
{
    const auto primes_v = get_primes(n);
    return std::unordered_set<int>(primes_v.begin(), primes_v.end());
}

int main()
{
    const auto primes = get_primes_as_unordered_set(100000);
    const auto primes_to_1k = get_primes(1000);

    int max_num_primes = 0;
    int max_num_primes_a = 0;
    int max_num_primes_b = 0;
    for (const int b : primes_to_1k)
    {
        for (const int a : primes_to_1k)
        {
            if (a >= b)
            {
                break;
            }

            int num_primes = 0;
            for (int n = 0; n < b; ++n)
            {
                int p0 = n * n - a * n + b;
                if (primes.find(p0) != primes.end())
                {
                    num_primes += 1;
                }
                else
                {
                    break;
                }
            }
            if (num_primes > max_num_primes)
            {
                max_num_primes = num_primes;
                max_num_primes_a = -a;
                max_num_primes_b = b;
                // std::cout << "Found a: -" << a << ", b: " << b << ", # primes: " << num_primes << '\n';
            }
        }
    }

    std::cout << max_num_primes_a * max_num_primes_b << '\n';
}
