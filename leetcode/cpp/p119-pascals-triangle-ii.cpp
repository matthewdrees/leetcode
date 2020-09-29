#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> getRow(int rowIndex)
    {
        if (rowIndex == 0) {
            return { 1 };
        }
        std::vector<int> v = { 1, 1 };
        for (int i = 1; i < rowIndex; ++i) {
            std::vector<int> new_v(v.size() + 1);
            new_v[0] = 1;
            new_v.back() = 1;
            for (int j = 1; j < static_cast<int>(v.size()); ++j) {
                new_v[j] = v[j - 1] + v[j];
            }
            v.swap(new_v);
        }
        return v;
    }
};

int main(int /*argc*/, char* /*argv*/ [])
{
    struct TestCase {
        int rowIndex;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { 0, { 1 } },
        { 1, { 1, 1 } },
        { 2, { 1, 2, 1 } },
        { 3, { 1, 3, 3, 1 } },
        { 4, { 1, 4, 6, 4, 1 } },
        { 5, { 1, 5, 10, 10, 5, 1 } },
        { 6, { 1, 6, 15, 20, 15, 6, 1 } },
        { 7, { 1, 7, 21, 35, 35, 21, 7, 1 } },
        { 8, { 1, 8, 28, 56, 70, 56, 28, 8, 1 } },
        { 9, { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.getRow(tc.rowIndex);
        if (tc.exp != ans) {
            std::cout << "FAIL. rowIndex: " << tc.rowIndex << "\n";
        }
    }
    return 0;
}
