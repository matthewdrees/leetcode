#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> triplets;
        if (nums.size() < 3) {
            return triplets;
        }

        const std::unordered_multiset<int> num_freq(nums.begin(), nums.end(), nums.size());

        // I wouldn't unnecessarily manipulate the input values like this in real
        // life, but it helps with speed. Need them sorted with unique values.
        std::sort(nums.begin(), nums.end());
        const auto nums_last = std::unique(nums.begin(), nums.end());
        const int max_num = *(nums_last - 1);
        if (max_num < 0) {
            return triplets;
        }
        
        auto nums_it = nums.begin();
        if (max_num < (INT32_MAX / 2)) {
            // Skip the first numbers that can't possibly be answers.
            const int min_num = -2 * max_num;
            nums_it = std::lower_bound(nums.begin(), nums_last, min_num);
        }

        for ( ; nums_it != nums_last; ++nums_it) {
            if (num_freq.count(*nums_it) >= 2) {

                // Handle 3 zeros.
                if (*nums_it == 0 && num_freq.count(0) >= 3) {
                    triplets.push_back({ 0, 0, 0 });

                // Handle 2 of same number.
                } else {
                    const int complement = -2 * *nums_it;
                    if (num_freq.count(complement) > 0 && complement != *nums_it) {
                        triplets.push_back({ *nums_it, *nums_it, complement });
                    }
                }
            }
            if ( *nums_it < 0) {
                const int two_sum = -*nums_it;
                auto lb = std::lower_bound(nums_it+1, nums_last, two_sum - max_num);
                auto ub = std::upper_bound(lb, nums_last, two_sum / 2);
                for (auto i = lb; i < ub; ++i) {
                    const int complement = two_sum - *i;
                    if (num_freq.count(complement) > 0 && *i != complement) {
                        triplets.push_back({ *nums_it, *i, complement });
                    }
                }
            }
        }
        return triplets;
    }
};

void coutNums(const std::vector<int>& v)
{
    std::cout << "{";
    if (!v.empty()) {
        std::cout << v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            std::cout << "," << v[i];
        }
    }
    std::cout << "}";
}

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<std::vector<int>> exp;
    };
    TestCase testCases[] = {
        { { 0, 0, 0 }, { { 0, 0, 0 } } },
        { { -4, -2, -1 }, {} },
        { { 1, 0, -1 }, { { -1, 0, 1 } } },
        { { 2, -1, -1 }, { { -1, -1, 2 } } },
        { { 1, -1, 0, 2 }, { { -1, 0, 1 } } },
        { { 3, 1, -1, 0 }, { { -1, 0, 1 } } },
        { { 1, -2, -1, 0 }, { { -1, 0, 1 } } },
        { { 1, -1, -2, 0 }, { { -1, 0, 1 } } },
        { { 1, -1, 2, -1, 0 }, { { -1, -1, 2 }, { -1, 0, 1 } } },
        { { -1, 0, 1, 2, -1, -4 }, { { -1, -1, 2 }, { -1, 0, 1 } } },
        { { -4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6 }, { { -4, -2, 6 }, { -4, 0, 4 }, { -4, 1, 3 }, { -2, -2, 4 }, { -2, 0, 2 }, { 2, 2, -4 } } },
        { { INT32_MIN + 1, 0, INT32_MAX }, { { INT32_MIN + 1, 0, INT32_MAX } } },
    };

    Solution s;
    for (auto& tc : testCases) {
        const auto ans = s.threeSum(tc.nums);
        if (tc.exp != ans) {
            std::cout << "FAIL. nums: ";
            coutNums(tc.nums);
            std::cout << ", exp: \n";
            for (const auto& v : tc.exp) {
                std::cout << "   ";
                coutNums(v);
                std::cout << "\n";
            }
            std::cout << "  ans: \n";
            for (const auto& v : ans) {
                std::cout << "   ";
                coutNums(v);
                std::cout << "\n";
            }
        }
    }
    return 0;
}
