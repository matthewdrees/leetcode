// Project Euler problem 58.
#include "project_euler_common.h"

#include <algorithm>
#include <iostream>

int main()
{
    const int NUM_MAX = 1'000'000'000;

    double num_primes = 3.0;
    double total = 4.0;
    int n = 9;
    int delta = 4;
    while (n < NUM_MAX)
    {
        for (int _ = 0; _ < 4; ++_)
        {
            n += delta;
            if (is_prime(n))
            {
                num_primes += 1.0;
            }
            total += 1.0;

            if (num_primes / total < 0.1)
            {
                std::cout << delta + 1 << "\n";
                return 0;
            }
        }
        delta += 2;
    }
    std::cout << num_primes / total << "\n";
    std::cout << delta + 1 << "\n";
    std::cout << "NUM_MAX not big enough\n";
    return 1;
}
