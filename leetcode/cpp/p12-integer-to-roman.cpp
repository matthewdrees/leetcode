#import <iostream>

class Solution {
public:
    std::string intToRoman(int num)
    {
        struct IntString {
            int i;
            std::string s;
        };
        const IntString intStrings[] = {
            { 1000, "M" },
            { 900, "CM" },
            { 500, "D" },
            { 400, "CD" },
            { 100, "C" },
            { 90, "XC" },
            { 50, "L" },
            { 40, "XL" },
            { 10, "X" },
            { 9, "IX" },
            { 5, "V" },
            { 4, "IV" },
            { 3, "III" },
            { 2, "II" },
            { 1, "I" },
        };

        std::string roman;
        while (num != 0) {
            for (const auto& intString : intStrings) {
                if (num >= intString.i) {
                    roman.append(intString.s);
                    num -= intString.i;
                    break;
                }
            }
        }
        return roman;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        int num;
        std::string exp;
    };
    const TestCase testCases[] = {
        { 1, "I" },
        { 2, "II" },
        { 3, "III" },
        { 4, "IV" },
        { 5, "V" },
        { 6, "VI" },
        { 7, "VII" },
        { 8, "VIII" },
        { 9, "IX" },
        { 10, "X" },
        { 40, "XL" },
        { 50, "L" },
        { 58, "LVIII" },
        { 90, "XC" },
        { 91, "XCI" },
        { 94, "XCIV" },
        { 99, "XCIX" },
        { 100, "C" },
        { 400, "CD" },
        { 500, "D" },
        { 900, "CM" },
        { 1000, "M" },
        { 1994, "MCMXCIV" },
        { 3999, "MMMCMXCIX" },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.intToRoman(tc.num);
        if (tc.exp != ans) {
            std::cout << "FAIL. num: " << tc.num
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
