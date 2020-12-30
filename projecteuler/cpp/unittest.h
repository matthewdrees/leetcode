// Unit test helper code

#include <functional>
#include <iostream>
#include <vector>

namespace unittest
{
    struct TestCase_s_i
    {
        std::string s;
        int expected;
    };
    int test_s_i(const char *func_name, std::function<int(std::string)> func, std::vector<TestCase_s_i> testcases)
    {
        int num_fails = 0;
        for (const auto &tc : testcases)
        {
            const auto actual = func(tc.s);
            if (tc.expected != actual)
            {
                ++num_fails;
                std::cerr << "FAIL, " << func_name
                          << "(s: " << tc.s
                          << "), expected: " << tc.expected
                          << ", actual: " << actual << "\n";
            }
        }
        return num_fails;
    }

} // namespace unittest