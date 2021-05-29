
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
