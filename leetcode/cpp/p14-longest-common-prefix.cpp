#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& strs)
    {
        const auto shortest_string_it = std::min_element(strs.begin(),
            strs.end(), [](const auto s1, const auto s2) {
                return s1.size() < s2.size();
            });
        if (shortest_string_it == strs.end()) {
            return "";
        }
        const int end = static_cast<int>(shortest_string_it->size());

        for (int x = 0; x < end; ++x) {
            const char c = strs[0][x];
            for (size_t y = 0; y < strs.size(); ++y) {
                if (strs[y][x] != c) {
                    return strs[y].substr(0, x);
                }
            }
        }
        return strs[0].substr(0, end);
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<std::string> words;
        std::string exp;
    };
    const TestCase testCases[] = {
        { { "flower", "flow", "flight" }, "fl" },
        { { "dog", "racer", "car" }, "" },
        { { "a", "a" }, "a" },
        { { "ab", "ab" }, "ab" },
        { { "a" }, "a" },
        { { "abcd" }, "abcd" },
        { { "" }, "" },
        { {}, "" },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.longestCommonPrefix(tc.words);
        if (tc.exp != ans) {
            std::cout << "FAIL. num words: " << tc.words.size()
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
