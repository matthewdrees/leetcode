/* Functions that are helpful for project euler problems. */

#include <cmath>

// Returns sum of consecutive numbers from first to last.
// e.g. add_consectutive_numbers(1, 5) -> 15
template <class T>
T add_consecutive_numbers(T first, T last)
{
    if (first > last)
    {
        return 0;
    }
    // Carl Gauss's formula.
    const T total_numbers = last - first + 1;
    return total_numbers * (first + last) / 2;
}

// True if n is prime.
template <class T>
bool is_prime(T n)
{
    if (n < 2)
    {
        return false;
    }
    if (n == 2)
    {
        return true;
    }
    if (n % 2 == 0)
    {
        return false;
    }
    for (int i = 3; i < static_cast<T>(std::sqrt(n)) + 1; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
