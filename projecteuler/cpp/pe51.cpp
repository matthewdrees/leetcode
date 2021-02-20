// Project Euler problem 51. Prime digit replacements.
//
// By replacing the 1st digit of the 2-digit number *3, it turns out that six of
// the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.
//
// By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit
// number is the first example having seven primes among the ten generated
// numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and
// 56993. Consequently 56003, being the first member of this family, is the
// smallest prime with this property.
//
// Find the smallest prime which, by replacing part of the number (not
// necessarily adjacent digits) with the same digit, is part of an eight prime
// value family.
#include "project_euler_common.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> get_filtered_6_digit_primes()
{
    auto primes = get_primes(1000000);

    auto it = std::find_if(primes.begin(), primes.end(), [](int p) { return p > 100000; });
    return std::vector<int>(it, primes.end());
}

class Digits
{
public:
    Digits();
    explicit Digits(int num)
    {
        while (num != 0)
        {
            digits.push_back(static_cast<int8_t>(num % 10));
            num = num / 10;
        }
    }

    int8_t operator[](size_t index) const
    {
        assert(index < digits.size());
        return digits[index];
    }

    std::vector<int8_t> digits;
    void set_digit(size_t index, int8_t value)
    {
        assert(index < digits.size());
        digits[index] = value;
    }

    int get_num_int() const noexcept
    {
        int num = 0;
        for (size_t i = digits.size(); i-- > 0;)
        {
            num += digits[i];
            num *= 10;
        }
        return num /= 10;
    }
};

int get_smallest_prime_eight_prime_value_family(const std::vector<int> &primes, std::vector<size_t> number_indexes)
{
    assert(number_indexes.size() >= 2);

    // map masked prime to the prime value family values.
    std::unordered_map<int, std::vector<int>> map;

    size_t biggest_size = 0;
    for (const auto p : primes)
    {
        auto digits = Digits(p);
        const auto num = digits.digits[number_indexes[0]];
        if (std::all_of(number_indexes.begin() + 1, number_indexes.end(), [=](const auto i) { return digits[i] == num; }))
        {
            for (const auto i : number_indexes)
            {
                digits.set_digit(i, 0);
            }
            int key = digits.get_num_int();
            auto it = map.find(key);
            if (it == map.end())
            {
                map.insert({key, {p}});
            }
            else
            {
                it->second.push_back(p);
                if (it->second.size() == 8)
                {
                    return it->second.front();
                }
                biggest_size = std::max(biggest_size, it->second.size());
            }
        }
    }

    return 0;
}

int main()
{
    auto primes = get_filtered_6_digit_primes();

    const size_t LEN = 6;
    for (size_t i = 1; i < LEN; ++i)
    {
        for (size_t j = i + 1; j < LEN; ++j)
        {
            for (size_t k = j + 1; k < LEN; ++k)
            {
                std::vector<size_t> number_indexes = {i, j, k};
                int val = get_smallest_prime_eight_prime_value_family(primes, number_indexes);
                if (val > 0)
                {
                    std::cout << val << "\n";
                }
            }
        }
    }
    return 0;
}
