// Project Euler problem 62. Cubic permutations.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

int64_t sort_num_descending(int64_t n)
{
    std::vector<int8_t> v;
    v.reserve(16);
    while (n != 0)
    {
        v.push_back(n % 10);
        n /= 10;
    }
    std::sort(begin(v), end(v), std::greater<>());
    int64_t ret = 0;
    for (const auto i : v)
    {
        ret *= 10;
        ret += i;
    }
    return ret;
}

int64_t pe62()
{
    constexpr int I_MAX = 2'094'101; // cubed root of int64_t::max.

    std::unordered_map<int64_t, size_t> map;
    int64_t sorted_cube_im_looking_for = 0;
    for (int i = 1; i < I_MAX; ++i)
    {
        const int64_t cube = std::pow(static_cast<int64_t>(i), 3);
        const int64_t sorted_cube = sort_num_descending(cube);
        auto it = map.find(sorted_cube);
        if (it == map.end())
        {
            map.insert({sorted_cube, 1});
        }
        else
        {
            ++(it->second);
            if (it->second == 5)
            {
                sorted_cube_im_looking_for = sorted_cube;
                break;
            }
        }
    }
    if (sorted_cube_im_looking_for != 0)
    {
        for (int i = 1; i < I_MAX; ++i)
        {
            const int64_t cube = std::pow(static_cast<int64_t>(i), 3);
            const int64_t sorted_cube = sort_num_descending(cube);
            if (sorted_cube == sorted_cube_im_looking_for)
            {
                return cube;
            }
        }
    }
    return 0;
}

int main()
{
    std::cout << pe62() << "\n";
    return 0;
}
