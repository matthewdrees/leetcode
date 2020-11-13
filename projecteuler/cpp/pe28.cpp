/* projecteuler.net problem 28. Number spiral diagonals.

Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

    21 22 23 24 25
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/
#include <cassert>
#include <iostream>

// Get the sum of the numbers on the diagonals with n x n spiral.
//
// Note, only handles the case where n is odd.
//
// \param n: dimension of the spiral.
// \return: sum of the numbers on the diagonals.
int number_spiral_diagonals(int n)
{
    assert(n % 2 != 0);

    int cur_num = 1;
    int total = 1;
    for (int i = 2; i < n; i += 2)
    {
        for (int j = 0; j < 4; ++j)
        {
            cur_num += i;
            total += cur_num;
        }
    }
    return total;
}

bool test_number_spiral_diagonals()
{
    struct TestCase
    {
        int n;
        int expected;
    };

    TestCase testCases[] = {
        {1, 1},
        {3, 25},
        {5, 101},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = number_spiral_diagonals(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

int main()
{
    std::cout << number_spiral_diagonals(1001) << '\n';

    return test_number_spiral_diagonals() ? 0 : 1;
}
