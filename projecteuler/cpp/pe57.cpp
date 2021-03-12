// Project Euler problem 57. Square root convergents.
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

bool add_one_and_check(boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int d)
{
    n = n + d;
    return num_digits(n) > num_digits(d);
}

int main()
{
    int count = 0;
    boost::multiprecision::cpp_int n = 1;
    boost::multiprecision::cpp_int d = 2;
    for (int _ = 1; _ < 1000; ++_)
    {
        n += d * 2;
        std::swap(n, d);
        if (add_one_and_check(n, d))
        {
            ++count;
        }
    }
    std::cout << count << "\n";
    return 0;
}
