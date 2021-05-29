#include "mystl/algorithm.hpp"

#include <iostream>
#include <sstream>
#include <vector>

template <class T>
std::string vec_to_string(const std::vector<T> v)
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

int test_all_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, true},
        {{1}, true},
        {{2}, false},
        {{1, 2}, false},
        {{2, 1}, false},
        {{1, 1}, true},
        {{1, 2, 3}, false},
        {{1, 1, 1}, true},
        {{1, 1, 1, 2}, false},
        {{2, 1, 1, 1}, false},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = all_of(tc.v.begin(), tc.v.end(), [](int i)
                                   { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_any_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, false},
        {{1}, true},
        {{2}, false},
        {{1, 2}, true},
        {{2, 1}, true},
        {{1, 1}, true},
        {{2, 2}, false},
        {{1, 2, 3}, true},
        {{1, 1, 1}, true},
        {{2, 3, 0}, false},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = any_of(tc.v.begin(), tc.v.end(), [](int i)
                                   { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_none_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, true},
        {{1}, false},
        {{2}, true},
        {{1, 2}, false},
        {{2, 1}, false},
        {{1, 1}, false},
        {{2, 2}, true},
        {{1, 2, 3}, false},
        {{1, 1, 1}, false},
        {{2, 3, 0}, true},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = none_of(tc.v.begin(), tc.v.end(), [](int i)
                                    { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_for_each()
{
    struct TestCase
    {
        std::vector<int> v;
        int expected;
    };
    struct Sum
    {
        void operator()(int i) { sum += i; }
        int sum{0};
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{0}, 0},
        {{1}, 1},
        {{2}, 2},
        {{1, 2}, 3},
        {{1, 2, 3}, 6},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        Sum s;
        const auto actual = for_each(tc.v.begin(), tc.v.end(), s);
        if (tc.expected != actual.sum)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual.sum
                      << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_all_of() + test_any_of() + test_none_of() + test_for_each();
    return num_fails == 0 ? 0 : 1;
}
