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
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = add_consecutive_numbers(tc.first, tc.last);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(first: " << tc.first << ", last: " << tc.last
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
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

    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = get_primes(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: \n"
                      << to_string(tc.expected) << ", actual: \n"
                      << to_string(actual) << "\n";
        }
    }
    return passed;
}

bool test_is_prime()
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

    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = is_prime(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}
int main()
{
    bool passed = true;

    passed = passed && test_add_consecutive_numbers();
    passed = passed && test_get_primes();
    passed = passed && test_is_prime();

    return passed ? 0 : 1;
}
