#ifndef MSL_ALGORITHM_H
#define MSL_ALGORITHM_H

namespace std
{
    struct random_access_iterator_tag {};

    template <typename T> 
    inline const T& max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }

    template <typename TPtr, typename T>
    inline TPtr find(TPtr first, TPtr last, const T& value)
    {
        for (; (first != last) && (*first != value);) { ++first; }
        return first;
    }

    template <typename TPtr>
    inline int distance(TPtr first, TPtr last)
    {
        random_access_iterator_tag tag;
        return __distance(first, last, tag);
    }

    template <typename TPtr>
    inline long __distance(TPtr first, TPtr last, random_access_iterator_tag tag)
    {
        long dist = (long)last - (long)first;
        return dist / (long)sizeof(TPtr);
    }
}

#endif