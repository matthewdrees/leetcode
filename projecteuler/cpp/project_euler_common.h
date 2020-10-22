/* Functions that are helpful for project euler problems. */

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
