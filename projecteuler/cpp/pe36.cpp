// Project Euler problem 36. Double-base palindromes.
//
// The decimal number, 585 = 1001001001₂ (binary), is palindromic in both bases.
//
// Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
//
// (Please note that the palindromic number, in either base, may not include leading zeros.)
#include <cassert>
#include <iostream>
#include <vector>

// Return true if n is a palendrome.
//
// \param n: number to check for palendrome.
// \param base: base of number to check for.
// \return: True if is a palendrome.
bool is_palendrome(int n, int base = 10)
{
    // Notes:
    // 1. It's possible to have a base 1 number (counting with line scratches). YAGNI.
    // 2. Deal with base 16 if it ever comes up (substitute in letters for 10 - 15).
    assert(base >= 2 && base <= 10);

    std::vector<int> v;
    while (n != 0)
    {
        v.push_back(n % base);
        n /= base;
    }
    for (int x = 0, y = static_cast<int>(v.size() - 1); x < y; ++x, --y)
    {
        if (v[x] != v[y])
        {
            return false;
        }
    }
    return true;
}

int test_is_palendrome()
{
    struct TestCase
    {
        int n;
        int base;
        bool expected;
    };
    TestCase testCases[] = {
        {0, 10, true},
        {1, 10, true},
        {9, 10, true},
        {10, 10, false},
        {11, 10, true},
        {12, 10, false},
        {121, 10, true},
        {921, 10, false},
        {9009, 10, true},
        {1011, 10, false},
        {1101, 10, false},
        {0, 2, true},
        {1, 2, true},
        {2, 2, false},
        {3, 2, true},
        {4, 2, false},
        {5, 2, true},
        {6, 2, false},
        {7, 2, true},
        {8, 2, false},
        {9, 2, true},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_palendrome(tc.n, tc.base);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << ", base: " << tc.base
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

// Return the sum of all numbers, less than n, which are palendromic in base 10 and 2.
//
// \param n: Consider all numbers 1 to n (not inclusive).
// \return: Sum of all double-base palendromic numbers.
int sum_double_base_palindromes_under_n(int n)
{
    int total = 0;
    for (int i = 1; i < n; ++i)
    {
        if (is_palendrome(i) && is_palendrome(i, 2))
        {
            total += i;
        }
    }
    return total;
}

int test_sum_double_base_palindromes_under_n()
{
    struct TestCase
    {
        int n;
        int expected;
    };
    TestCase testCases[] = {
        {0, 0},
        {1, 0},
        {2, 1},
        {3, 1},
        {4, 4},
        {5, 4},
        {6, 9},
        {7, 9},
        {8, 16},
        {9, 16},
        {10, 25},
        {11, 25},
        {12, 25},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = sum_double_base_palindromes_under_n(tc.n);
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
    std::cout << sum_double_base_palindromes_under_n(1000000) << '\n';

    const int num_fails = test_is_palendrome() + test_sum_double_base_palindromes_under_n();
    return num_fails == 0 ? 0 : 1;
}
