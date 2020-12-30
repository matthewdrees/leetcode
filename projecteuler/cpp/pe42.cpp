// Project Euler problem 42. Coded triangle numbers.
//
// The nth term of the sequence of triangle numbers is given by, tₙ = ½n(n+1); so the first ten triangle numbers are:
//
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
// By converting each letter in a word to a number corresponding to its alphabetical position and adding these
// values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t₁₀. If the word
// value is a triangle number then we shall call the word a triangle word.
//
// Using https://projecteuler.net/project/resources/p042_words.txt, a 16K text file containing nearly
// two-thousand common English words, how many are triangle words?
#include <cassert>
#include <fstream>
#include <iostream>

int get_word_score(std::string word)
{
    int score = 0;
    for (const char c : word)
    {
        const int c_score = 1 + c - 'A';
        assert(c_score >= 1 && c_score <= 26);
        score += c_score;
    }
    return score;
}

int test_get_word_score()
{
    struct TestCase
    {
        std::string s;
        int expected;
    };
    TestCase testCases[] = {
        {"A", 1},
        {"B", 2},
        {"Z", 26},
        {"SKY", 55},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_word_score(tc.s);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(s: " << tc.s
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

bool is_triangle_number(int n)
{
    // Note, would be faster to precompute these and look them up but this was easy and fast enough.
    int delta = 1;
    for (int i = 1; i <= n; i += delta)
    {
        if (i == n)
        {
            return true;
        }
        delta += 1;
    }
    return false;
}

int test_is_triangle_number()
{
    struct TestCase
    {
        int n;
        bool expected;
    };
    TestCase testCases[] = {
        {0, false},
        {1, true},
        {2, false},
        {3, true},
        {4, false},
        {5, false},
        {6, true},
        {7, false},
        {9, false},
        {10, true},
        {11, false},
        {54, false},
        {55, true},
        {56, false},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = is_triangle_number(tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(n: " << tc.n
                      << "), expected: " << tc.expected << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

int main()
{
    int num_triangle_words = 0;
    std::ifstream ifs("p042_words.txt");
    while (ifs.good())
    {
        std::string quoted_word;
        std::getline(ifs, quoted_word, ',');
        const std::string word = quoted_word.substr(1, quoted_word.size() - 2);
        const int score = get_word_score(word);
        if (is_triangle_number(score))
        {
            ++num_triangle_words;
        }
    }
    std::cout << num_triangle_words << '\n';

    const int num_fails = test_get_word_score() + test_is_triangle_number();
    return num_fails == 0 ? 0 : 1;
}
