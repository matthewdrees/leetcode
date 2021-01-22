// Simpsons rule for integration.
#include <cmath>
#include <optional>

#include <boost/math/special_functions/relative_difference.hpp>

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

// Find the value of x from a function with the given integration_value.
//
// \param integration_value: The integration value to search for. Must be finite and > 0.
// \param acceptable_error: +/- error tolerance for integration_value. Must be
//        finite and > 0. The returned value of x might be for an
//        integration_value outside the bounds of acceptable_error if the
//        error resolution is smaller than the resultion for the calculation.
//        I.e this is an optimization to tell the search algorithm to stop
//        early if the answer is "good enough".
// \param func: Function to integrate. Must be positive values for x > 0 up to
//        and including x.
// \return: false if no answer found, otherwise a finite value for x.
template <class Func>
std::optional<double> find_x_from_integration_value(double integration_value, double acceptable_error, Func func)
{
    assert(std::isfinite(integration_value) && integration_value > 0.0);
    assert(std::isfinite(acceptable_error) && acceptable_error > 0.0);
    const double acceptable_relative_error = acceptable_error / integration_value;

    double x = 1.0;
    double delta_x = 1.0;

    while (true)
    {
        if (!std::isfinite(x))
        {
            return {};
        }
        const auto val = simpsons_rule(0.0, x, acceptable_error, func);
        if (!val || *val <= 0.0)
        {
            return {};
        }
        if (integration_value < *val)
        {
            break;
        }
        x += delta_x;
        delta_x *= 2.0;
    }

    delta_x /= 2.0;
    x -= delta_x;
    for (; delta_x > 0.0; delta_x /= 2.0)
    {
        const auto val = simpsons_rule(0.0, x, acceptable_error, func);
        if (!val || *val <= 0.0)
        {
            return {};
        }
        const double relative_error = boost::math::relative_difference(integration_value, *val);
        if (relative_error <= acceptable_relative_error)
        {
            // Found the answer.
            break;
        }
        // Track x to make sure it's changing. The delta_x value might get too small at some point.
        const double prev_x = x;
        if (*val < integration_value)
        {
            x += delta_x;
        }
        else
        {
            x -= delta_x;
        }
        if (prev_x == x)
        {
            // It's not within acceptable_error, but it's as close as we can get. Return it.
            break;
        }
        // Simpsons_rule can't handle a zero-length range, so fix a low value.
        const double x_lo_thresh = 0.125;
        if (x < x_lo_thresh)
        {
            return {};
        }
    }
    return x;
}
