// PSP program 4.
//
// Using PSP1.1, write a program to calculate relative size ranges for very small,
// small, medium, large, and very large ranges using standard deviation.
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

bool within_relative_distance(float f1, float f2, float distance)
{
    const float error = std::fabs((f1 - f2) / std::min(f1, f2));
    return error <= distance;
}

// Relative size table.
//
// Contains typical values for very small, small, medium, large, and very large values
// of given data set. (E.g. lines of code)
struct RelativeSizeTable
{
    float vs = 0.0f; // very small, -2 sigma, 6.68% of values.
    float s = 0.0f;  // small, -1 sigma, 24.17% of values.
    float m = 0.0f;  // medium, average, 38.2% of values.
    float l = 0.0f;  // large, +1 sigma, 24.17% of values.
    float vl = 0.0f; // very large, +2 sigma, 6.68% of values.

    bool operator==(const RelativeSizeTable &other) const
    {
        const float distance = 0.001f;
        return within_relative_distance(this->vs, other.vs, distance) &&
               within_relative_distance(this->s, other.s, distance) &&
               within_relative_distance(this->m, other.m, distance) &&
               within_relative_distance(this->l, other.l, distance) &&
               within_relative_distance(this->vl, other.vl, distance);
    }
    bool operator!=(const RelativeSizeTable &other) const
    {
        return !(*this == other);
    }
};

// Generate the RelativeSizeTable of a given data set.
//
// \param data: data points.
// \return: RelativeSizeTable
RelativeSizeTable generate_relative_size_table(const std::vector<float> &data)
{
    RelativeSizeTable relativeSizeTable;

    // Guard against the math that divides by (data.size() - 1);
    if (data.size() <= 1)
    {
        return relativeSizeTable;
    }
    std::vector<float> ln_data = data;
    for (auto &d : ln_data)
    {
        d = std::log(d);
    }
    const float avg = std::accumulate(ln_data.begin(), ln_data.end(), 0.0f) /
                      static_cast<float>(ln_data.size());
    const float var = std::accumulate(ln_data.begin(), ln_data.end(), 0.0f, [=](float sum, float d) {
                          return sum + std::pow(d - avg, 2.0f);
                      }) /
                      static_cast<float>(ln_data.size() - 1);
    const float stddev = std::sqrt(var);
    relativeSizeTable.vs = std::exp(avg - 2.0f * stddev);
    relativeSizeTable.s = std::exp(avg - stddev);
    relativeSizeTable.m = std::exp(avg);
    relativeSizeTable.l = std::exp(avg + stddev);
    relativeSizeTable.vl = std::exp(avg + 2.0f * stddev);
    return relativeSizeTable;
}

// Convert std::vector<float> to a std::string.
std::string to_string(const std::vector<float> v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto f : v)
    {
        oss << f << ',';
    }
    oss << "\b}";
    return oss.str();
}

// Convert RelativeSizeTable to a std::string.
std::string to_string(const RelativeSizeTable &rst)
{
    const std::vector<float> v = {rst.vs, rst.s, rst.m, rst.l, rst.vl};
    return to_string(v);
}

// unittest. returns # of failed tests.
int test_generate_relative_size_table()
{
    struct TestCase
    {
        std::vector<float> data;
        RelativeSizeTable expected;
    };
    TestCase testCases[] = {
        {{18 / 3.0f,
          18 / 3.0f,
          25 / 3.0f,
          31 / 3.0f,
          37 / 3.0f,
          82 / 5.0f,
          82 / 4.0f,
          87 / 4.0f,
          89 / 4.0f,
          230 / 10.0f,
          85 / 3.0f,
          87 / 3.0f,
          558 / 10.0f},
         {4.3953, 8.5081, 16.4696, 31.8811, 61.7137}},
        {{7,
          12,
          10,
          12,
          10,
          12,
          12,
          12,
          12,
          8,
          8,
          8,
          20,
          14,
          18,
          12},
         {6.3375, 8.4393, 11.2381, 14.9650, 19.9280}}};
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = generate_relative_size_table(tc.data);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FUNCTION__ << "(data: " << to_string(tc.data)
                      << "), expected: " << to_string(tc.expected) << ", actual: " << to_string(actual) << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_generate_relative_size_table();
    return num_fails == 0 ? 0 : 1;
}
