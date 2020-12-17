// Project Euler problem 30. Digit fifth powers.
// Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
//
//     1634 = 1⁴ + 6⁴ + 3⁴ + 4⁴
//     8208 = 8⁴ + 2⁴ + 0⁴ + 8⁴
//     9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴
//
// As 1 = 1⁴ is not a sum it is not included.
//
// The sum of these numbers is 1634 + 8208 + 9474 = 19316.
//
// Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
#include <cmath>
#include <iostream>

int digit_x_power(int power)
{
    int total = 0;
    const int x_max = std::pow(10, power + 1);
    for (int x = 2; x < x_max; ++x)
    {
        int sum = 0;
        int y = x;
        while (y != 0)
        {
            sum += std::pow(y % 10, power);
            y /= 10;
        }
        if (sum == x)
        {
            total += sum;
        }
    }
    return total;
}

int main()
{
    std::cout << digit_x_power(5) << '\n';
    return 0;
}
