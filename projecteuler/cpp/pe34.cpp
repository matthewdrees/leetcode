// Project Euler problem 34. Digit factorials.
//
// 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
//
// Find the sum of all numbers which are equal to the sum of the factorial of their digits.
//
// Note: As 1! = 1 and 2! = 2 are not sums they are not included.
#include "project_euler_common.h"

#include <iostream>

// Return true if n is sum of its digit factorials.
//
// \param n: Number considered for sum of digit factorials.
// \return: true if is sum of its digit factorials.
bool is_sum_of_digit_factorials(int n)
{
    if (n <= 9)
    {
        return false;
    }
    int total = 0;
    int x = n;
    while (x != 0)
    {
        total += factorial(x % 10);
        x = x / 10;
    }
    return total == n;
}

int test_is_sum_of_digit_factorials()
{
    struct TestCase
    {
        int n;
        bool expected;
    };
    TestCase testCases[] = {
        {1, false},
        {2, false},
        {100, false},
        {144, false},
        {145, true},
        {40585, true},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_sum_of_digit_factorials(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    int total = 0;
    for (int i = 10; i < 100000; ++i)
    {
        if (is_sum_of_digit_factorials(i))
        {
            total += i;
        }
    }
    std::cout << total << '\n';

    return test_is_sum_of_digit_factorials() == 0 ? 0 : 1;
}
