#include <iterator>

template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (auto it = first; it != last; ++it)
    {
        if (!p(*it))
        {
            return false;
        }
    }
    return true;
}

template <class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (auto it = first; it != last; ++it)
    {
        if (p(*it))
        {
            return true;
        }
    }
    return false;
}

template <class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p)
{
    return !any_of(first, last, p);
}

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
    for (auto it = first; it != last; ++it)
    {
        f(*it);
    }
    return f;
}

template <class InputIt, class Size, class UnaryFunction>
constexpr InputIt for_each_n(InputIt first, Size n, UnaryFunction f)
{
    auto it = first;
    for (; it != first + n; ++it)
    {
        f(*it);
    }
    return it;
}

template <class InputIt, class T>
constexpr typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T &value)
{
    typename std::iterator_traits<InputIt>::difference_type n = 0;
    for (auto it = first; it != last; ++it)
    {
        if (*it == value)
        {
            ++n;
        }
    }
    return n;
}

template <class InputIt, class UnaryPredicate>
constexpr typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p)
{
    typename std::iterator_traits<InputIt>::difference_type n = 0;
    for (auto it = first; it != last; ++it)
    {
        if (p(*it))
        {
            ++n;
        }
    }
    return n;
}

template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1,
         InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2))
        {
            break;
        }
    }
    return {first1, first2};
}

template <class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T &value)
{
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            break;
        }
    }
    return first;
}

template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            break;
        }
    }
    return first;
}

template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (!p(*first))
        {
            break;
        }
    }
    return first;
}
