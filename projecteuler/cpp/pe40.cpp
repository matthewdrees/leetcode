// Project Euler problem 40. Champernowne's constant.
//
// An irrational decimal fraction is created by concatenating the positive integers:
//
// 0.123456789101112131415161718192021...
//
// It can be seen that the 12th digit of the fractional part is 1.
//
// If dn represents the nth digit of the fractional part, find the value of the following expression.
//
// d₁ × d₁₀ × d₁₀₀ × d₁₀₀₀ × d₁₀₀₀₀ × d₁₀₀₀₀₀ × d₁₀₀₀₀₀₀
#include <cassert>
#include <iostream>
#include <vector>

static int get_num_digits(int n)
{
    if (n == 0)
    {
        return 1;
    }
    int num_digits = 0;
    while (n != 0)
    {
        n = n / 10;
        ++num_digits;
    }
    return num_digits;
}

int main()
{
    std::vector<int> indexes = {1000000,
                                100000,
                                10000,
                                1000,
                                100};
    int cur_index = 10;
    int product = 1;
    int i = 1;
    for (int x = 1; x < 1000000; ++x)
    {
        const int num_digits = get_num_digits(x);

        if (i + num_digits > cur_index)
        {
            std::cout << "i: " << i
                      << ", x: " << x
                      << ", num_digits: " << num_digits;

            const std::string s = std::to_string(x);
            const int s_index = cur_index - i;
            std::cout << ", s_index: " << s_index;
            assert(s_index >= 0 && s_index < s.size());
            int d = s[s_index] - '0';
            std::cout << ", d[" << cur_index << "] = " << d
                      << '\n';

            product *= d;
            if (indexes.empty())
            {
                break;
            }
            cur_index = indexes.back();
            indexes.pop_back();
        }
        i += num_digits;
    }
    std::cout << product << '\n';
    return 0;
}
