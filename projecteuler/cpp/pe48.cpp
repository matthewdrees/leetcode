// Project Euler problem 48. Self powers.
//
// The series, 1¹ + 2² + 3³ + ... + 10¹⁰ = 10405071317.
//
// Find the last ten digits of the series, 1¹ + 2² + 3³ + ... + 1000¹⁰⁰⁰.
#include <cstdint>
#include <iostream>

// Modulus to get 10 digits.   1234567890
const int64_t mod_10_digits = 10000000000;

// Return the last 10 digits of the self power of n.
//
// \param n: Number for self power (e.g. n^n)
// \return: Last 10 digits of self power.
int64_t last_10_digits_of_self_power(int64_t n)
{
    int64_t last_10_digits = 1;
    for (int i = 1; i <= n; ++i)
    {
        last_10_digits *= n;
        last_10_digits = last_10_digits % mod_10_digits;
    }
    return last_10_digits;
}

int test_last_10_digits_of_self_power()
{
    struct TestCase
    {
        int64_t n;
        int64_t expected;
    };

    TestCase testCases[] = {
        {1, 1},
        {2, 4},
        {3, 27},
        {9, 387420489},
        {10, 0},
        //   0123456789
        {11, 5311670611},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = last_10_digits_of_self_power(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

// Return the sum of last 10 digits of self powers from 1 .. n.
//
// E.g. for n == 10:
//
//  1¹ + 2² + 3³ + ... + 10¹⁰ = 10405071317.
//
// \param n: Last term in sequence of self power numbers.
// \return: Last 10 digits of sum of self powers.
int64_t sum_of_last_10_digits_of_self_powers(int64_t n)
{
    int64_t last_10_digits = 0;
    for (int64_t i = 1; i <= n; ++i)
    {
        last_10_digits += last_10_digits_of_self_power(i);
        last_10_digits = last_10_digits % mod_10_digits;
    }
    return last_10_digits;
}

int test_sum_of_last_10_digits_of_self_powers()
{
    struct TestCase
    {
        int64_t n;
        int64_t expected;
    };

    TestCase testCases[] = {
        {1, 1},
        {2, 5},
        {3, 32},
        {10, 405071317}, // truncated from 10405071317
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = sum_of_last_10_digits_of_self_powers(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    std::cout << sum_of_last_10_digits_of_self_powers(1000) << "\n";

    const int num_fails = test_last_10_digits_of_self_power() + test_sum_of_last_10_digits_of_self_powers();
    return num_fails == 0 ? 0 : 1;
}
