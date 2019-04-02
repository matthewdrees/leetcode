#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> numIndexMap;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            int num = nums[i];
            int ans = target - num;
            const auto it = numIndexMap.find(ans);
            if (it != numIndexMap.end()) {
                return { it->second, i };
            }
            numIndexMap[num] = i;
        }
        return {};
    }
};

int main(int /*argc*/, char* /*argv*/ [])
{
    struct TestCase {
        std::vector<int> nums;
        int target;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { { 1, 1 }, 2, { 0, 1 } },
        { { 2, 7 }, 9, { 0, 1 } },
        { { 2, 7, 11, 15 }, 9, { 0, 1 } },
        { { 2, 7, 11, 15 }, 13, { 0, 2 } },
        { { 2, 7, 11, 15 }, 17, { 0, 3 } },
        { { 2, 7, 11, 15 }, 18, { 1, 2 } },
        { { 2, 7, 11, 15 }, 22, { 1, 3 } },
        { { 2, 7, 11, 15 }, 26, { 2, 3 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.twoSum(tc.nums, tc.target);
        if (tc.exp != ans) {
            std::cout << "FAIL. target: " << tc.target
                 << ", exp: " << tc.exp.size()
                 << ", ans: " << ans.size() << "\n";
        }
    }
    return 0;
}
