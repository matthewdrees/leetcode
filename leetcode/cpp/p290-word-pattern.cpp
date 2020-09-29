#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    bool wordPattern(std::string pattern, std::string str)
    {
        std::unordered_map<char, std::string> d;
        size_t strIndex = 0;
        for (const char c : pattern) {
            while (str[strIndex] == ' ' && strIndex < str.size()) {
                ++strIndex;
            }
            if (strIndex == str.size()) {
                return false;
            }
            size_t wordEndIndex = strIndex;
            while (str[wordEndIndex] != ' ' && wordEndIndex < str.size()) {
                ++wordEndIndex;
            }
            const std::string word = str.substr(strIndex, wordEndIndex - strIndex);
            strIndex = wordEndIndex;
            const auto it = d.find(c);
            if (it == d.end()) {
                d.insert({ c, word });
            } else if (word != it->second) {
                return false;
            }
        }
        while (str[strIndex] == ' ' && strIndex < str.size()) {
            ++strIndex;
        }
        if (strIndex != str.size()) {
            return false;
        }
        // check to make sure dictionary words are unique.
        std::unordered_set<std::string> word_set;
        for (const auto& pair : d) {
            word_set.insert(pair.second);
        }
        return word_set.size() == d.size();
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::string pattern;
        std::string s;
        bool exp;
    };
    const TestCase testCases[] = {
        { "", "", true },
        { "", " ", true },
        { "", " grr", false },
        { "", "dog cat cat dog", false },
        { "x", "dog", true },
        { "x", "dog cat cat dog", false },
        { "xy", "dog cat", true },
        { "xy", "dog cat cat dog", false },
        { "xx", "dog dog", true },
        { "xx", "dog dog cat cat", false },
        { "abba", "dog cat cat dog", true },
        { "abba", "dog cat cat fish", false },
        { "aaaa", "dog cat cat dog", false },
        { "aaaa", "dog dog dog dog", true },
        { "abba", "dog dog dog dog", false },
        { "aaaa", "dog cat cat dog", false },
        { "jquery", "jquery", false },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const int ans = s.wordPattern(tc.pattern, tc.s);
        if (tc.exp != ans) {
            std::cout << "FAIL. pat: \"" << tc.pattern
                      << "\", str: \"" << tc.s
                      << "\", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
