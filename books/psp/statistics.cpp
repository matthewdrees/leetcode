#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "statistics.hpp"

// Factorial of n
int64_t factorial(int64_t n)
{
    assert(n >= 0);
    assert(n <= 20); // factorial(21) overflows an int64_t.
    int64_t fac = 1;
    for (int i = 2; i <= n; ++i)
    {
        fac *= i;
    }
    return fac;
}

double gamma_n_over_2(int numerator)
{
    assert(numerator > 0);
    assert(numerator <= 40);
    if (numerator % 2 == 0)
    {
        return static_cast<double>(factorial((numerator / 2) - 1));
    }

    double d = std::sqrt(boost::math::constants::pi<double>());
    for (int i = 1; i < numerator; i += 2)
    {
        d *= static_cast<double>(i) / 2.0;
    }
    return d;
}

TDistribution::TDistribution(int degrees_of_freedom) : dof(degrees_of_freedom),
                                                       intermediate_calc(gamma_n_over_2(dof + 1) /
                                                                         gamma_n_over_2(dof) /
                                                                         std::sqrt(dof * boost::math::constants::pi<double>()))
{
    assert(dof > 0);
    assert(dof <= 40);
    assert(std::isfinite(intermediate_calc));
}
