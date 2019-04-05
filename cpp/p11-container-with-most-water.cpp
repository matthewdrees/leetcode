#include <iostream>
#include <vector>

class Solution {
public:
    int maxArea(const std::vector<int>& height)
    {
        if (height.empty()) {
            return 0;
        }
        int x = 0;
        int y = static_cast<int>(height.size()) - 1;
        int max_area = 0;
        while (x != y) {
            const int area = std::min(height[x], height[y]) * (y - x);
            max_area = std::max(area, max_area);
            if (height[x] < height[y]) {
                ++x;
            } else {
                --y;
            }
        }
        return max_area;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<int> height;
        int exp;
    };
    const TestCase testCases[] = {
        { { 1, 1 }, 1 },
        { { 2, 2 }, 2 },
        { { 1, 2 }, 1 },
        { { 2, 1 }, 1 },
        { { 1, 2, 3 }, 2 },
        { { 1, 3, 2 }, 2 },
        { { 2, 1, 3 }, 4 },
        { { 2, 3, 1 }, 2 },
        { { 3, 1, 2 }, 4 },
        { { 3, 2, 1 }, 2 },
        { { 1, 8, 6, 2, 5, 4, 8, 3, 7 }, 49 },
        { { 7, 6, 4, 3, 1 }, 9 },
        { { 1, 2, 3, 2, 1 }, 4 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.maxArea(tc.height);
        if (tc.exp != ans) {
            std::cout << "FAIL. height: "
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
