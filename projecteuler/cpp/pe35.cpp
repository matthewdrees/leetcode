// Project Euler problem 35.
//
// The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
//
// How many circular primes are there below one million?
#include "project_euler_common.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template <class T>
std::vector<T> get_digits_vector(T n)
{
    std::vector<T> v;
    while (n != 0)
    {
        v.push_back(n % 10);
        n = n / 10;
    }
    return v;
}

template <class T>
T get_num_from_digits(std::vector<T> v)
{
    T num = 0;
    for (size_t i = v.size(); i-- > 0;)
    {
        num += v[i];
        num *= 10;
    }
    return num /= 10;
}

static std::string to_string(const std::vector<int> v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v)
    {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

bool test_get_digits_vector()
{
    struct TestCase
    {
        int n;
        std::vector<int> expected;
    };

    TestCase testCases[] = {
        {1, {1}},
        {10, {0, 1}},
        {97, {7, 9}},
        {159, {9, 5, 1}},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = get_digits_vector(tc.n);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << to_string(tc.expected) << ", actual: " << to_string(actual) << "\n";
        }
    }
    return passed;
}

bool test_get_num_from_digits()
{
    struct TestCase
    {
        std::vector<int> v;
        int expected;
    };

    TestCase testCases[] = {
        {{1}, 1},
        {{0, 1}, 10},
        {{7, 9}, 97},
        {{9, 5, 1}, 159},
    };
    bool passed = true;
    for (const auto &tc : testCases)
    {
        const auto actual = get_num_from_digits(tc.v);
        if (tc.expected != actual)
        {
            passed = false;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(v: " << to_string(tc.v)
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return passed;
}

// Find the number of circular primes under n.
int circular_primes(int n)
{
    const auto primes = get_primes(n);
    int num_circular_primes = 0;
    for (const auto prime : primes)
    {
        auto v = get_digits_vector(prime);

        bool is_circular_prime = true;
        for (size_t i = 1; i < v.size(); ++i)
        {
            std::rotate(v.begin(), v.begin() + 1, v.end());
            const auto prime = get_num_from_digits(v);
            if (!std::binary_search(primes.begin(), primes.end(), prime))
            {
                is_circular_prime = false;
                break;
            }
        }
        if (is_circular_prime)
        {
            ++num_circular_primes;
        }
    }
    return num_circular_primes;
}

int main()
{
    std::cout << circular_primes(1000000) << '\n';
    return test_get_digits_vector() && test_get_num_from_digits() ? 0 : 1;
}
