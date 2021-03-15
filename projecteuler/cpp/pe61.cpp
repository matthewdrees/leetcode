// Project Euler problem 61. Cyclical figurate numbers.
#include <algorithm>
#include <iostream>
#include <vector>

template <class Func>
std::vector<int> get_4_digit_shape_numbers(Func shape_func)
{
    std::vector<int> v;
    for (int i = 0; i < 10'000; ++i)
    {
        const int n = shape_func(i);
        if (n >= 10'000)
        {
            break;
        }
        if (n >= 1'000)
        {
            v.push_back(n);
        }
    }
    return v;
}

bool does_overlap(int i1, int i2)
{
    return (i1 % 100) == (i2 / 100);
}

int pe61()
{
    std::vector<std::vector<int>> shape_numbers;
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * (n + 1) / 2; }));
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * n; }));
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * (3 * n - 1) / 2; }));
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * (2 * n - 1); }));
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * (5 * n - 3) / 2; }));
    shape_numbers.push_back(get_4_digit_shape_numbers([](int n) { return n * (3 * n - 2); }));

    std::vector<size_t> indexes = {0, 1, 2, 3, 4, 5};
    do
    {
        for (const auto a : shape_numbers[indexes[0]])
        {
            for (const auto b : shape_numbers[indexes[1]])
            {
                if (!does_overlap(a, b))
                {
                    continue;
                }
                for (const auto c : shape_numbers[indexes[2]])
                {
                    if (!does_overlap(b, c))
                    {
                        continue;
                    }
                    for (const auto d : shape_numbers[indexes[3]])
                    {
                        if (!does_overlap(c, d))
                        {
                            continue;
                        }
                        for (const auto e : shape_numbers[indexes[4]])
                        {
                            if (!does_overlap(d, e))
                            {
                                continue;
                            }
                            for (const auto f : shape_numbers[indexes[5]])
                            {
                                if (does_overlap(e, f))
                                {
                                    if (does_overlap(f, a))
                                    {
                                        return a + b + c + d + e + f;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (std::next_permutation(begin(indexes), end(indexes)));
    return 0;
}

int main()
{
    std::cout << pe61() << "\n";
    return 0;
}
