// If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
//
// Not all numbers produce palindromes so quickly. For example,
//
//     349 + 943 = 1292,
//     1292 + 2921 = 4213
//     4213 + 3124 = 7337
//
// That is, 349 took three iterations to arrive at a palindrome.
//
// Although no one has proved it yet, it is thought that some numbers, like 196,
// never produce a palindrome. A number that never forms a palindrome through
// the reverse and add process is called a Lychrel number. Due to the theoretical
// nature of these numbers, and for the purpose of this problem, we shall assume
// that a number is Lychrel until proven otherwise. In addition you are given
// that for every number below ten-thousand, it will either (i) become a
// palindrome in less than fifty iterations, or, (ii) no one, with all the
// computing power that exists, has managed so far to map it to a palindrome. In
// fact, 10677 is the first number to be shown to require over fifty iterations
// before producing a palindrome: 4668731596684224866951378664 (53 iterations,
// 28-digits).
//
// Surprisingly, there are palindromic numbers that are themselves Lychrel
// numbers; the first example is 4994.
//
// How many Lychrel numbers are there below ten-thousand?
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using BigNum = std::vector<int8_t>;

std::string bn_to_string(const BigNum &v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v)
    {
        oss << static_cast<int16_t>(i) << ',';
    }
    oss << "\b}";
    return oss.str();
}

BigNum get_bignum(int n)
{
    BigNum bn;
    while (n != 0)
    {
        bn.push_back(n % 10);
        n = n / 10;
    }
    return bn;
}

BigNum reverse_add(BigNum bn)
{
    BigNum ans;
    if (bn.empty())
    {
        return ans;
    }
    int8_t carry = 0;
    for (size_t i = 0; i < bn.size(); ++i)
    {
        int8_t temp = bn[i] + bn[bn.size() - i - 1] + carry;
        ans.push_back(temp % 10);
        carry = temp / 10;
    }
    if (carry != 0)
    {
        assert(carry < 10);
        ans.push_back(carry);
    }
    return ans;
}

bool is_palendrome(const BigNum &bn)
{
    if (bn.empty())
    {
        return false;
    }
    size_t first_index = 0;
    size_t last_index = bn.size() - 1;
    for (; first_index < last_index; ++first_index, --last_index)
    {
        if (bn[first_index] != bn[last_index])
        {
            return false;
        }
    }
    return true;
}

bool is_lychrel(int n)
{
    BigNum bn = get_bignum(n);
    // Try for a certain number of iterations, then give up.
    for (int _ = 0; _ < 50; ++_)
    {
        BigNum bn2 = reverse_add(bn);
        if (is_palendrome(bn2))
        {
            return false;
        }
        bn = std::move(bn2);
    }
    return true;
}

int test_reverse_add()
{
    struct TestCase
    {
        BigNum bn;
        BigNum expected;
    };
    TestCase testCases[] = {
        {{1}, {2}},
        {{4, 7}, {1, 2, 1}},
        {{9, 4, 3}, {2, 9, 2, 1}},
        {{4, 9, 9, 4}, {8, 8, 9, 9}},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = reverse_add(tc.bn);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(bn: " << bn_to_string(tc.bn) << ")"
                      << ", expected: " << bn_to_string(tc.expected)
                      << ", actual: " << bn_to_string(actual) << "\n";
        }
    }
    return num_fails;
}

int test_is_palendrome()
{
    struct TestCase
    {
        BigNum bn;
        bool expected;
    };
    TestCase testCases[] = {
        {{}, false},
        {{0}, true},
        {{1}, true},
        {{0, 1}, false},
        {{2, 2}, true},
        {{2, 1}, false},
        {{3, 2, 2}, false},
        {{1, 1, 2}, false},
        {{1, 2, 1}, true},
        {{1, 2, 1, 2}, false},
        {{1, 2, 2, 1}, true},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_palendrome(tc.bn);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(bn: " << bn_to_string(tc.bn) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int test_is_lychrel()
{
    struct TestCase
    {
        int n;
        bool expected;
    };
    TestCase testCases[] = {
        {1, false},
        {47, false},
        {196, true},
        {4994, true},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_lychrel(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    int num_lychrels = 0;
    for (int i = 1; i < 10'000; ++i)
    {
        if (is_lychrel(i))
        {
            ++num_lychrels;
        }
    }
    std::cout << num_lychrels << "\n";

    const int num_fails = test_reverse_add() + test_is_palendrome() + test_is_lychrel();
    return num_fails == 0 ? 0 : 1;
}
