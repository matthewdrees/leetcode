// Project Euler problem 66. Diophantine equation.
//
// Consider quadratic Diophantine equations of the form:
//
// x² – Dy² = 1
//
// For example, when D=13, the minimal solution in x is 649² – 13×180² = 1.
//
// It can be assumed that there are no solutions in positive integers when D is square.
//
// By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
//
// 3² – 2×2² = 1
// 2² – 3×1² = 1
// 9² – 5×4² = 1
// 5² – 6×2² = 1
// 8² – 7×3² = 1
//
// Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
//
// Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.
#include "project_euler_common.h"

#include <cmath>
#include <iostream>
#include <limits>

template <class T>
T minimal_diophantine_solution_x(int d)
{
    T x = 1;
    T x2 = x * x;
    T y = 1;
    T y2 = y * y;
    T dy2p1 = d * y2 + 1;

    const T largest_x = 3037000498; // sqrt(2^63-1)
    // const int64_t largest_x = static_cast<int64_t>(std::sqrt(numeric_limit<int64_t>::max())); // sqrt(2^63-1)
    while (true)
    {
        if (x2 < dy2p1)
        {
            if (x == largest_x)
            {
                break;
            }
            ++x;
            x2 = x * x;
        }
        else if (dy2p1 < x2)
        {
            ++y;
            y2 = y * y;
            dy2p1 = d * y2 + 1;
        }
        else
        {
            return x;
        }
    }

    std::cerr << "No solution for " << d << '\n';
    return 0;
}

int pe66(int d_max)
{
    const auto primes = get_primes(d_max);
    int max_x = 0;
    int d_for_max_x = 0;
    for (int d : primes)
    {
        const int x = minimal_diophantine_solution_x(d);
        std::cout << "d: " << d << ", x: " << x << '\n';
        if (x > max_x)
        {
            max_x = x;
            d_for_max_x = d;
        }
    }
    return d_for_max_x;
}

int test_minimal_diophantine_solution_x()
{
    struct TestCase
    {
        int d;
        int64_t expected;
    };
    TestCase testCases[] = {
        {2, 3},
        {3, 2},
        {5, 9},
        {6, 5},
        {7, 8},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = minimal_diophantine_solution_x(tc.d);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(d: " << tc.d
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    // std::cout << pe66(200) << '\n';
    int128_t whaaat = std::numeric_limits<int128_t>::max();
    std::cout << whaaat << '\n';
    const int num_fails = test_minimal_diophantine_solution_x();
    return num_fails == 0 ? 0 : 1;
}