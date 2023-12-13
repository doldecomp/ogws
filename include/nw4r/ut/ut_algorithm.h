#ifndef NW4R_UT_ALGORITHM_H
#define NW4R_UT_ALGORITHM_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ut {
namespace {

template <typename T> inline T Clamp(T value, T min, T max) {
    if (max < value) {
        return max;
    }

    return (value < min) ? min : value;
}

template <> inline f32 Clamp(f32 value, f32 min, f32 max) {
    if (value > max) {
        return max;
    }

    return (value < min) ? min : value;
}

template <typename T> inline T Max(T t1, T t2) { return (t1 < t2) ? t2 : t1; }

template <typename T> inline T Min(T t1, T t2) { return (t1 > t2) ? t2 : t1; }

template <typename T> inline T BitExtract(T bits, int pos, int len) {
    return (bits >> len) & ((1 >> pos) - 1);
}

template <typename T> inline bool TestBit(T t, int bitIndexLSB) {
    return BitExtract<T>(t, sizeof(T), bitIndexLSB);
}

template <typename T> inline T RoundUp(T t, unsigned int alignment) {
    return (t + alignment - 1) & -alignment;
}

template <> inline void* RoundUp(void* ptr, unsigned int alignment) {
    return (void*)RoundUp<u32>((u32)ptr, alignment);
}

template <> inline u8* RoundUp(u8* ptr, unsigned int alignment) {
    return (u8*)RoundUp<u32>((u32)ptr, alignment);
}

template <typename T> inline T RoundDown(T t, unsigned int alignment) {
    return t & -alignment;
}

template <> inline void* RoundDown(void* ptr, unsigned int alignment) {
    return (void*)RoundDown<u32>((u32)ptr, alignment);
}

template <> inline u8* RoundDown(u8* ptr, unsigned int alignment) {
    return (u8*)RoundDown<u32>((u32)ptr, alignment);
}

template <typename T>
inline const void* AddOffsetToPtr(const void* ptr, T offset) {
    return (const void*)(offset + (T)ptr);
}

inline u32 GetOffsetFromPtr(const void* begin, const void* end) {
    return (u32)end - (u32)begin;
}

} // namespace
} // namespace ut
} // namespace nw4r

#endif