/* projecteuler.net problem 1.

Multiples of 3 and 5.

If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/
#include "project_euler_common.h"

#include <iostream>

// Return the sum of multiples of 3 and 5 up to n.
int sum_of_multiples_of_3_and_5_below(int n)
{
    return add_consecutive_numbers(1, (n - 1) / 3) * 3 + add_consecutive_numbers(1, (n - 1) / 5) * 5 - add_consecutive_numbers(1, (n - 1) / 15) * 15;
}

bool test_sum_of_mulitples_of_3_and_5_below()
{
    struct TestCase
    {
        int n;
        int expected;
    };

    TestCase testCases[] = {
        {0, 0},
        {3, 0},
        {4, 3},
        {5, 3},
        {6, 8},
        {7, 14},
        {9, 14},
        {10, 23},
        {11, 33},
        {16, 60},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = sum_of_multiples_of_3_and_5_below(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

int main()
{
    std::cout << sum_of_multiples_of_3_and_5_below(1000) << '\n';
    return test_sum_of_mulitples_of_3_and_5_below() ? 0 : 1;
}
