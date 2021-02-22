// Project Euler 52. Permuted multiples.
//
// It can be seen that the number, 125874, and its double, 251748, contain exactly
// the same digits, but in a different order.
//
// Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
// contain the same digits.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

// Get the unique digits in n.
//
// Return the digits highest to lowest (otherwise you lose any zeros).
//
// \param n: Number to find unique digits.
// \return: Integer containing unique digits, sorted highest to lowest.
int get_unique_digits(int n)
{
    std::vector<int8_t> v;
    while (n != 0)
    {
        v.push_back(n % 10);
        n /= 10;
    }
    std::sort(v.begin(), v.end());
    const auto last = std::unique(v.begin(), v.end());
    return std::accumulate(
        std::make_reverse_iterator(last), v.rend(), 0, [](auto i1, auto i2) {
            return i1 * 10 + i2;
        });
}

// Return true if n is a permuted multiple up to biggest_multiple
//
// \param n: Number to test for permuted multiple.
// \param biggest_multiple: Largest multiple to test for.
// \return: True if is permuted multiple.
bool is_permuted_multiple(int n, int biggest_multiple)
{
    const int unique_digits = get_unique_digits(n);
    for (int mult = 2; mult <= biggest_multiple; ++mult)
    {
        if (unique_digits != get_unique_digits(n * mult))
        {
            return false;
        }
    }
    return true;
}

int pe52()
{
    // A sieve with pre-calculated sorted digits would probably be faster,
    // but this was fast enough.
    const int BIGGEST_MULTIPLE = 6;
    const int I_MAX = std::numeric_limits<int>::max() / BIGGEST_MULTIPLE;
    for (int i = 1; i < I_MAX; ++i)
    {
        if (is_permuted_multiple(i, BIGGEST_MULTIPLE))
        {
            return i;
        }
    }
    return 0;
}

int main()
{
    std::cout << pe52() << '\n';
    return 0;
}
