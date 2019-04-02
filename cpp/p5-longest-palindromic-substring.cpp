#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s)
    {
        if (s.empty()) {
            return "";
        }
        int longestPos = 0;
        int longestSize = 1;
        // odd palendrome
        for (int x = 1; x < (int)s.size() - 1; ++x) {
            const int maxY = min(x, (int)s.size() - x - 1) + 1;
            for (int y = 1; y < maxY; ++y) {
                if (s[x - y] != s[x + y]) {
                    break;
                }
                if (2 * y + 1 > longestSize) {
                    longestPos = x - y;
                    longestSize = x + y + 1 - longestPos;
                }
            }
        }
        // even palendrome
        for (int x = 0; x < (int)s.size() - 1; ++x) {
            const int maxY = min(x, (int)s.size() - x - 2) + 1;
            for (int y = 0; y < maxY; ++y) {
                if (s[x - y] != s[x + y + 1]) {
                    break;
                }
                if (2 * (y + 1) > longestSize) {
                    longestPos = x - y;
                    longestSize = x + y + 2 - longestPos;
                }
            }
        }

        return s.substr(longestPos, longestSize);
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        string s;
        string exp;
    };
    const TestCase testCases[] = {
        { "", "" },
        { "bd", "b" },
        { "babad", "bab" },
        { "adbab", "bab" },
        { "cbbd", "bb" },
        { "amanaplanacanalpanama", "amanaplanacanalpanama" },
        { "bbbbba", "bbbbb" },
        { "wwkew", "ww" },
        { "wkeww", "ww" },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.longestPalindrome(tc.s);
        if (tc.exp != ans) {
            cout << "FAIL. num: " << tc.s
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
