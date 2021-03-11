// A googol (10100) is a massive number: one followed by one-hundred zeros;
// 100^100 is almost unimaginably large: one followed by two-hundred zeros.
// Despite their size, the sum of the digits in each number is only 1.
//
// Considering natural numbers of the form, ab, where a, b < 100, what is the
// maximum digital sum?
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

int main()
{
    int max_sum = 0;
    for (int a = 79; a < 100; ++a)
    {
        for (int b = 79; b < 100; ++b)
        {
            const boost::multiprecision::cpp_int ci_a = a;
            boost::multiprecision::cpp_int ans = boost::multiprecision::pow(ci_a, b);
            int sum = 0;
            while (ans != 0)
            {
                sum += static_cast<int>(ans % 10);
                ans /= 10;
            }
            if (sum > max_sum)
            {
                max_sum = sum;
            }
        }
    }
    std::cout << max_sum << "\n";
    return 0;
}
