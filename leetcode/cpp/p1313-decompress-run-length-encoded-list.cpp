#import <iostream>
#import <sstream>
#import <vector>

using namespace std;

class Solution {
public:
    vector<int> decompressRLElist(vector<int> nums)
    {
        vector<int> decompressedList;
        for (size_t i = 0; i < nums.size(); i += 2) {
            const auto count = nums[i];
            const auto num = nums[i + 1];
            (void)decompressedList.insert(end(decompressedList), count, num);
        }
        return decompressedList;
    }
};

static string toString(vector<int> nums)
{
    ostringstream oss;
    for (const auto num : nums) {
        oss << num << ',';
    }
    return oss.str();
}

int main(int argc, char* argv[])
{
    struct TestCase {
        vector<int> compressedList;
        vector<int> exp;
    };
    const TestCase testCases[] = {
        { { 1, 1 }, { 1 } },
        { { 1, 2 }, { 2 } },
        { { 2, 1 }, { 1, 1 } },
        { { 1, 2, 3, 4 }, { 2, 4, 4, 4 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.decompressRLElist(tc.compressedList);
        if (tc.exp != ans) {
            cout << "FAIL. prices: "
                 << ", exp: " << toString(tc.exp)
                 << ", ans: " << toString(ans) << "\n";
        }
    }
    return 0;
}
