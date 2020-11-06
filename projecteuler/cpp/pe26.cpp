/*projecteuler.net problem 26. Reciprocal cycles.

A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/
#include <iostream>

// Find the positive integer d that is < n where '1/d' has the longest repeating decimal.
//
// This solution inspired by "grimbal" on https://projecteuler.net/thread=26. Simply brilliant.
int reciprocal_cycles(int n)
{
    int max_cycle_len = 0;
    int max_d = 0;

    for (int d = 2; d < n; ++d)
    {
        int v = 1;
        for (int i = 0; i < d; ++i)
        {
            v = (v * 10) % d;
        }
        const int v0 = v;
        int cycle_len = 0;
        do
        {
            v = (v * 10) % d;
            ++cycle_len;
        } while (v != v0);
        if (cycle_len > max_cycle_len)
        {
            max_d = d;
            max_cycle_len = cycle_len;
        }
    }
    return max_d;
}

int main()
{
    std::cout << reciprocal_cycles(1000) << '\n';
    return 0;
}
