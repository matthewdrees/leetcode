#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x)
    {
        if (x < 0) {
            return false;
        }
        int nums[11];
        int index = 0;
        while (x != 0) {
            nums[index++] = x % 10;
            x = x / 10;
        }
        for (int y = 0; y < index / 2; ++y) {
            if (nums[y] != nums[index - 1 - y]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        int num;
        bool exp;
    };
    const TestCase testCases[] = {
        { 121, true },
        { 1221, true },
        { 2147483647, false },
        { 2147447412, true },
        { 214747412, true },
        { 0, true },
        { 9, true },
        { 10, false },
        { -121, false },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.isPalindrome(tc.num);
        if (tc.exp != ans) {
            cout << "FAIL. num: " << tc.num
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
