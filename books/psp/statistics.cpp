#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

#include <boost/math/constants/constants.hpp>

#include "statistics.hpp"

#include "integration.hpp"

namespace statistics
{
    bool operator==(const SlopeIntercept &si1, const SlopeIntercept &si2)
    {
        return si1.slope == si2.slope && si1.y_intercept == si2.y_intercept;
    }
    bool operator!=(const SlopeIntercept &si1, const SlopeIntercept &si2)
    {
        return !(si1 == si2);
    }

    // Factorial of n.
    // \param n: 0 - 170.
    // \return: n!
    double factorial(int64_t n)
    {
        assert(n >= 0);
        assert(n <= 170); // factorial(171.0) overflows a double.
        double fac = 1.0;
        for (int i = 2; i <= n; ++i)
        {
            fac *= i;
        }
        return fac;
    }

    // The gamma function for the special case of n/2.
    // \param numerator: n/2 for gamma function. Range: 0 < numerator <= 342.
    // \return: Gamma function for n/2.
    double gamma_n_over_2(int numerator)
    {
        assert(numerator > 0);
        assert(numerator <= 342);
        if (numerator % 2 == 0)
        {
            return factorial(numerator / 2 - 1);
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
        assert(dof <= 341);
        assert(std::isfinite(intermediate_calc));
    }

    SlopeIntercept linear_regression(const std::vector<Point> &points)
    {
        Point sums;
        double sum_of_multiples;
        double sum_of_x_squared;
        for (const auto p : points)
        {
            sums.x += p.x;
            sums.y += p.y;
            sum_of_multiples += p.x * p.y;
            sum_of_x_squared += p.x * p.x;
        }
        const double num_points = static_cast<double>(points.size());
        const double x_avg = sums.x / num_points;
        const double y_avg = sums.y / num_points;

        SlopeIntercept si;
        si.slope = (sum_of_multiples - num_points * x_avg * y_avg) /
                   (sum_of_x_squared - num_points * x_avg * x_avg);
        si.y_intercept = y_avg - si.slope * x_avg;
        return si;
    }

    double get_projection(SlopeIntercept si, double x)
    {
        return x * si.slope + si.y_intercept;
    }

    double correlation(const std::vector<Point> &points)
    {
        Point sums;
        Point sum_squares;
        double sum_of_multiples = 0.0;
        for (const auto p : points)
        {
            sums.x += p.x;
            sums.y += p.y;
            sum_squares.x += p.x * p.x;
            sum_squares.y += p.y * p.y;
            sum_of_multiples += p.x * p.y;
        }
        const double num_points = static_cast<double>(points.size());
        const double numerator = num_points * sum_of_multiples - sums.x * sums.y;
        const double den_part1 = num_points * sum_squares.x - sums.x * sums.x;
        const double den_part2 = num_points * sum_squares.y - sums.y * sums.y;
        return numerator / std::sqrt(den_part1 * den_part2);
    }

    double significance(const std::vector<Point> &points)
    {
        assert(points.size() >= 3);
        const double n = static_cast<double>(points.size());
        const double correl = correlation(points);
        const double x = abs(correl) * std::sqrt(n - 2) / std::sqrt(1 - correl * correl);
        const double acceptable_error = 0.00000000001;
        const double dof = n - 2;
        const auto p = integration::simpsons_rule(0.0, x, acceptable_error, TDistribution(dof));
        if (!p)
        {
            return std::numeric_limits<double>::quiet_NaN();
        }
        const double tail_area = 1 - 2 * (*p);
        return tail_area;
    }

    double prediction_range(const std::vector<Point> &points, double x_estimate, double percent)
    {
        assert(points.size() >= 3);
        assert(std::isfinite(x_estimate));
        assert(std::isfinite(percent));
        assert(percent >= 0 && percent <= 100);

        const double n = static_cast<double>(points.size());
        const SlopeIntercept si = linear_regression(points);
        const double stddev = std::sqrt(1.0 / (n - 2) * std::accumulate(points.begin(), points.end(), 0.0, [=](double total, const auto &p) {
                                            return total + std::pow(p.y - si.y_intercept - si.slope * p.x, 2);
                                        }));

        const double x_avg = std::accumulate(points.begin(), points.end(), 0.0, [=](double total, const auto &p) {
                                 return total + p.x;
                             }) /
                             n;
        const double x_avg2 = std::accumulate(points.begin(), points.end(), 0.0, [=](double total, const auto &p) {
            return total + std::pow(p.x - x_avg, 2);
        });
        const double calc = std::sqrt(1.0 + 1.0 / n + std::pow(x_estimate - x_avg, 2) / x_avg2);

        const double integration_value = percent / 2 / 100;
        const double acceptable_error = 0.00000000001;
        const auto t_dist_x = integration::find_x_from_integration_value(integration_value, acceptable_error, TDistribution(n - 2));
        if (!t_dist_x)
        {
            return std::numeric_limits<double>::quiet_NaN();
        }

        return stddev * calc * (*t_dist_x);
    }
} // namespace statistics
