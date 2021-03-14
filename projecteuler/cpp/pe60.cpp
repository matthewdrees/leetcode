// Project Euler problem 60. Prime sets.
#include <iostream>

#include "project_euler_common.h"

int concatenate_numbers(int n1, int n2)
{
    int tmp = n2;
    while (tmp != 0)
    {
        tmp /= 10;
        n1 *= 10;
    }
    return n1 + n2;
}

bool is_prime_pair_set(int p1, int p2)
{
    return is_prime(concatenate_numbers(p1, p2)) && is_prime(concatenate_numbers(p2, p1));
}

int pe60()
{
    const auto primes = get_primes(8500);

    for (size_t a = 1; a < primes.size(); ++a)
    {
        for (size_t b = a + 1; b < primes.size(); ++b)
        {
            if (is_prime_pair_set(primes[a], primes[b]))
            {
                for (size_t c = b + 1; c < primes.size(); ++c)
                {
                    if (is_prime_pair_set(primes[b], primes[c]) &&
                        is_prime_pair_set(primes[a], primes[c]))
                    {
                        for (size_t d = c + 1; d < primes.size(); ++d)
                        {
                            if (is_prime_pair_set(primes[c], primes[d]) &&
                                is_prime_pair_set(primes[b], primes[d]) &&
                                is_prime_pair_set(primes[a], primes[d]))
                            {
                                for (size_t e = d + 1; e < primes.size(); ++e)
                                {
                                    if (is_prime_pair_set(primes[d], primes[e]) &&
                                        is_prime_pair_set(primes[c], primes[e]) &&
                                        is_prime_pair_set(primes[b], primes[e]) &&
                                        is_prime_pair_set(primes[a], primes[e]))
                                    {
                                        return primes[a] + primes[b] + primes[c] + primes[d] + primes[e];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    std::cout << pe60() << "\n";
    return 0;
}
