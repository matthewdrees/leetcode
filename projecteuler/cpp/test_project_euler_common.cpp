/* Unit tests for project_euler_common.h. */
#include "project_euler_common.h"

#include <iostream>

bool test_add_consecutive_numbers()
{
    struct TestCase
    {
        int first;
        int last;
        int expected;
    };

    TestCase testCases[] = {
        {0, 0, 0},
        {1, 0, 0},

        {0, 1, 1},
        {0, 2, 3},
        {0, 3, 6},
        {0, 4, 10},
        {0, 5, 15},

        {1, 2, 3},
        {1, 5, 15},

        {2, 3, 5},

        {-1, 0, -1},
        {-2, 0, -3},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = add_consecutive_numbers(tc.first, tc.last);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(first: " << tc.first << ", last: " << tc.last
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

int main()
{
    bool passed = true;

    passed = passed && test_add_consecutive_numbers();

    return passed ? 0 : 1;
}
