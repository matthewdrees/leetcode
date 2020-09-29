#include <algorithm>
#include <iostream>

class Solution {
public:
    std::string reverseVowels(std::string s)
    {
        if (s.empty()) {
            return s;
        }
        const std::string vowels = "AEIOUaeiou";
        size_t i1 = 0;
        size_t i2 = s.size() - 1;
        while (i1 < i2) {
            while (!std::binary_search(vowels.begin(), vowels.end(), s[i1])) {
                ++i1;
                if (i1 >= i2) {
                    return s;
                }
            }
            while (!std::binary_search(vowels.begin(), vowels.end(), s[i2])) {
                --i2;
                if (i1 >= i2) {
                    return s;
                }
            }
            std::swap(s[i1], s[i2]);
            ++i1;
            --i2;
        }
        return s;
    }
};

struct TestCase {
    std::string s;
    std::string exp;
};

int main(int /*argc*/, char* /*argv*/ [])
{
    TestCase testCases[] = {
        { "hello", "holle" },
        { "leetcode", "leotcede" },
        { "HELLO", "HOLLE" },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto act = s.reverseVowels(tc.s);
        if (tc.exp != act) {
            std::cerr << "FAIL. "
                      << tc.exp << " != " << act << '\n';
        }
    }
    return 0;
}
