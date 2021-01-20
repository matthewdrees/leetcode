// Simpsons rule for integration.
#include <cmath>
#include <optional>

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
