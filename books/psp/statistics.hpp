// t-distribution function.
#include <cmath>

// The gamma function for the special case of n/2.
//
// \param numerator: n/2 for gamma function. Range: 0 < numerator <= 40.
// \return gamma function for n/2.
double gamma_n_over_2(int numerator);

// t-distribution function
class TDistribution
{
    // Degrees of freedom for this t-distribution.
    // Valid range: (0 < dof <= 40).
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
