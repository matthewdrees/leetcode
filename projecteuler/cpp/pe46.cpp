// Project Euler problem 46. Goldbach's other conjecture.
//
// It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
//
// 9 = 7 + 2×1²
// 15 = 7 + 2×2²
// 21 = 3 + 2×3²
// 25 = 7 + 2×3²
// 27 = 19 + 2×2²
// 33 = 31 + 2×1²
//
// It turns out that the conjecture was false.
//
// What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
#include "project_euler_common.h"

#include <iostream>

int goldbachs_other_conjecture()
{
    for (int i = 4; i < 6000; ++i)
    {
        if (i % 2 == 0 || is_prime(i))
        {
            continue;
        }

        for (int j = 1; j < i; ++j)
        {
            const int second_term = 2 * j * j;
            const int first_term = i - second_term;
            if (first_term < 2)
            {
                return i;
            }

            if (is_prime(first_term))
            {
                //std::cout << i << " = " << first_term << " + 2x" << j << "^2"
                //          << "\n";
                break;
            }
        }
    }
    return 0;
}

int main()
{
    std::cout << goldbachs_other_conjecture() << '\n';
}
