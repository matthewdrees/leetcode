// Chakravala method.
//
// From Wikipedia: "The chakravala method is a cyclic algorithm to solve
// indeterminate quadratic equations, including Pell's equation."
// https://en.wikipedia.org/wiki/Chakravala_method
//
// The implementation was taken from "The method" section on that page.
//
// Inspired by Project Euler problem 66 "Diophantine equation":
// https://projecteuler.net/problem=66

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>

#include <sstream>
#include <utility>

namespace pe
{
    struct ChakravalaTriple
    {
        boost::multiprecision::cpp_int x;
        boost::multiprecision::cpp_int y;
        boost::multiprecision::cpp_int k;
    };
    bool operator==(const ChakravalaTriple &ct1, const ChakravalaTriple &ct2)
    {
        return ct1.x == ct2.x &&
               ct1.y == ct2.y &&
               ct1.k == ct2.k;
    }
    bool operator!=(const ChakravalaTriple &ct1, const ChakravalaTriple &ct2)
    {
        return !(ct1 == ct2);
    }
    std::string to_string(const ChakravalaTriple &ct)
    {
        std::ostringstream oss;
        oss << "{" << ct.x << ", " << ct.y << ", " << ct.k << "}";
        return oss.str();
    }

    bool chakravala_is_integer(const ChakravalaTriple &ct, const boost::multiprecision::cpp_int &m)
    {
        return (ct.x + m * ct.y) % ct.k == 0;
    }

    boost::multiprecision::cpp_int chakravala_find_m(const ChakravalaTriple &ct, const boost::multiprecision::cpp_int &N)
    {
        boost::multiprecision::cpp_int lo_root = boost::multiprecision::sqrt(N);
        boost::multiprecision::cpp_int hi_root = lo_root + 1;
        boost::multiprecision::cpp_int lo_delta = N - lo_root;
        boost::multiprecision::cpp_int hi_delta = hi_root - N;

        while (lo_root != 0)
        {
            if (lo_delta <= hi_delta)
            {
                if (chakravala_is_integer(ct, lo_root))
                {
                    return lo_root;
                }
                --lo_root;
                lo_delta += lo_root * 2 + 1;
            }
            else
            {
                if (chakravala_is_integer(ct, hi_root))
                {
                    return hi_root;
                }
                hi_delta += hi_root * 2 + 1;
                ++hi_root;
            }
        }
        for (; !chakravala_is_integer(ct, hi_root); ++hi_root)
        {
        }
        return hi_root;
    }

    // Solve Pell's equation for x and y given N.
    //
    //    x^2 - N * y^2 = 1
    //
    // \param N: value of N for Pell's equation.
    // \return: ChakravalaTriple with k == 1, and x, y as a solution.
    //          If N is < 2 or square, all values are zero.
    ChakravalaTriple chakravala_method(boost::multiprecision::cpp_int N)
    {
        ChakravalaTriple ct;
        if (N < 2)
        {
            return ct;
        }
        ct.x = boost::multiprecision::sqrt(N);
        if (ct.x * ct.x == N)
        {
            ct.x = 0;
            return ct;
        }
        ++ct.x;
        ct.y = 1;
        ct.k = ct.x * ct.x - N;
        while (ct.k != 1)
        {
            ChakravalaTriple next;
            const boost::multiprecision::cpp_int m = chakravala_find_m(ct, N);
            next.x = (ct.x * m + N * ct.y) / boost::multiprecision::abs(ct.k);
            next.y = (ct.x + ct.y * m) / boost::multiprecision::abs(ct.k);
            next.k = (m * m - N) / ct.k;
            ct = std::move(next);
        }
        return ct;
    }
}
