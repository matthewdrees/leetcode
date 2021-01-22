// Unit tests.
#include <iostream>
#include <string>

#include <boost/math/special_functions/relative_difference.hpp>

#include "integration.hpp"
#include "statistics.hpp"

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

int test_find_x_from_integration_value()
{
    struct TestCase
    {
        double integration_value;
        int dof;
        double expected;
    };
    TestCase testCases[] = {
        {0.2, 6, 0.55338},
        {0.45, 15, 1.75305},
        {0.495, 4, 4.60409},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const double acceptable_error = 0.00000000001;
        const auto actual = find_x_from_integration_value(tc.integration_value, acceptable_error, TDistribution(tc.dof));
        std::string fail_msg;
        if (actual)
        {
            const auto rel_diff = boost::math::relative_difference(tc.expected, *actual);
            const double diff_thresh = 0.00001 / tc.expected;
            if (rel_diff > diff_thresh)
            {
                fail_msg = std::to_string(*actual) + ", rel_diff: " + std::to_string(rel_diff) + " > " + std::to_string(diff_thresh);
            }
        }
        else
        {
            fail_msg = "false";
        }
        if (!fail_msg.empty())
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(integration_value: " << tc.integration_value
                      << ", acceptable_error: " << acceptable_error
                      << ", TDistribution(" << tc.dof << ")"
                      << "), expected: " << tc.expected << ", actual: " << fail_msg << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_simpsons_rule_iteration() + test_simpsons_rule() + test_find_x_from_integration_value();
    return num_fails == 0 ? 0 : 1;
}
