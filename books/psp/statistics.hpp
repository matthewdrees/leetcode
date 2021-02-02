// Statistics functions.
#pragma once

#include <cmath>
#include <vector>

namespace statistics
{
    // The slope and y-intercept parameters for a line.
    struct SlopeIntercept
    {
        double slope = 1.0;
        double y_intercept = 0.0;
    };
    bool operator==(const SlopeIntercept &si1, const SlopeIntercept &si2);
    bool operator!=(const SlopeIntercept &si1, const SlopeIntercept &si2);

    struct Point
    {
        double x = 0.0;
        double y = 0.0;
    };

    // Calculate the best-fit y = mx + b line that fits the provided points.
    // \param points: Data points.
    // \return: y = mx + b slope/intercept parameters of the best fit line.
    SlopeIntercept linear_regression(const std::vector<Point> &points);

    // Get a value of y, given x and slope/intercept parameters.
    // \param slope_intercept: m and b values of y = mx + b.
    // \param x: x value for equation.
    // \return: Projected y value.
    double get_projection(SlopeIntercept slope_intercept, double x);

    // Calculate the Pearson correlation coefficient.
    // \param points: Data points.
    // \return: Pearson correlation.
    double correlation(const std::vector<Point> &points);

    // Factorial of n.
    // \param n: 0 - 170.
    // \return: n!
    double factorial(int64_t);

    // Calculate significance of points.
    // \param points: Data points. Must have at least 3 points. All must be finite.
    // \return: Statistical significance, or nan if not calculated.
    double significance(const std::vector<Point> &points);

    // Calculate estimate prediction range.
    // \param points: Data points. Must have at least 3 points. All must be finite.
    // \param x_estimate: The x value to estimate.
    // \param percent: Percent of prediction range estimate, typically 70% or 90%.
    // \return: prediction range calculation, or nan if not calculated.
    double prediction_range(const std::vector<Point> &points, double x_estimate, double percent);

    // t-distribution function
    class TDistribution
    {
        // Degrees of freedom for this t-distribution.
        // Valid range: (0 < dof <= 341).
        const int dof;

        // Intermediate calculation that doesn't change with x.
        const double intermediate_calc;

    public:
        explicit TDistribution(int degrees_of_freedom);

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
} // namespace statistics
