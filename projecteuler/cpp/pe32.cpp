// Project Euler problem 32. Pandigital products.
//
// We shall say that an n-digit number is pandigital if it makes use of all the digits 1
// to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
//
// The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand,
// multiplier, and product is 1 through 9 pandigital.
//
// Find the sum of all products whose multiplicand/multiplier/product identity can be
// written as a 1 through 9 pandigital.
//
// HINT: Some products can be obtained in more than one way so be sure to only include it
// once in your sum.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

int compare_helper(std::string n, int len1, int len2)
{
    int num1 = stoi(n.substr(0, len1));
    int num2 = stoi(n.substr(len1, len2));
    int ans = stoi(n.substr(len1 + len2, n.size() - len1 - len2));

    if (num1 * num2 == ans)
    {
        // std::cout << "found " << num1 << " * " << num2 << " == " << ans << '\n';
        return ans;
    }
    return 0;
}

int main()
{
    std::unordered_set<int> products;
    std::string s = "123456789";
    do
    {
        products.insert(compare_helper(s, 1, 3));
        products.insert(compare_helper(s, 1, 4));
        products.insert(compare_helper(s, 2, 2));
        products.insert(compare_helper(s, 2, 3));
    } while (std::next_permutation(s.begin(), s.end()));

    std::cout << std::accumulate(products.begin(), products.end(), 0) << '\n';
}
