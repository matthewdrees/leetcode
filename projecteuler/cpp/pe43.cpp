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

bool has_interesting_substring_divisibility_property(std::string s)
{
    struct PosDiv
    {
        size_t pos;
        int divisor;
    };
    const PosDiv posDivs[] = {
        {1, 2},
        {2, 3},
        {3, 5},
        {4, 7},
        {5, 11},
        {6, 13},
        {7, 17},
    };
    return std::all_of(std::begin(posDivs), std::end(posDivs), [=](PosDiv pd) {
        return std::stoi(s.substr(pd.pos, 3)) % pd.divisor == 0;
    });
}

// Return the largest pandigital prime
int main()
{
    int64_t total = 0;
    std::string s = std::string("0123456789");
    do
    {
        if (has_interesting_substring_divisibility_property(s))
        {
            total += std::stoll(s);
        }
    } while (std::next_permutation(s.begin(), s.end()));
    std::cout << total << '\n';
    return 0;
}
