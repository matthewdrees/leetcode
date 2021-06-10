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

int test_for_each_n()
{
    struct TestCase
    {
        std::vector<int> v;
        int n;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, 0, {}},
        {{0}, 1, {1}},
        {{1}, 1, {2}},
        {{1}, 0, {1}},
        {{2}, 1, {3}},
        {{1, 2}, 0, {1, 2}},
        {{1, 2}, 1, {2, 2}},
        {{1, 2}, 2, {2, 3}},
        {{1, 2, 3}, 0, {1, 2, 3}},
        {{1, 2, 3}, 1, {2, 2, 3}},
        {{1, 2, 3}, 2, {2, 3, 3}},
        {{1, 2, 3}, 3, {2, 3, 4}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto v = tc.v;
        for_each_n(v.begin(), tc.n, [](int &i)
                   { i += 1; });
        if (tc.expected != v)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ", n: " << tc.n << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(v)
                      << "\n";
        }
    }
    return num_fails;
}

int test_count()
{
    struct TestCase
    {
        std::vector<int> v;
        int n;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0, 0},
        {{0}, 1, 0},
        {{1}, 1, 1},
        {{1, 2}, 0, 0},
        {{1, 2}, 1, 1},
        {{1, 2}, 2, 1},
        {{1, 1}, 2, 0},
        {{1, 1}, 1, 2},
        {{1, 2, 3}, 0, 0},
        {{1, 2, 3}, 1, 1},
        {{1, 2, 3}, 2, 1},
        {{1, 2, 3}, 3, 1},
        {{1, 2, 3}, 4, 0},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto actual = count(tc.v.begin(), tc.v.end(), tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ", n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_count_if()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{0}, 1},
        {{1}, 0},
        {{0, 0}, 2},
        {{1, 0}, 1},
        {{0, 1}, 1},
        {{1, 1}, 0},
        {{1, 1, 3}, 0},
        {{1, 2, 3}, 1},
        {{2, 4, 3}, 2},
        {{2, 4, 6}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto actual = count_if(tc.v.begin(), tc.v.end(), [](int i)
                               { return i % 2 == 0; });
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

int test_mismatch1()
{
    struct TestCase
    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, {}, 0},
        {{0}, {0}, 1},
        {{0}, {1}, 0},
        {{1}, {0}, 0},
        {{1, 2}, {1, 2}, 2},
        {{1, 3}, {1, 2}, 1},
        {{1, 2, 3}, {1, 2, 3}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto p = mismatch1(tc.v1.begin(), tc.v1.end(), tc.v2.begin());
        const auto actual1 = std::distance(tc.v1.begin(), p.first);
        const auto actual2 = std::distance(tc.v2.begin(), p.second);

        if (tc.expected != actual1 || tc.expected != actual2)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v1: " << vec_to_string(tc.v1)
                      << ", v2: " << vec_to_string(tc.v2) << ")"
                      << ", expected: " << tc.expected
                      << ", actual1: " << actual1
                      << ", actual2: " << actual2
                      << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_all_of() +
                          test_any_of() +
                          test_none_of() +
                          test_for_each() +
                          test_for_each_n() +
                          test_count() +
                          test_count_if() +
                          test_mismatch1();
    return num_fails == 0 ? 0 : 1;
}
