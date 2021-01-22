// Unit tests.
#include "statistics.hpp"

#include <boost/math/special_functions/relative_difference.hpp>

#include <iostream>

int test_gamma_n_over_2()
{
    struct TestCase
    {
        int n;
        double expected;
    };
    TestCase testCases[] = {
        {1, 1.772453850905516},
        {2, 1.0},
        {3, 0.886226925452758},
        {4, 1.0},
        {5, 1.329340388179137},
        {6, 2.0},
        {7, 3.323350970447843},
        {8, 6.0},
        {9, 11.63172839656745},
        {10, 24.0},
        {30, 87178291200.0},
        {31, 334838609873.556},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = gamma_n_over_2(tc.n);
        if (boost::math::relative_difference(tc.expected, actual) > 0.0000000000001)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_TDisribution()
{
    int num_fails = 0;
    TDistribution td(9);
    {
        const double expected = 0.388035;
        const double actual = td.get_intermediate_calc();
        if (boost::math::relative_difference(expected, actual) > 0.000001)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(dof: " << td.get_dof()
                      << "), expected: " << expected << ", actual: " << actual << "\n";
        }
    }

    struct TestCase
    {
        double x;
        double expected;
    };
    TestCase testCases[] = {
        {0.0, 0.38803},
        {0.11, 0.38544},
        {0.22, 0.37777},
        {0.33, 0.36539},
        {0.44, 0.34886},
        {0.55, 0.32892},
        {0.66, 0.30636},
        {0.77, 0.28205},
        {0.88, 0.25682},
        {0.99, 0.23142},
        {1.1, 0.20652},
    };
    for (const auto &tc : testCases)
    {
        const auto actual = td(tc.x);
        if (boost::math::relative_difference(tc.expected, actual) > 0.00005)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(: " << tc.x
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_gamma_n_over_2() + test_TDisribution();
    return num_fails == 0 ? 0 : 1;
}
