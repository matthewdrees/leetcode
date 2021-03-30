// Project Euler problem 66. Diophantine equation.
#include "pe/chakravala.hpp"

boost::multiprecision::cpp_int pe66()
{
    boost::multiprecision::cpp_int D_for_largest_x;
    boost::multiprecision::cpp_int largest_x;
    for (boost::multiprecision::cpp_int D = 2; D <= 1000; ++D)
    {
        const auto ct = pe::chakravala_method(D);
        if (ct.x > largest_x)
        {
            largest_x = ct.x;
            D_for_largest_x = D;
        }
    }
    return D_for_largest_x;
}

int main()
{
    std::cout << pe66() << "\n";
    return 0;
}
