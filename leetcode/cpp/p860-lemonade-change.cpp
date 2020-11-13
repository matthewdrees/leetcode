/* LeetCode problem 860. Lemonade change.

At a lemonade stand, each lemonade costs $5.

Customers are standing in a queue to buy from you, and order one at a time (in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(const vector<int>& bills)
    {
        int n5s = 0;
        int n10s = 0;

        for (const auto bill : bills) {
            if (bill == 5) {
                n5s += 1;
            } else if (bill == 10) {
                if (n5s > 0) {
                    n10s += 1;
                    n5s -= 1;
                } else {
                    return false;
                }
            } else if (bill == 20) {
                if (n10s > 0 && n5s > 0) {
                    n10s -= 1;
                    n5s -= 1;
                } else if (n5s >= 3) {
                    n5s -= 3;
                } else {
                    return false;
                }
            } else {
                std::cerr << "Bad bill: " << bill << '\n';
                return false;
            }
        }
        return true;
    }
};

static std::string to_string(const std::vector<int>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v) {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

int main()
{
    struct TestCase {
        std::vector<int> bills;
        bool expected;
    };
    TestCase testCases[] = {
        { { 5, 5, 5, 10, 20 }, true },
        { { 10, 10 }, false },
        { { 5, 5, 10, 10, 20 }, false },
    };
    Solution s;
    for (const auto& tc : testCases) {
        const auto actual = s.lemonadeChange(tc.bills);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(bills: " << to_string(tc.expected) << "), expected: \n"
                      << tc.expected << ", actual: \n"
                      << actual << "\n";
        }
    }
}
