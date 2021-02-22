// Project Euler problem 53. Combinatoric selections.
//
// There are exactly ten ways of selecting three from five, 12345:
//
//      123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
//
// In combinatorics, we use the notation,  /5\ = 10.
//                                         \3/
//
// It is not until /23\, that a value exceeds one-million: 1144066
//                 \10/
//
// How many, not necessarily distinct, values of /n\ for 1 <= n <= 100 are > 1 million?
//                                               \r/
#include <iostream>

#include <boost/math/special_functions/binomial.hpp>

int pe53()
{
    int count = 0;
    for (unsigned n = 1; n <= 100; ++n)
    {
        for (unsigned r = 1; r <= n; ++r)
        {
            try
            {
                const double bc = boost::math::binomial_coefficient<double>(n, r);
                if (bc < 1'000'000.0)
                {
                    continue;
                }
            }
            catch (...)
            {
                // Don't care about overflows.
            }
            count += 1;
        }
    }
    return count;
}

int main()
{
    std::cout << pe53() << "\n";
    return 0;
}
