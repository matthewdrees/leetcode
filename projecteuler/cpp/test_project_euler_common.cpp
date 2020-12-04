/* Unit tests for project_euler_common.h. */
#include "project_euler_common.h"

#include <iostream>
#include <sstream>

bool test_add_consecutive_numbers()
{
    struct TestCase
    {
        int first;
        int last;
        int expected;
    };

    TestCase testCases[] = {
        {0, 0, 0},
        {1, 0, 0},

        {0, 1, 1},
        {0, 2, 3},
        {0, 3, 6},
        {0, 4, 10},
        {0, 5, 15},

        {1, 2, 3},
        {1, 5, 15},

        {2, 3, 5},

        {-1, 0, -1},
        {-2, 0, -3},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = add_consecutive_numbers(tc.first, tc.last);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(first: " << tc.first << ", last: " << tc.last
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

static std::string to_string(const std::vector<int> v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v)
    {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

int test_factorial()
{
    int num_fails = 0;
    {
        struct TestCase
        {
            int n;
            int expected;
        };

        TestCase testCases[] = {
            {0, 1},
            {1, 1},
            {2, 2},
            {3, 6},
            {4, 24},
            {5, 120},
            {12, 479001600},
            {13, 0},
        };

        for (const auto &tc : testCases)
        {
            const auto actual = factorial(tc.n);
            if (tc.expected != actual)
            {
                ++num_fails;
                std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                          << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
            }
        }
    }
    {
        struct TestCase
        {
            uint64_t n;
            uint64_t expected;
        };
        TestCase testCases[] = {
            {0, 1},
            {1, 1},
            {2, 2},
            {3, 6},
            {4, 24},
            {5, 120},
            {12, 479001600},
            {13, 6227020800},
            {20, 2432902008176640000},
            {21, 0},
        };

        for (const auto &tc : testCases)
        {
            const auto actual = factorial(tc.n);
            if (tc.expected != actual)
            {
                ++num_fails;
                std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                          << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
            }
        }
    }
    return num_fails;
}

bool test_get_primes()
{
    struct TestCase
    {
        int n;
        std::vector<int> expected;
    };
    TestCase testCases[] = {
        {2, {}},
        {3, {2}},
        {4, {2, 3}},
        {6, {2, 3, 5}},
        {7, {2, 3, 5}},
        {8, {2, 3, 5, 7}},
        {9, {2, 3, 5, 7}},
        {10, {2, 3, 5, 7}},
        {11, {2, 3, 5, 7}},
        {12, {2, 3, 5, 7, 11}},
        {100, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}}};

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_primes(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: \n"
                      << to_string(tc.expected) << ", actual: \n"
                      << to_string(actual) << "\n";
        }
    }
    return num_fails;
}

int test_is_prime()
{
    struct TestCase
    {
        int n;
        bool expected;
    };

    TestCase testCases[] = {
        {1, false},
        {2, true},
        {3, true},
        {4, false},
        {5, true},
        {6, false},
        {7, true},
        {8, false},
        {9, false},
        {10, false}};

    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_prime(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_product_will_fit_type_max_value()
{
    struct TestCase
    {
        int n1;
        int n2;
        bool expected;
    };

    TestCase testCases[] = {
        {0, 0, true},
        {1, 0, true},
        {0, -1, true},
        {306783378, 7, true},
        {306783378, 8, false},
        {std::numeric_limits<int>::max(), 0, true},
        {std::numeric_limits<int>::max(), 1, true},
        {std::numeric_limits<int>::max(), 2, false},
        {0, std::numeric_limits<int>::max(), true},
        {1, std::numeric_limits<int>::max(), true},
        {2, std::numeric_limits<int>::max(), false},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), false},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = product_will_fit_type_max_value(tc.n1, tc.n2);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n1: " << tc.n1 << ", n2: " << tc.n2
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails =
        test_add_consecutive_numbers() +
        test_factorial() +
        test_get_primes() +
        test_is_prime() +
        test_product_will_fit_type_max_value() +
        0;
    return num_fails == 0 ? 0 : 1;
}
