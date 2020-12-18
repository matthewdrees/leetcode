// Linear statistics calcualtions.
//
// Problem 3 of PSP.
#include "LinkedList.h"

#include <cmath>

// y intercept and slope parameters for line.
class LinearRegressionParameters
{
public:
    LinearRegressionParameters() : b0(0.0f), b1(1.0f) {}
    LinearRegressionParameters(float b0_, float b1_) : b0(b0_), b1(b1_) {}

    float b0; // y intercept
    float b1; // slope
};

// x/y data point.
struct DataPoint
{
    float x = 0.0f;
    float y = 0.0f;
};

LinearRegressionParameters
calculateLinearRegression(const LinkedList<DataPoint> &data_points)
{
    DataPoint sums;
    float sum_of_multiples;
    float sum_of_x_squared;
    for (std::size_t i = 0; i < data_points.size(); ++i)
    {
        const DataPoint &dp = data_points[i];
        sums.x += dp.x;
        sums.y += dp.y;
        sum_of_multiples += dp.x * dp.y;
        sum_of_x_squared += dp.x * dp.x;
    }
    const float num_points = static_cast<float>(data_points.size());
    const float x_avg = sums.x / num_points;
    const float y_avg = sums.y / num_points;

    LinearRegressionParameters params;
    params.b1 = (sum_of_multiples - num_points * x_avg * y_avg) /
                (sum_of_x_squared - num_points * x_avg * x_avg);
    params.b0 = y_avg - params.b1 * x_avg;
    return params;
}

float getProjection(LinearRegressionParameters params, float x)
{
    return x * params.b1 + params.b0;
}

float calculateCorrelation(const LinkedList<DataPoint> &data_points)
{
    DataPoint sums;
    DataPoint sum_squares;
    float sum_of_multiples = 0.0;
    for (std::size_t i = 0; i < data_points.size(); ++i)
    {
        const DataPoint &dp = data_points[i];
        sums.x += dp.x;
        sums.y += dp.y;
        sum_squares.x += dp.x * dp.x;
        sum_squares.y += dp.y * dp.y;
        sum_of_multiples += dp.x * dp.y;
    }
    const float num_points = static_cast<float>(data_points.size());
    const float numerator = num_points * sum_of_multiples - sums.x * sums.y;
    const float den_part1 = num_points * sum_squares.x - sums.x * sums.x;
    const float den_part2 = num_points * sum_squares.y - sums.y * sums.y;
    return numerator / std::sqrt(den_part1 * den_part2);
}
