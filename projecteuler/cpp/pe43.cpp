// Project Euler problem 43. Sub-string divisibility.
//
// The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the
// digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
//
// Let d₁ be the 1st digit, d₂ be the 2nd digit, and so on. In this way, we note the following:
//
// d₂d₃d₄=406 is divisible by 2
// d₃d₄d₅=063 is divisible by 3
// d₄d₅d₆=635 is divisible by 5
// d₅d₆d₇=357 is divisible by 7
// d₆d₇d₈=572 is divisible by 11
// d₇d₈d₉=728 is divisible by 13
// d₈d₉d₁₀=289 is divisible by 17
//
// Find the sum of all 0 to 9 pandigital numbers with this property.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

bool has_interesting_substring_divisibility_property(const std::vector<int8_t> &v)
{
    // Optimization for divisors = 2 or 5.
    if (v[3] % 2 != 0 || v[5] % 5 != 0)
    {
        return false;
    }
    struct PosDiv
    {
        size_t pos;
        int divisor;
    };
    const PosDiv posDivs[] = {
        // {1, 2}, See optimization above.
        {2, 3},
        // {3, 5}, See optimization above.
        {4, 7},
        {5, 11},
        {6, 13},
        {7, 17},
    };
    return std::all_of(std::begin(posDivs), std::end(posDivs), [&](PosDiv pd) {
        int total = 0;
        for (int i = pd.pos; i < pd.pos + 3; ++i)
        {
            total = total * 10 + v[i];
        }
        return total % pd.divisor == 0;
    });
}

int64_t get_int64_from_digits(const std::vector<int8_t> &v)
{
    int64_t total = 0;
    for (auto d : v)
    {
        total = total * 10 + d;
    }
    return total;
}

int main()
{
    int64_t total = 0;
    std::vector<int8_t> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    do
    {
        if (has_interesting_substring_divisibility_property(v))
        {
            total += get_int64_from_digits(v);
        }
    } while (std::next_permutation(v.begin(), v.end()));
    std::cout << total << '\n';
    return 0;
}
