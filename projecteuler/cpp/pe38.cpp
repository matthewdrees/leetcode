// Project Euler problem 38. Pandigital multiples.
//
// Take the number 192 and multiply it by each of 1, 2, and 3:
//
//     192 × 1 = 192
//     192 × 2 = 384
//     192 × 3 = 576
//
// By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call
// 192384576 the concatenated product of 192 and (1,2,3)
//
// The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving
// the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
//
// What is the largest 1 to 9 pandigital 9-digit number that can be formed as the
// concatenated product of an integer with (1,2, ... , n) where n > 1?
#include <cstdlib>
#include <iostream>

int get_pandigit(int i)
{
    std::string s;
    for (int n = 1; n < 10; ++n)
    {
        s = s + std::to_string(i * n);
        if (s.size() >= 9)
        {
            return std::stoi(s);
        }
    }
    return 0;
}

bool is_pandigit_multiple(int i)
{
    bool nums[10] = {true, false};
    int count = 0;
    for (int n = 1; n < 10; ++n)
    {
        int product = i * n;
        while (product != 0)
        {
            ++count;
            int digit = product % 10;
            if (nums[digit])
            {
                return false;
            }
            nums[digit] = true;
            product /= 10;
        }
        if (count == 9)
        {
            return true;
        }
        if (count > 9)
        {
            return false;
        }
    }
    return false;
}

int main()
{
    int largest = 0;
    for (int i = 12; i < 10000; ++i)
    {
        if (is_pandigit_multiple(i))
        {
            int pandigit_number = get_pandigit(i);
            // std::cout << "Found one, i: " << i << ", pan: " << pandigit_number << '\n';
            if (pandigit_number > largest)
            {
                largest = pandigit_number;
            }
        }
    }
    std::cout << largest << '\n';
    return 0;
}
