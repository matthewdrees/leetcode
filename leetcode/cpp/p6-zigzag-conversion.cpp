#include <iostream>
#include <string>

class Solution {
public:
    std::string convert(std::string s, int numRows)
    {
        if (numRows >= static_cast<int>(s.size()) || numRows < 2) {
            return s;
        }
        std::string ret;
        const int biggestGap = (numRows - 1) * 2;

        // Handle first row
        for (int x = 0; x < static_cast<int>(s.size()); x += biggestGap) {
            ret += s[x];
        }

        // Middle rows alternate gaps.
        int nextGap = biggestGap - 2;
        for (int numRow = 1; numRow < numRows - 1; ++numRow) {
            int x = numRow;
            int gap = nextGap;
            while (x < static_cast<int>(s.size())) {
                ret += s[x];
                x += gap;
                gap = biggestGap - gap;
            }
            nextGap -= 2;
        }
        // Handle last row
        for (int x = numRows - 1; x < static_cast<int>(s.size()); x += biggestGap) {
            ret += s[x];
        }
        return ret;
    }
};

int main(int /*argc*/, char* /*argv*/ [])
{
    struct TestCase {
        std::string s;
        int numRows;
        std::string exp;
    };
    const TestCase testCases[] = {
        { "", 0, "" },
        { "", 1, "" },
        { "a", 1, "a" },
        { "ab", 1, "ab" },
        { "a", 2, "a" },
        { "ab", 2, "ab" },
        { "abc", 2, "acb" },
        { "abcd", 2, "acbd" },
        { "abcde", 2, "acebd" },
        { "a", 3, "a" },
        { "ab", 3, "ab" },
        { "abc", 3, "abc" },
        { "abcd", 3, "abdc" },
        { "abcde", 3, "aebdc" },
        { "abcdef", 3, "aebdfc" },
        { "a", 4, "a" },
        { "ab", 4, "ab" },
        { "abc", 4, "abc" },
        { "abcd", 4, "abcd" },
        { "abcde", 4, "abced" },
        { "abcdef", 4, "abfced" },
        { "abcdefg", 4, "agbfced" },
        { "PAYPALISHIRING", 3, "PAHNAPLSIIGYIR" },
        { "PAYPALISHIRING", 4, "PINALSIGYAHRPI" },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.convert(tc.s, tc.numRows);
        if (tc.exp != ans) {
            std::cout << "FAIL. s: " << tc.s
                      << ", numRows: " << tc.numRows
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
