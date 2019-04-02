#import <iostream>

using namespace std;

class Solution {
public:
    int romanToInt(string s)
    {
        int total = 0;
        for (int x = 0; x < (int)s.size(); ++x) {
            const char c = s[x];
            const char nextC = x + 1 < (int)s.size() ? s[x + 1] : '\0';
            switch (c) {
            case 'I':
                switch (nextC) {
                case 'V':
                    total += 4;
                    x += 1;
                    break;
                case 'X':
                    total += 9;
                    x += 1;
                    break;
                default:
                    total += 1;
                    break;
                }
                break;
            case 'V':
                total += 5;
                break;
            case 'X':
                switch (nextC) {
                case 'L':
                    total += 40;
                    x += 1;
                    break;
                case 'C':
                    total += 90;
                    x += 1;
                    break;
                default:
                    total += 10;
                    break;
                }
                break;
            case 'L':
                total += 50;
                break;
            case 'C':
                switch (nextC) {
                case 'D':
                    total += 400;
                    x += 1;
                    break;
                case 'M':
                    total += 900;
                    x += 1;
                    break;
                default:
                    total += 100;
                    break;
                }
                break;
            case 'D':
                total += 500;
                break;
            case 'M':
                total += 1000;
                break;
            }
        }
        return total;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        string roman;
        int exp;
    };
    const TestCase testCases[] = {
        { "I", 1 },
        { "II", 2 },
        { "III", 3 },
        { "IV", 4 },
        { "V", 5 },
        { "VI", 6 },
        { "VII", 7 },
        { "VIII", 8 },
        { "IX", 9 },
        { "X", 10 },
        { "XL", 40 },
        { "L", 50 },
        { "LVIII", 58 },
        { "XC", 90 },
        { "C", 100 },
        { "CD", 400 },
        { "D", 500 },
        { "CM", 900 },
        { "M", 1000 },
        { "MCMXCIV", 1994 },
        { "MMMCMXCIX", 3999 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.romanToInt(tc.roman);
        if (tc.exp != ans) {
            cout << "FAIL. prices: "
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
