#include "LinearStats.h"

#include <cassert>
#include <iostream>
#include <vector>

// Helper function to convert useful vector data to our disaterous linked list monstrosity.
static LinkedList<DataPoint> toLinkedList(std::vector<float> x_data, std::vector<float> y_data)
{
    assert(x_data.size() == y_data.size());
    LinkedList<DataPoint> data_points;
    for (size_t i = 0; i < x_data.size(); ++i)
    {
        DataPoint dp;
        dp.x = x_data[i];
        dp.y = y_data[i];
        data_points.push_front(std::move(dp));
    }
    return data_points;
}

// Lame float comparison for our purposes.
bool floats_equal(float f1, float f2, float delta)
{
    return f1 < f2 + delta && f1 > f2 - delta;
}

namespace
{
    const std::vector<float> estimated_proxy_size_data = {130, 650, 99, 150, 128, 302, 95, 945, 368, 961};
    const std::vector<float> plan_added_modified_size = {163, 765, 141, 166, 137, 355, 136, 1206, 433, 1130};
    const std::vector<float> actual_added_modified_size = {186, 699, 132, 272, 291, 331, 199, 1890, 788, 1601};
    const std::vector<float> actual_developent_hours = {15.0, 69.9, 6.5, 22.4, 28.4, 65.9, 19.4, 198.7, 38.8, 138.2};
} // namespace

int test_calculateLinearRegression()
{
    struct TestCase
    {
        std::vector<float> x_data;
        std::vector<float> y_data;
        float b0;
        float b1;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, -22.55, 1.7279},
        {estimated_proxy_size_data, actual_developent_hours, -4.039, 0.1681},
        {plan_added_modified_size, actual_added_modified_size, -23.92, 1.43097},
        {plan_added_modified_size, actual_developent_hours, -4.604, 0.140164},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto data_points = toLinkedList(tc.x_data, tc.y_data);
        const auto params = calculateLinearRegression(data_points);
        const float delta = 0.005;
        if (!floats_equal(tc.b0, params.b0, delta) || !floats_equal(tc.b1, params.b1, delta))
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "()"
                      << ", expected: " << tc.b0 << ", " << tc.b1
                      << ", actual: " << params.b0 << ", " << params.b1 << "\n";
        }
    }
    return num_fails;
}

int test_calculateCorrelation()
{
    struct TestCase
    {
        std::vector<float> x_data;
        std::vector<float> y_data;
        float r;
    };

    TestCase testCases[] = {
        {estimated_proxy_size_data, actual_added_modified_size, 0.9545},
        {estimated_proxy_size_data, actual_developent_hours, 0.9333},
        {plan_added_modified_size, actual_added_modified_size, 0.9631},
        {plan_added_modified_size, actual_developent_hours, 0.9480},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto data_points = toLinkedList(tc.x_data, tc.y_data);
        const float actual = calculateCorrelation(data_points);
        const float delta = 0.05;
        if (!floats_equal(tc.r, actual, delta))
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "()"
                      << ", expected: " << tc.r
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_getProjection()
{
    struct TestCase
    {
        float b0;
        float b1;
        float xk;
        float yk;
    };

    TestCase testCases[] = {
        {-22.55, 1.7279, 386.0, 644.429},
        {-4.039, 0.1681, 386.0, 60.858},
        {-23.92, 1.43097, 386.0, 528.4294},
        {-4.604, 0.140164, 386.0, 49.4994},
    };

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        LinearRegressionParameters params;
        params.b0 = tc.b0;
        params.b1 = tc.b1;
        const float actual = getProjection(params, tc.xk);
        const float delta = 0.05;
        if (!floats_equal(tc.yk, actual, delta))
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "()"
                      << ", expected: " << tc.yk
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails =
        test_calculateCorrelation() +
        test_calculateLinearRegression() +
        test_getProjection();
    return num_fails == 0 ? 0 : 1;
}
