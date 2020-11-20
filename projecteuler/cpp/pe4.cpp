/* Project Euler Problem 4. Largest palindrome product.

A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

// Return true if n is a palendrome.
//
// \param n: number to determine if palendrome.
bool is_number_palendrome(int n)
{
    if (n < 0)
    {
        return false;
    }
    std::vector<int8_t> v;
    while (n != 0)
    {
        v.push_back(n % 10);
        n = n / 10;
    }
    const size_t v_mid = v.size() / 2;
    for (size_t i = 0; i < v_mid; ++i)
    {
        if (v[i] != v[v.size() - 1 - i])
        {
            return false;
        }
    }
    return true;
}

// Largest palendromic number when multiplying x-digit numbers.
//
// \param num_digits: Number of digits in numbers to multiply.
//                    (e.g. 1: 1-9, 2: 1-99, 3: 1-999)
// \return: Largest palendromic number.
int largest_palendromic_number_multiplying_x_digits(int num_digits_to_multiply)
{
    if (num_digits_to_multiply <= 0)
    {
        return 0;
    }
    int smallest_x_digit_num = std::pow(10, num_digits_to_multiply - 1);
    int largest_palendrome = 0;

    // work from biggest to smallest
    for (int i = std::pow(10, num_digits_to_multiply) - 1; i > smallest_x_digit_num; --i)
    {
        if (i * i <= largest_palendrome)
        {
            // found it!
            break;
        }
        for (int j = i; j > largest_palendrome / i; --j)
        {
            int num = i * j;
            if (num < largest_palendrome)
            {
                break;
            }
            if (is_number_palendrome(num))
            {
                if (num > largest_palendrome)
                {
                    largest_palendrome = num;
                    break;
                }
            }
        }
    }
    return largest_palendrome;
}

bool test_is_number_palendrome()
{
    struct TestCase
    {
        int n;
        bool expected;
    };
    TestCase testCases[] = {
        {-1, false},
        {0, true},
        {1, true},
        {9, true},
        {10, false},
        {11, true},
        {12, false},
        {121, true},
        {129, false},
        {9009, true},
        {1011, false},
        {1101, false},
        {1111, true},
        {1221, true},
    };

    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = is_number_palendrome(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

bool test_largest_palendromic_number()
{
    struct TestCase
    {
        int n;
        int expected;
    };

    TestCase testCases[] = {
        {1, 9},
        {2, 9009},
        {3, 906609},
    };

    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = largest_palendromic_number_multiplying_x_digits(tc.n);
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
    std::cout << largest_palendromic_number_multiplying_x_digits(3) << '\n';
    return test_is_number_palendrome() &&
                   test_largest_palendromic_number()
               ? 0
               : 1;
}
