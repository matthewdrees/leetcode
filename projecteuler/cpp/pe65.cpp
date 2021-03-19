// Project Euler problem 65. Convergents of e.
#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>

int get_term_factor(int i)
{
    if (i % 3 == 0)
    {
        return (i / 3) * 2;
    }
    return 1;
}

// Get numerator of nth convergent term of e.
//
// The insight here is the pattern of the terms:
//
//      e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1 ...]
//
// Note that every 3rd value is: int(n / 3) * 2
//
// \param i: convergent term number of e.
// \return: numerator of nth convergent term.
boost::multiprecision::cpp_int get_numerator_of_convergent_term_of_e(int i)
{
    if (i < 1)
    {
        return 0;
    }
    if (i == 1)
    {
        return 2;
    }

    boost::multiprecision::cpp_int n = 1;
    boost::multiprecision::cpp_int d = get_term_factor(i);
    --i;
    for (; i > 1; --i)
    {
        boost::multiprecision::cpp_int tmp = d;
        d = get_term_factor(i) * d + n;
        n = tmp;
    }
    return d * 2 + n;
}

int add_digits(boost::multiprecision::cpp_int n)
{
    int total = 0;
    while (n != 0)
    {
        total += static_cast<int>(n % 10);
        n /= 10;
    }
    return total;
}

int pe65()
{
    return add_digits(get_numerator_of_convergent_term_of_e(100));
}

int test_get_numerator_of_convergent_term_of_e()
{
    struct TestCase
    {
        int n;
        int expected;
    };
    TestCase testCases[] = {
        {0, 0},
        {1, 2},
        {2, 3},
        {3, 8},
        {4, 11},
        {5, 19},
        {6, 87},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_numerator_of_convergent_term_of_e(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int main()
{
    std::cout << pe65() << "\n";
    const int num_fails = test_get_numerator_of_convergent_term_of_e();
    return num_fails == 0 ? 0 : 1;
}
