#include <iostream>
#include <stack>
#include <unordered_map>

class Solution {
public:
    bool isValid(std::string s)
    {
        std::stack<char> paren_stack;
        std::unordered_map<char, char> paren_map = {
            { '[', ']' },
            { '{', '}' },
            { '(', ')' }
        };
        for (const char c : s) {
            if (paren_map.find(c) != paren_map.end()) {
                paren_stack.push(c);
            } else if (paren_stack.empty()) {
                return false;
            } else {
                const auto it = paren_map.find(paren_stack.top());

                if (it->second != c) {
                    return false;
                }
                paren_stack.pop();
            }
        }
        return paren_stack.empty();
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::string s;
        bool exp;
    };
    const TestCase testCases[] = {
        { "()", true },
        { "()[]{}", true },
        { "(]", false },
        { "([)]", false },
        { "{[]}", true },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const int ans = s.isValid(tc.s);
        if (tc.exp != ans) {
            std::cout << "FAIL. s: " << tc.s
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
