// Project Euler problem 67.
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using Triangle = std::vector<std::vector<int>>;

// Get triangle values from a file.
Triangle get_triangle_from_file(std::string filename)
{
    Triangle triangle;

    std::ifstream ifs(filename);
    while (ifs.good())
    {
        std::string line;
        while (std::getline(ifs, line))
        {
            std::vector<int> v;
            std::istringstream iss(line);
            int i;
            while (iss >> i)
            {
                v.push_back(i);
            }
            if (!v.empty())
            {
                triangle.push_back(std::move(v));
            }
        }
    }
    return triangle;
}

// Return score of maximum path through the triangle.
//
// \param triangle_str: string representing triangle of numbers.
// \return: score of highest path through triangle.
int maximum_path_sum(Triangle triangle)
{
    assert(triangle.size() > 1);
    for (size_t y = triangle.size() - 1; y-- > 0;)
    {
        assert(triangle[y].size() + 1 == triangle[y + 1].size());
        for (size_t x = triangle[y].size(); x-- > 0;)
        {
            triangle[y][x] += std::max(triangle[y + 1][x], triangle[y + 1][x + 1]);
        }
    }
    return triangle[0][0];
}

int main()
{
    auto triangle = get_triangle_from_file("p067_triangle.txt");
    std::cout << maximum_path_sum(triangle) << "\n";
    return 0;
}
