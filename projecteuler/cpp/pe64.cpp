// Project Euler problem 64. Odd period square roots.
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

struct PeriodicRoot
{
    int a = 1;
    int n = 1;
    int d = 1;
};

constexpr bool operator==(const PeriodicRoot &pr1, const PeriodicRoot &pr2)
{
    return pr1.a == pr2.a && pr1.n == pr2.n && pr1.d == pr2.d;
}

std::string to_string(const PeriodicRoot pr)
{
    std::ostringstream oss;
    oss << "{a: " << pr.a << ", n: " << pr.n << ", d: " << pr.d << "}";
    return oss.str();
}

bool is_square(int n)
{
    const int sr = static_cast<int>(std::sqrt(n));
    return sr * sr == n;
}

PeriodicRoot get_next_periodic_root(int root, PeriodicRoot pr)
{
    PeriodicRoot new_pr;
    new_pr.d = (root - std::pow(pr.n, 2)) / pr.d;
    assert(new_pr.d > 0);

    const int max_n = static_cast<int>(std::sqrt(root));
    new_pr.a = (pr.n + max_n) / new_pr.d;
    new_pr.n = (new_pr.d * new_pr.a) - pr.n;
    return new_pr;
}

int get_period_length(int n)
{
    if (is_square(n))
    {
        return 0;
    }

    PeriodicRoot pr1;
    pr1.a = static_cast<int>(std::sqrt(n));
    pr1.n = pr1.a;
    pr1.d = 1;

    PeriodicRoot pr = get_next_periodic_root(n, pr1);
    const PeriodicRoot pr_loop_start = pr;
    for (int count = 1; count <= n; ++count)
    {
        pr = get_next_periodic_root(n, pr);
        if (pr == pr_loop_start)
        {
            return count;
        }
    }
    assert(false);
}

int pe64()
{
    int num_odd_periods = 0;
    for (int i = 2; i <= 10'000; ++i)
    {
        if (get_period_length(i) % 2 == 1)
        {
            ++num_odd_periods;
        }
    }
    return num_odd_periods;
}

int test_get_next_periodic_root()
{
    struct TestCase
    {
        int root;
        PeriodicRoot pr;
        PeriodicRoot expected;
    };
    TestCase testCases[] = {
        {2, {1, 1, 1}, {2, 1, 1}},
        {3, {1, 1, 1}, {1, 1, 2}},
        {23, {4, 4, 1}, {1, 3, 7}},
        {23, {1, 3, 7}, {3, 3, 2}},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_next_periodic_root(tc.root, tc.pr);
        if (!(tc.expected == actual))
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(root: " << tc.root << ", pr: " << to_string(tc.pr) << ")"
                      << ", expected: " << to_string(tc.expected)
                      << ", actual: " << to_string(actual)
                      << "\n";
        }
    }
    return num_fails;
}

int test_get_period_length()
{
    struct TestCase
    {
        int n;
        int expected;
    };
    TestCase testCases[] = {
        {2, 1},
        {3, 2},
        {4, 0},
        {5, 1},
        {6, 2},
        {7, 4},
        {8, 2},
        {9, 0},
        {10, 1},
        {11, 2},
        {13, 5},
        {23, 4},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_period_length(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int main()
{
    std::cout << pe64() << "\n";
    const int num_fails = test_get_next_periodic_root() + test_get_period_length();
    return num_fails == 0 ? 0 : 1;
}
