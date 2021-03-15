// Project Euler problem 63. Powerful digit counts.
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

int num_digits(boost::multiprecision::cpp_int ci)
{
    int count = 0;
    while (ci != 0)
    {
        ++count;
        ci /= 10;
    }
    return count;
}

int pe63()
{
    int powerful_digit_count = 0;
    for (unsigned exp = 1; exp < 100; ++exp)
    {
        bool found_one = false;
        for (boost::multiprecision::cpp_int base = 9; base > 0; --base)
        {
            boost::multiprecision::cpp_int n = boost::multiprecision::pow(base, exp);
            if (num_digits(n) == exp)
            {
                found_one = true;
                ++powerful_digit_count;
            }
            else
            {
                break;
            }
        }
        if (!found_one)
        {
            return powerful_digit_count;
        }
    }
    return 0;
}

int main()
{
    std::cout << pe63() << "\n";
    return 0;
}
