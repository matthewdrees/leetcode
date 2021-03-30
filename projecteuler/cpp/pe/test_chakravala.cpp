#include "pe/chakravala.hpp"

using namespace pe;

int test_chakravala_method()
{
    struct TestCase
    {
        int n;
        pe::ChakravalaTriple expected;
    };
    TestCase testCases[] = {
        {1, {0, 0, 0}},
        {2, {3, 2, 1}},
        {3, {2, 1, 1}},
        {4, {0, 0, 0}},
        {5, {9, 4, 1}},
        {6, {5, 2, 1}},
        {7, {8, 4, 1}},
        {61, {1766319049, 226153980, 1}},
        {109, {158070671986249, 15140424455100, 1}},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = pe::chakravala_method(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << pe::to_string(tc.expected)
                      << ", actual: " << pe::to_string(actual)
                      << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_chakravala_method();
    return num_fails == 0 ? 0 : 1;
}
