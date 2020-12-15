// Project Euler problem 39. Integer right triangles.
//
// If p is the perimeter of a right angle triangle with integral length sides,
// {a,b,c}, there are exactly three solutions for p = 120.
//
// {20,48,52}, {24,45,51}, {30,40,50}
//
// For which value of p ≤ 1000, is the number of solutions maximised?
#include <iostream>

int get_num_solutions_integer_right_triangle(int perimeter)
{
    int num_solutions = 0;
    for (int a = 1; a < perimeter / 3; ++a)
    {
        const int a2 = a * a;
        // Could speed this up by binary searching for b -> c
        // ... but it already runs in < 1 second.
        for (int b = a; b < perimeter / 2; ++b)
        {
            const int b2 = b * b;
            const int c = perimeter - a - b;
            const int c2 = c * c;
            if (a2 + b2 == c2)
            {
                num_solutions += 1;
                break;
            }
            if (a2 + b2 >= c2)
            {
                break;
            }
        }
    }
    return num_solutions;
}

int main()
{
    int max_num_solutions = 0;
    int max_perimeter = 0;

    for (int p = 120; p <= 1000; ++p)
    {
        const int num_solutions = get_num_solutions_integer_right_triangle(p);
        if (num_solutions > max_num_solutions)
        {
            max_num_solutions = num_solutions;
            max_perimeter = p;
        }
    }
    std::cout << max_perimeter << '\n';
}
