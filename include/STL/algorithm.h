#ifndef MSL_ALGORITHM_H
#define MSL_ALGORITHM_H

namespace std
{
    template <typename T> 
    const T& max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }
}

#endif