#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int reverse(int x)
    {
        int res = 0;
        while (x != 0) {
            if (x < 0 && (INT32_MIN - x % 10) / 10 > res) {
                return 0;
            }
            if (x > 0 && (INT32_MAX - x % 10) / 10 < res) {
                return 0;
            }
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};

// First cut at solution.
class Solution2 {
public:
    int reverse(int x)
    {
        int64_t ret = 0;

        while (true) {
            ret += x % 10;
            x /= 10;
            if (x == 0) {
                break;
            }
            ret *= 10;
        }
        if (ret >= 0) {
            return (ret <= INT32_MAX) ? ret : 0;
        }
        return (ret >= INT32_MIN) ? ret : 0;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        int num;
        int exp;
    };
    const TestCase testCases[] = {
        { 0, 0 },
        { 123, 321 },
        { 1463847412, 2147483641 },
        { 1563847412, 0 },
        { -1463847412, -2147483641 },
        { -1563847412, 0 },
        { -123, -321 },
        { 120, 21 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const int ans = s.reverse(tc.num);
        if (tc.exp != ans) {
            cout << "FAIL. num: " << tc.num
                 << ", ans: " << ans
                 << ", exp: " << tc.exp << "\n";
        }
    }
    return 0;
}
