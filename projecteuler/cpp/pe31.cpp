/* Project Euler 31. Coin sums.

In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
*/
#include <iostream>

// Returns number of possible coin combinations to make amount.
//
// \param amount: Amount of money for calculation.
// \return: Number of combinations of coins to make amount.
int coin_sums(int amount)
{
    int total_coins = 0;

    for (int a = 0; a <= amount; a += 200)
    {
        for (int b = a; b <= amount; b += 100)
        {
            for (int c = b; c <= amount; c += 50)
            {
                for (int d = c; d <= amount; d += 20)
                {
                    for (int e = d; e <= amount; e += 10)
                    {
                        for (int f = e; f <= amount; f += 5)
                        {
                            for (int g = f; g <= amount; g += 2)
                            {
                                total_coins += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return total_coins;
}

bool test_coin_sums()
{
    struct TestCase
    {
        int n;
        int expected;
    };

    TestCase testCases[] = {
        {1, 1},
        {2, 2},
        {3, 2},
        {4, 3},
        {5, 4},
        {6, 5},
        {7, 6},
        {8, 7},
        {10, 11},
        {20, 41},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = coin_sums(tc.n);
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
    std::cout << coin_sums(200) << '\n';

    return test_coin_sums() ? 0 : 1;
}
