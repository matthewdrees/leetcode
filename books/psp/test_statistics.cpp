// Unit tests.
#include "statistics.hpp"

#include <cassert>
#include <iostream>
#include <vector>

// Test data
const std::vector<double> estimated_proxy_size_data = {130, 650, 99, 150, 128, 302, 95, 945, 368, 961};
const std::vector<double> plan_added_modified_size = {163, 765, 141, 166, 137, 355, 136, 1206, 433, 1130};
const std::vector<double> actual_added_modified_size = {186, 699, 132, 272, 291, 331, 199, 1890, 788, 1601};
const std::vector<double> actual_developent_hours = {15.0, 69.9, 6.5, 22.4, 28.4, 65.9, 19.4, 198.7, 38.8, 138.2};

// Convert to
std::vector<statistics::Point> to_points(const std::vector<double> &v1, const std::vector<double> &v2)
{
    assert(v1.size() == v2.size());
    std::vector<statistics::Point> points;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        statistics::Point p;
        p.x = v1[i];
        p.y = v2[i];
        points.push_back(std::move(p));
    }
    return points;
}

int test_linear_regression()
{
    struct TestCase
    {
        std::vector<double> x_data;
        std::vector<double> y_data;
        statistics::SlopeIntercept expected;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, {1.7278770829565129, -22.531347355753155}},
        {estimated_proxy_size_data, actual_developent_hours, {0.16810492853057193, -4.0305666415029293}},
        {plan_added_modified_size, actual_added_modified_size, {1.4309569289543411, -23.919249491650817}},
        {plan_added_modified_size, actual_developent_hours, {0.1401508866743113, -4.5978907075409836}},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto points = to_points(tc.x_data, tc.y_data);
        const auto actual = statistics::linear_regression(points);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << "FAIL, " << __FUNCTION__ << "()"
                      << ", expected: " << tc.expected.slope << ", " << tc.expected.y_intercept
                      << ", actual: " << actual.slope << ", " << actual.y_intercept << "\n";
        }
    }
    return num_fails;
}

int test_correlation()
{
    struct TestCase
    {
        std::vector<double> x_data;
        std::vector<double> y_data;
        double expected;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, 0.95449657410468258},
        {estimated_proxy_size_data, actual_developent_hours, 0.93330689814055112},
        {plan_added_modified_size, actual_added_modified_size, 0.96311409314905272},
        {plan_added_modified_size, actual_developent_hours, 0.94803298743005071},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto points = to_points(tc.x_data, tc.y_data);
        const double actual = statistics::correlation(points);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << "FAIL, " << __FUNCTION__ << "()"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_get_projection()
{
    struct TestCase
    {
        statistics::SlopeIntercept si;
        double xk;
        double expected;
    };

    TestCase testCases[] = {
        {{1.7279, -22.55}, 386.0, 644.4194},
        {{0.1681, -4.039}, 386.0, 60.8476},
        {{1.43097, -23.92}, 386.0, 528.43442000000005},
        {{0.140164, -4.604}, 386.0, 49.499304000000002},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const double actual = statistics::get_projection(tc.si, tc.xk);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << "FAIL, " << __FUNCTION__ << "()"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

namespace statistics
{
    double gamma_n_over_2(int numerator);
}

int test_gamma_n_over_2()
{
    struct TestCase
    {
        int n;
        double expected;
    };
    TestCase testCases[] = {
        {1, 1.7724538509055159},
        {2, 1.0},
        {3, 0.88622692545275794},
        {4, 1.0},
        {5, 1.329340388179137},
        {6, 2.0},
        {7, 3.3233509704478426},
        {8, 6.0},
        {9, 11.63172839656745},
        {10, 24.0},
        {30, 87178291200.0},
        {31, 334838609873.55646},
        {340, 4.2690680090047027e+304},
        {341, 5.5620924145599975e+305},
        {342, 7.257415615307994e+306},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = statistics::gamma_n_over_2(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_TDisribution()
{
    int num_fails = 0;
    statistics::TDistribution td(9);
    {
        const double expected = 0.38803490887166864;
        const double actual = td.get_intermediate_calc();
        if (expected != actual)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(dof: " << td.get_dof() << ")"
                      << ", expected: " << expected
                      << ", actual: " << actual << "\n";
        }
    }

    struct TestCase
    {
        double x;
        double expected;
    };
    TestCase testCases[] = {
        {0.0, 0.38803490887166864},
        {0.11, 0.38543693984483191},
        {0.22, 0.37776732398026308},
        {0.33, 0.36538748960779849},
        {0.44, 0.34886333127019764},
        {0.55, 0.32891596328171846},
        {0.66, 0.30636259289430617},
        {0.77, 0.28205497140663432},
        {0.88, 0.25682234441928659},
        {0.99, 0.23142425829711366},
        {1.1, 0.206516442244851},
    };
    for (const auto &tc : testCases)
    {
        const auto actual = td(tc.x);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << __FUNCTION__ << "(x: " << tc.x << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_significance()
{
    struct TestCase
    {
        std::vector<double> x_data;
        std::vector<double> y_data;
        double expected;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, 1.7751717935166056e-05},
        {estimated_proxy_size_data, actual_developent_hours, 7.9820275384667738e-05},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto points = to_points(tc.x_data, tc.y_data);
        const double actual = statistics::significance(points);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << "FAIL, " << __FUNCTION__ << "()"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_prediction_range()
{
    struct TestCase
    {
        std::vector<double> x_data;
        std::vector<double> y_data;
        double xk;
        double expected;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, 386.0, 230.00171969804339},
        {estimated_proxy_size_data, actual_developent_hours, 386.0, 27.557647472300467},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto points = to_points(tc.x_data, tc.y_data);
        const double actual = statistics::prediction_range(points, tc.xk, 70.0);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr.precision(17);
            std::cerr << "FAIL, " << __FUNCTION__ << "(xk: " << tc.xk << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_gamma_n_over_2() + test_TDisribution() + test_correlation() + test_get_projection() + test_linear_regression() + test_significance() + test_prediction_range();
    return num_fails == 0 ? 0 : 1;
}
