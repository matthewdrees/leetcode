// PSP problem 5. Using PSP2, write a program to numerically integrate a function
// using Simpson’s rule.  Use the t-distribution as the function.
#include <iostream>

#include <boost/math/special_functions/relative_difference.hpp>

#include "integration.hpp"
#include "statistics.hpp"

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

int test_simpsons_rule_iteration()
{
    struct TestCase
    {
        int num_segments;
        double expected;
    };
    TestCase testCases[] = {
        {10, 0.3500589},
        {20, 0.35005864},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = simpsons_rule_iteration(0.0, 1.1, tc.num_segments, TDistribution(9));
        if (boost::math::relative_difference(tc.expected, actual) > 0.00000005)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(num_segments: " << tc.num_segments
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_simpsons_rule()
{
    struct TestCase
    {
        double x_end;
        int dof;
        double expected;
    };
    TestCase testCases[] = {
        {1.1, 9, 0.35006},
        {1.1812, 10, 0.36757},
        {2.750, 30, 0.49500},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = simpsons_rule(0.0, tc.x_end, 0.000005, TDistribution(tc.dof));
        if (actual)
        {
            const auto rel_diff = boost::math::relative_difference(tc.expected, *actual);
            const double diff_thresh = 0.0000137;
            if (rel_diff > diff_thresh)
            {
                ++num_fails;
                std::cerr << __FUNCTION__ << "(x_end: " << tc.x_end << ", dof: " << tc.dof
                          << "), expected: " << tc.expected << ", actual: " << *actual
                          << ", rel_diff: " << rel_diff << " > " << diff_thresh << "\n";
            }
        }
        else
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(x_end: " << tc.x_end << ", dof: " << tc.dof
                      << "), expected: " << tc.expected << ", actual: false\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_gamma_n_over_2() + test_TDisribution() + test_simpsons_rule_iteration() + test_simpsons_rule();
    return num_fails == 0 ? 0 : 1;
}
