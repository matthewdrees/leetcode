// LeetCode 22. Generate parentheses.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

bool has_valid_parens(std::string s)
{
    int i = 0;
    for (const char c : s) {
        if (c == '(') {
            ++i;
        } else if (c == ')') {
            --i;
            if (i < 0) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> v;
        if (n <= 0) {
            return v;
        }
        if (n == 1) {
            v.push_back("()");
            return v;
        }
        std::ostringstream oss;
        for (size_t i = 0; i++ < n;) {
            oss << "(";
        }
        for (size_t i = 0; i++ < n;) {
            oss << ")";
        }
        std::string s = oss.str();
        size_t count = 0;
        do {
            if (has_valid_parens(s)) {
                v.push_back(s);
            }
        } while (std::next_permutation(s.begin() + 1, s.end() - 1));
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        return v;
    }
};

int main()
{
    Solution solution;
    for (int i = 1; i <= 8; ++i) {
        const auto v = solution.generateParenthesis(i);
        //for (const auto s : v) {
        //    std::cout << s << "\n";
        // }
        std::cout << "size: " << v.size() << "\n";
    }

    return 0;
}
