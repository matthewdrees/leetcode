#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.empty()) {
            return 0;
        }
        int longest = 1;
        auto c1 = s.begin();
        auto c2 = c1 + 1;
        while (c2 != s.end()) {
            if (find(c1, c2, *c2) == c2) {
                ++c2;
                longest = std::max(longest, (int)std::distance(c1, c2));
            } else {
                ++c1;
            }
        }
        return longest;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s)
    {
        int longest = 0;
        deque<char> chars;
        for (const char c : s) {
            while (find(chars.begin(), chars.end(), c) != chars.end()) {
                chars.pop_back();
            }
            chars.push_front(c);
            longest = std::max(longest, (int)chars.size());
        }
        return longest;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        string s;
        int exp;
    };
    const TestCase testCases[] = {
        { "", 0 },
        { "a", 1 },
        { "abcabcbb", 3 },
        { "bbbbb", 1 },
        { "pwwkew", 3 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const int ans = s.lengthOfLongestSubstring(tc.s);
        if (tc.exp != ans) {
            cout << "FAIL. s: " << tc.s
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
