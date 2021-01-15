// PSP problem 5. Using PSP2, write a program to numerically integrate a function
// using Simpson’s rule.  Use the t-distribution as the function.
#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/relative_difference.hpp>

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

// The gamma function for the special case of n/2.
//
// \param numerator: n/2 for gamma function. Range: 0 < numerator <= 40.
// \return gamma function for n/2.
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

class TDistribution
{
    // Degrees of freedom for this t-distribution.
    // Valid range: (0 < dof <= 40).
    const int dof;

    // Intermediate calculation that doesn't change with x.
    const double intermediate_calc;

public:
    explicit TDistribution(int degrees_of_freedom) : dof(degrees_of_freedom),
                                                     intermediate_calc(gamma_n_over_2(dof + 1) /
                                                                       gamma_n_over_2(dof) /
                                                                       std::sqrt(dof * boost::math::constants::pi<double>()))
    {
        assert(dof > 0);
        assert(dof <= 40);
        assert(std::isfinite(intermediate_calc));
    }

    double get_dof() const noexcept { return dof; }
    double get_intermediate_calc() const noexcept { return intermediate_calc; }

    // Calculate y for a given x.
    // \param x: x value.
    // \return: y value calculation.
    double operator()(double x) const
    {
        return intermediate_calc * std::pow(1 + x * x / dof, -(dof + 1) / 2.0);
    }
};

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

// Iteration of Simpson's rule.
//
// A single iteration of Simpson's rule.
//
// \param x_begin: x range start of integration, must be finite.
// \param x_end: x range end of integration, must be finite, and > x_begin.
// \num_segments: Number of segments for integration. Must be positive and even.
// \func: Function to integrate, passed as a functor object.
// \return: Integration calculation.
template <class Func>
double simpsons_rule_iteration(double x_begin, double x_end, int num_seg, Func func)
{
    assert(std::isfinite(x_begin));
    assert(std::isfinite(x_end));
    assert(x_begin < x_end);
    assert(num_seg > 0);
    assert(num_seg % 2 == 0);

    const double W = (x_end - x_begin) / num_seg;
    double p = func(x_begin);
    for (int i = 1; i < num_seg; i += 2)
    {
        p += 4 * func(x_begin + i * W);
    }
    for (int i = 2; i < num_seg; i += 2)
    {
        p += 2 * func(x_begin + i * W);
    }
    p += func(x_end);
    return W / 3.0 * p;
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

// Simpsons rule for integrating a function over a range of x.
//
// \param x_begin: x range start of integration, must be finite.
// \param x_end: x range end of integration, must be finite, and > x_begin.
// \acceptable_error: Allowable error in the calculated answer.
// \func: Function to integrate, passed as a functor object.
// \return: Integration calculation, or false if couldn't be calculated.
template <class Func>
std::optional<double> simpsons_rule(double x_begin, double x_end, double acceptable_error, Func func)
{
    assert(std::isfinite(x_begin));
    assert(std::isfinite(x_end));
    assert(x_begin < x_end);
    assert(std::isfinite(acceptable_error));
    int num_segments = 16;
    double p1 = simpsons_rule_iteration(x_begin, x_end, num_segments, func);
    const int num_segments_end = 1048576; // 2^20
    for (num_segments = 32; num_segments <= num_segments_end; num_segments *= 2)
    {
        const double p2 = simpsons_rule_iteration(x_begin, x_end, num_segments, func);
        if (abs(p2 - p1) <= acceptable_error)
        {
            return p2;
        }
        p1 = p2;
    }
    return {};
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
