#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices)
    {
        int curLo = INT32_MAX;
        int maxProfit = 0;
        for (const int price : prices) {
            if (curLo > price) {
                curLo = price;
            } else {
                const int profit = price - curLo;
                if (maxProfit < profit) {
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        vector<int> prices;
        int exp;
    };
    const TestCase testCases[] = {
        { {}, 0 },
        { { 7 }, 0 },
        { { 1, 2 }, 1 },
        { { 1, 4, 2 }, 3 },
        { { 7, 1, 5, 3, 6, 4 }, 5 },
        { { 7, 6, 4, 3, 1 }, 0 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.maxProfit(tc.prices);
        if (tc.exp != ans) {
            cout << "FAIL. prices: "
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
