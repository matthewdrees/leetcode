// Project Euler problem 33. Digit cancelling fractions.
//
// The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting
// to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by
// cancelling the 9s.
//
// We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
//
// There are exactly four non-trivial examples of this type of fraction, less than one in
// value, and containing two digits in the numerator and denominator.
//
// If the product of these four fractions is given in its lowest common terms, find the
// value of the denominator.
#include <iostream>
#include <utility>

#include <boost/rational.hpp>

// Return a pair of last 2 digits of number.
std::pair<int, int> get_2_digits(int num)
{
    return std::pair<int, int>((num / 10) % 10, num % 10);
}

int main()
{
    boost::rational<int> f(1);
    for (int denominator = 12; denominator < 99; ++denominator)
    {
        const auto d = get_2_digits(denominator);
        if (d.first == d.second || d.second == 0)
        {
            continue;
        }
        for (int numerator = 11; numerator < denominator; ++numerator)
        {
            const auto n = get_2_digits(numerator);
            if (n.first == n.second || n.second == 0)
            {
                continue;
            }
            boost::rational<int> f1(numerator, denominator);
            boost::rational<int> f2(1);
            if (d.first == n.second)
            {
                f2 = boost::rational<int>(n.first, d.second);
            }
            else if (d.second == n.first)
            {
                f2 = boost::rational<int>(n.second, d.first);
            }
            if (f1 == f2)
            {
                // std::cout << "found one: " << numerator << "/" << denominator << " == " << f2.numerator() << "/" << f2.denominator() << '\n';
                f *= f2;
            }
        }
    }

    std::cout << f.denominator() << '\n';
    return 0;
}
