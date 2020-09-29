#include <cstdint>
#include <iostream>

class Solution {
public:
    int myAtoi(std::string str)
    {
        size_t i = 0; // Index of str.

        // Skip leading whitespace.
        for (; i < str.size(); ++i) {
            if (str[i] != ' ') {
                break;
            }
        }

        // Track optional +/- prefix.
        bool isPositive = true;
        if (i < str.size()) {
            if (str[i] == '-') {
                isPositive = false;
                ++i;
            } else if (str[i] == '+') {
                ++i;
            }
        }

        // Read in the number. Cap it to a 32 bit signed integer.
        int64_t n = 0; // Number to return
        if (isPositive) {
            for (; i < str.size(); ++i) {
                if (str[i] < '0' || '9' < str[i]) {
                    break;
                }
                const int x = str[i] - '0';
                n *= 10;
                n += x;
                if (n > INT32_MAX) {
                    return INT32_MAX;
                }
            }
        } else {
            // number is negative
            for (; i < str.size(); ++i) {
                if (str[i] < '0' || '9' < str[i]) {
                    break;
                }
                const int x = str[i] - '0';
                n *= 10;
                n -= x;
                if (n < INT32_MIN) {
                    return INT32_MIN;
                }
            }
        }
        return static_cast<int32_t>(n);
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::string str;
        int exp;
    };
    const TestCase testCases[] = {
        { "", 0 },
        { " ", 0 },
        { " -", 0 },
        { " +", 0 },
        { "42", 42 },
        { "   -42", -42 },
        { "+42", 42 },
        { "4193 with words", 4193 },
        { "words and 987", 0 },
        { "-91283472332", -2147483648 },
        { "-2147483648", -2147483648 },
        { "2147483648", 2147483647 },
        { "2147483647", 2147483647 },
        { "0", 0 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.myAtoi(tc.str);
        if (tc.exp != ans) {
            std::cout << "FAIL. str: " << tc.str
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
